#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_SIZE 1024
#define SEM_KEY 0x998877
#define SHM_KEY 0x665544

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

