#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    int *id;
    id = (int *)paramID;

    printf("Hello World! from thread #%d!\n", *id);
    pthread_exit(NULL);
    return NULL; 
}

int main(int argc, char *argv[]) {
    pthread_t threadsID[NUM_THREADS];
    int rc, t, param[NUM_THREADS];

    // Ciclo for para crear los hilos
    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %d\n", t);
        param[t] = t;

        rc = pthread_create(&threadsID[t], NULL, PrintHello, (void *)&param[t]);

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Ciclo for separado para hacer el join
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threadsID[t], NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    return 0;
}