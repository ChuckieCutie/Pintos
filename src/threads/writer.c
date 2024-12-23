#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    key_t key = ftok("shmfile", 65); // Create a unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory segment
    char *str = (char*)shmat(shmid, (void*)0, 0); // Attach to shared memory

    printf("Writer Process: Enter a message: ");
    fgets(str, SHM_SIZE, stdin); // Read input from user
    printf("Writer Process: Written to shared memory: %s\n", str);

    shmdt(str); // Detach from shared memory
    return 0;
}