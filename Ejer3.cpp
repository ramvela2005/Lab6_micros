#include <iostream>
#include <pthread.h>
#include <vector>
#include <cmath>

struct ThreadData {
    int n;
    double result;
};

// Función que será ejecutada por cada hilo
void* calculateTerm(void* arg) {
    ThreadData* data = static_cast<ThreadData*>(arg);
    int n = data->n;
    data->result = pow(-1, n+1) / static_cast<double>(n);
    return nullptr;
}

int main() {
    int max_n;

    // Solicitar el valor máximo de 'n' al usuario
    std::cout << "Ingrese el valor máximo de n: ";
    std::cin >> max_n;

    // Crear un vector para almacenar los identificadores de hilos
    std::vector<pthread_t> threads(max_n);
    std::vector<ThreadData> thread_data(max_n);

    // Crear hilos, uno por cada término de la serie
    for (int i = 1; i <= max_n; ++i) {
        thread_data[i-1].n = i;
        pthread_create(&threads[i-1], nullptr, calculateTerm, &thread_data[i-1]);
    }

    // Esperar a que todos los hilos terminen y sumar los resultados
    double sum = 0.0;
    for (int i = 0; i < max_n; ++i) {
        pthread_join(threads[i], nullptr);
        sum += thread_data[i].result;
    }

    // Imprimir el resultado final
    std::cout << "El valor de convergencia de la serie es: " << sum << std::endl;

    return 0;
}
