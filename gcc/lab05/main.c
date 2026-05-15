#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>

#define styleRED   "\x1b[1;31m" 
#define styleGREEN "\x1b[1;32m" 
#define styleBLUE  "\x1b[1;34m" 
#define styleEND   "\x1b[0m"

// ДЛЯ ПРОСТОТЫ КОЛИЧЕСТВО ПЛАГИНСОВ ОГРАНИЧЕНО!
#define MAX_PLUGINS_COUNT     10
// Длина имени файла плагина!
#define MAX_FILE_NAME_LEN     32
// Длина имени плагина!
#define MAX_PLUGINS_NAME_LEN 128
//=============================================================================
int get_plugin_files(char* file_names)
{   int plugins_count = -1;
    // Получаем доступ к папке
    DIR *d; 
    struct dirent *dir;
    if ((d = opendir("plugins")) > 0)
    {   // Читаем содержимое папки
        while ((dir=readdir(d)) != NULL)
        {   // Выбираем только динамически линкуемые библиотеки,
            // увеличиваем количество плагинов, а затем
            // добавляем их имена в массив, т.е. по адресу БАЗЫ c вычисленным СМЕЩЕНИЕМ  
            if (strstr(dir->d_name, ".so")>0)
                strcpy(file_names + (++plugins_count)*MAX_FILE_NAME_LEN, dir->d_name);
            // Т.к. списки не строим, то количество ограничено
            if (plugins_count==MAX_PLUGINS_COUNT-1) break;
        }   
        closedir(d);
    }    
    return ++plugins_count;
}
//=============================================================================
int get_plugins(char* plugin_files, char* plugin_names)
{   printf("\n\n");
    // чистим память
    memset(plugin_files, 0, MAX_PLUGINS_COUNT*MAX_FILE_NAME_LEN);
    memset(plugin_names, 0, MAX_PLUGINS_COUNT*MAX_PLUGINS_NAME_LEN);
    int plugins_count = get_plugin_files(plugin_files);
    // Обрабатываем полученный перечень plugins
    // Не контролируется вариант когда файл есть, но не работает 
    for (int i=0; i<plugins_count; i++)
    {   
        if (*(plugin_files + i*MAX_FILE_NAME_LEN)>0)
        {   char path_name[256]="plugins/";
            // Соединяем имя с относительным путём
            strcat(path_name,(plugin_files + i*MAX_FILE_NAME_LEN));
            //printf("%s\n",path_name);
            // Связывание хендлера (указателя) с загружаемой в память библиотекой
            // В Windows функция LoadLibrary
            void* lib_handler = dlopen(path_name, RTLD_LAZY);
            if (!lib_handler)
            {
                fprintf(stderr, "dlopen() error: %s\n", dlerror());
                exit(1); 
            }
            // Описание аргументов и возвращаемого значения вызываемой из библиотеки функции
            void (*dllfunc)(char*);
            // Получение указателя на библиотечную функцию по её ИМЕНИ    
            // В Windows функция GetProcAddress 
            if (!(dllfunc = dlsym(lib_handler, "get_name")))
            {
                fprintf(stderr, "dllfunc() error: \n");
                dlclose(lib_handler);
                exit(1); 
            }
            // Вызов библиотечной функции по УКАЗАТЕЛЮ:
            // в нашем случае - передача адреса, для записи строки не более заранее оговореной длины
            (*dllfunc)(plugin_names + i*MAX_PLUGINS_NAME_LEN);
            //printf("%d.\t%s\n", i, (plugin_names + i*MAX_PLUGINS_NAME_LEN));
            // Выгрузка библиотеки из памяти по её хендлеру
            dlclose(lib_handler);
        }    
    }
    printf("\n\n");
    return plugins_count;
}
//=============================================================================
int call_plugin(char* file_name)
{   char path_name[256]="plugins/";
    // Соединяем имя с относительным путём
    strcat(path_name, file_name);
    // Связывание хендлера (указателя) с загружаемой в память библиотекой
    // В Windows функция LoadLibrary
    void* lib_handler = dlopen(path_name, RTLD_LAZY);
    if (!lib_handler)
    {
        fprintf(stderr, "dlopen() error: %s\n", dlerror());
        exit(1); 
    }
    // Описание аргументов и возвращаемого значения вызываемой из библиотеки функции
    int (*dllfunc)(int, int*);
    // Получение указателя на библиотечную функцию по её ИМЕНИ    
    // В Windows функция GetProcAddress 
    if (!(dllfunc = dlsym(lib_handler, "fun_job")))
    {
        fprintf(stderr, "dllfunc() error: \n");
        dlclose(lib_handler);
        exit(1); 
    }
    int A[10] = {102, 4, -45, 24, 17, 75, -3, -16, -3, 0};
    // Вызов библиотечной функции по УКАЗАТЕЛЮ:
    int b = (*dllfunc)(10, A);
    // Выгрузка библиотеки из памяти по её хендлеру
    dlclose(lib_handler);
    return 0;
}
//=============================================================================
// Многократная печать меню
int processing_plugins(char* plugin_files, char* plugin_names, int plugins_count)
{   while (1)    
    {   printf("\n\n");
        for (int i=0; i<plugins_count; i++)
            printf("%s%d.\t%s%s\n", styleGREEN, i+1, (plugin_names + i*MAX_PLUGINS_NAME_LEN), styleEND);
        printf("\nНажмите цифру и Enter (0 - это пректащение выполения):  ");
        int symbol = getchar();
        if (symbol==48) 
            break;
        else
            if (symbol<48 || symbol>48+plugins_count)
                printf("%sВведено неправильное число!%s\n", styleRED, styleEND);
            else 
                // расчёт СМЕЩЕНИЯ от нуля (для первого элемента) с шагом равным длине строки
                call_plugin((plugin_files + (symbol-48-1)*MAX_FILE_NAME_LEN));
        // В терминале Linux трудно получить код нажатой клавиши до нажатия Enter
        // В Windows можно применить _kbhit() 
        while ((symbol = getchar()) != '\n' && symbol != EOF);
    }
    return 0;
}
//=============================================================================
int main()
{   // ДЛЯ ПРОСТОТЫ КОЛИЧЕСТВО ПЛАГИНСОВ ОГРАНИЧЕНО!
    char plugin_files[MAX_PLUGINS_COUNT*32];
    char plugin_names[MAX_PLUGINS_COUNT*128];
    int plugins_count = 0;
    if ((plugins_count = get_plugins(plugin_files, plugin_names)) > 0)
        processing_plugins(plugin_files, plugin_names, plugins_count);
    return 0;
}
//=============================================================================
