#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <stdexcept>

// Define un tipo para representar las expresiones
typedef std::vector<std::string> Expression;

// Función para dividir una expresión en tokens
Expression tokenize(const std::string& input) {
    Expression tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}
// Función para evaluar una expresión
int evaluate(Expression& tokens) {
    std::stack<int> stack;

    for (const std::string &token: tokens)
        if (token == "+") {
            if (stack.size() < 2) {
                throw std::runtime_error("Faltan operandos para +");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "") {
            if (stack.size() < 2) {
                throw std::runtime_error("Faltan operandos para");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        } else {
            stack.push(std::stoi(token));
        }


    if (stack.size() != 1) {
        throw std::runtime_error("La expresión no está bien formada");
    }

    return stack.top();
}
int main() {
    try {
        std::string input;
        std::cout << "Ingrese una expresión (por ejemplo, 3 4 + 5 ): ";
        std::getline(std::cin, input);
        Expression tokens = tokenize(input);
        int result = evaluate(tokens);
        std::cout << "Resultado: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
int main() {
    try {
        std::string input;
        std::cout << "Ingrese una expresión (por ejemplo, 3 4 + 5): ";
        std::getline(std::cin, input);
        Expression tokens = tokenize(input);
        int result = evaluate(tokens);
        std::cout << "Resultado: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
