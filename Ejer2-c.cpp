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
    pthread_t threadID;
    int rc, param;

    // Ciclo for que crea el hilo y hace el join en el mismo ciclo
    for (int t = 0; t < NUM_THREADS; t++) {
        std::cout << "In main: creating thread " << t << std::endl;
        param = t;

        rc = pthread_create(&threadID, NULL, PrintHello, (void *)&param);

        if (rc) {
            std::cerr << "ERROR; return code from pthread_create() is " << rc << std::endl;
            exit(-1);
        }

        // Join del hilo inmediatamente después de crearlo
        rc = pthread_join(threadID, NULL);
        if (rc) {
            std::cerr << "ERROR; return code from pthread_join() is " << rc << std::endl;
            exit(-1);
        }
    }
    return 0;
}