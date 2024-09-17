#include <iostream>
#include <pthread.h>
#include <vector>

struct FibonacciArgs {
    int n;              // Índice del número de Fibonacci que se quiere calcular
    long long result;   // Resultado del cálculo del número de Fibonacci
    long long prev1;    //El valor de F(n-1), el numeros anerior de la serie
    long long prev2;    //Valor de F(n-2) dos numeros atras de la serie
};

//Esta funcion sera ejecutada por los hilos para calcular

void* calcularFibonacci(void* args) {
    FibonacciArgs* fibArgs = (FibonacciArgs*)args;  //Convertir los argumentos
    int n = fibArgs->n;     //obtiene el indice n

    // Calcular el valor de Fibonacci según el índice n

    if (n == 0) {
        fibArgs->result = 0;
        fibArgs->prev1 = 0;
        fibArgs->prev2 = 0;
    } else if (n == 1) {
        fibArgs->result = 1;
        fibArgs->prev1 = 1;
        fibArgs->prev2 = 0;
    } else {
        fibArgs->result = fibArgs->prev1 + fibArgs->prev2;
        fibArgs->prev2 = fibArgs->prev1;
        fibArgs->prev1 = fibArgs->result;
    }

    pthread_exit(nullptr);
}

int main() {
    int limite;

    std::cout << "Ingrese un número entre 0 y 100: ";
    std::cin >> limite;

    if (limite < 0 || limite > 100) {
        std::cerr << "El número debe estar entre 0 y 100." << std::endl;
        return 1;
    }

    // Crear un vector para almacenar los identificadores de los hilos

    std::vector<pthread_t> threads(limite + 1);
    
    // Crear un vector para almacenar los argumentos de Fibonacci para cada hilo
    
    std::vector<FibonacciArgs> fibArgs(limite + 1);

    // Inicializar los primeros dos elementos de la serie
    fibArgs[0].n = 0;
    fibArgs[1].n = 1;
    fibArgs[0].prev1 = 0;
    fibArgs[0].prev2 = 0;
    fibArgs[1].prev1 = 1;
    fibArgs[1].prev2 = 0;

    // Crear los hilos para calcular cada número de Fibonacci
    for (int i = 0; i <= limite; ++i) {
        if (i > 1) {
            fibArgs[i].n = i;
            fibArgs[i].prev1 = fibArgs[i - 1].prev1;
            fibArgs[i].prev2 = fibArgs[i - 1].prev2;
        }
        pthread_create(&threads[i], nullptr, calcularFibonacci, (void*)&fibArgs[i]);
        pthread_join(threads[i], nullptr);
    }

    long long sumaTotal = 0; // Variable para acumular la suma de los resultados de Fibonacci


    // Imprimir los resultados de manera amigable
    for (int i = 0; i <= limite; ++i) {
        std::cout << i + 1 << ". F" << i << " = ";
        if (i == 0) {
            std::cout << "0" << std::endl;
        } else if (i == 1) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "F" << i-1 << " + F" << i-2 << " = " << fibArgs[i-1].result << " + " << fibArgs[i-2].result << " = " << fibArgs[i].result << std::endl;
        }
        sumaTotal += fibArgs[i].result;
    }

    // Imprimir la suma total de los números de Fibonacci calculados

    std::cout << "La suma total de los números de Fibonacci entre 0 y " << limite << " es: " << sumaTotal << std::endl;

    return 0;
}
