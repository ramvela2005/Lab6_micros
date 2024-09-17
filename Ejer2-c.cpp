
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    int *id = (int *)paramID;
    printf("Hello World! from thread #%d!\n", *id);
    pthread_exit(NULL);
    return NULL; 
}

int main(int argc, char *argv[]) {
    pthread_t threadID;
    int rc, param;

    // Ciclo for que crea el hilo y hace el join en el mismo ciclo
    for (int t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %d\n", t);
        param = t;

        rc = pthread_create(&threadID, NULL, PrintHello, (void *)&param);

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        // Join del hilo inmediatamente después de crearlo
        rc = pthread_join(threadID, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    return 0;
}
