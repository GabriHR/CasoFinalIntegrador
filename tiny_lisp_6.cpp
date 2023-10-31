#include <iostream>

int suma(int a, int b) {
    return a + b;
}

int multiplicacion(int a, int b) {
    return a * b;
}

int main() {
    int valor1, valor2;
    char operacion;

    std::cout << "Ingrese el primer valor: ";
    std::cin >> valor1;

    std::cout << "Ingrese el segundo valor: ";
    std::cin >> valor2;

    std::cout << "Ingrese la operacion (+ para suma, * para multiplicacion): ";
    std::cin >> operacion;

    int resultado;

    if (operacion == '+') {
        resultado = suma(valor1, valor2);
    } else if (operacion == '*') {
        resultado = multiplicacion(valor1, valor2);
    } else {
        std::cout << "Operación no válida. Por favor, ingrese + o *." << std::endl;
        return 1; // Salir del programa con un código de error
    }

    std::cout << "El resultado de la operacion es: " << resultado << std::endl;

  return 0;
}