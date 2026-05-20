#include "task.h"
#include <string.h>

int main() {

    int semid = semget(SEM_KEY, 1, 0666);
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    
    if (semid < 0 || shmid < 0) {
        printf("Ошибка: Сервер еще не запущен или IPC ресурсы не созданы!\n");
        return 1;
    }

    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        printf("Ошибка подключения к разделяемой памяти!\n");
        return 1;
    }
    strcpy(shm_ptr, "");
    printf("Клиент успешно записал данные в память.\n");

    struct sembuf unlock_op = {0, 1, 0};
    semop(semid, &unlock_op, 1);
    printf("Клиент отправил сигнал серверу через семафор.\n");

    shmdt(shm_ptr);
    return 0;
}

