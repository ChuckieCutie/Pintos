#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024 // Size of the shared memory segment

int main() {
    key_t key = ftok("shmfile", 65); // Create the same key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Access the shared memory segment
    char *str = (char*)shmat(shmid, (void*)0, 0); // Attach to shared memory

    printf("Reader Process: Read from shared memory: %s\n", str); // Read message
    shmdt(str); // Detach from shared memory

    shmctl(shmid, IPC_RMID, NULL); // Destroy the shared memory segment
    return 0;
}