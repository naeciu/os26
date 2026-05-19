#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_FILES 100
#define MAX_PATH 512

typedef struct {
    char filepath[MAX_PATH];
    unsigned int crc;
} TrackedFile;

TrackedFile files[MAX_FILES];
int file_count = 0;

unsigned int calculate_crc32(const char* filepath) {
    FILE* file = fopen(filepath, "rb");
    if (!file) return 0;

    unsigned int crc = 0xFFFFFFFF;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        crc ^= (unsigned char)ch;
        for (int i = 0; i < 8; i++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320; 
            else
                crc >>= 1;
        }
    }
    fclose(file);
    return ~crc;
}

void scan_directory(const char* dirpath) {
    DIR* dir = opendir(dirpath);
    if (!dir) return;

    struct dirent* entry;
    struct stat statbuf;

    while ((entry = readdir(dir)) != NULL && file_count < MAX_FILES) {
        
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", dirpath, entry->d_name);

        if (stat(full_path, &statbuf) == 0 && S_ISREG(statbuf.st_mode)) {
            strcpy(files[file_count].filepath, full_path);
            files[file_count].crc = calculate_crc32(full_path);
            file_count++;
        }
    }
    closedir(dir);
}

int main() {
   
    const char* monitor_dir = "/home/itsadrill/os26/test";
    const char* log_file = "/tmp/test_folder_monitor.log";

    scan_directory(monitor_dir);

    // Демонизация процесса
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    if (setsid() < 0) exit(EXIT_FAILURE);
    umask(0);
    if (chdir("/") < 0) exit(EXIT_FAILURE);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    FILE* log = fopen(log_file, "a");
    if (log) {
        time_t now = time(NULL);
        fprintf(log, "[%s] Демон запущен. Взят на контроль %d файл(ов).\n", 
                strtok(ctime(&now), "\n"), file_count);
        fclose(log);
    }

    while (1) {
        sleep(20);

        for (int i = 0; i < file_count; i++) {
            unsigned int current_crc = calculate_crc32(files[i].filepath);

            if (current_crc != files[i].crc) {
                log = fopen(log_file, "a");
                if (log) {
                    time_t now = time(NULL);
                    fprintf(log, "[%s] Изменен файл %s! Старый CRC: 0x%08X, Новый CRC: 0x%08X\n", 
                            strtok(ctime(&now), "\n"), files[i].filepath, files[i].crc, current_crc);
                    fclose(log);
                }
                files[i].crc = current_crc;
            }
        }
    }
    return 0;
}
