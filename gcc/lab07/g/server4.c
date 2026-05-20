#include "task.h"

int main() {

    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);

    semctl(semid, 0, SETVAL, 0);

    printf("Сервер запущен. Ожидание клиента...\n");

    struct sembuf lock_op = {0, -1, 0};
    semop(semid, &lock_op, 1);

    printf("Сервер прочитал из памяти: %s\n", shm_ptr);

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, 0);
    
    return 0;
}

