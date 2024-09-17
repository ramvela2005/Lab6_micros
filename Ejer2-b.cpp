#include <pthread.h>
#include <iostream>
#include <cstdlib>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    int *id = (int *)paramID;
    std::cout << "Hello World! from thread #" << *id << "!" << std::endl;
    pthread_exit(NULL);
    return NULL; 
}

int main(int argc, char *argv[]) {
    pthread_t threadsID[NUM_THREADS];
    int rc, t, param[NUM_THREADS];

    // Ciclo for para crear los hilos
    for (t = 0; t < NUM_THREADS; t++) {
        std::cout << "In main: creating thread " << t << std::endl;
        param[t] = t;

        rc = pthread_create(&threadsID[t], NULL, PrintHello, (void *)&param[t]);

        if (rc) {
            std::cerr << "ERROR; return code from pthread_create() is " << rc << std::endl;
            exit(-1);
        }
    }

    // Ciclo for para hacer el join de los hilos
    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_join(threadsID[t], NULL);
        if (rc) {
            std::cerr << "ERROR; return code from pthread_join() is " << rc << std::endl;
            exit(-1);
        }
    }
    return 0;
}