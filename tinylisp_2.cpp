#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <stdexcept>
#include <functional>

typedef std::vector<std::string> Tokens;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

int evaluateRPN(Tokens& tokens) {
    std::stack<int> stack;

    for (const std::string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Error: Operador '" + token + "' requiere al menos 2 operandos.");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            if (token == "+") stack.push(b + a);
            else if (token == "-") stack.push(b - a);
            else if (token == "*") stack.push(b * a);
            else if (token == "/") {
                if (a == 0) {
                    throw std::invalid_argument("Error: División por cero.");
                }
                stack.push(b / a);
            }
        } else if (token == "min" || token == "max") {
            if (stack.size() < 2) {
                throw std::invalid_argument("Error: La función '" + token + "' requiere al menos 2 argumentos.");
            }
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            if (token == "min") stack.push(std::min(a, b));
            else if (token == "max") stack.push(std::max(a, b));
        } else {
            stack.push(std::stoi(token));
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Error: Expresión RPN mal formada.");
    }

    return stack.top();
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    Tokens tokens = tokenize(input);
    try {
        int result = evaluateRPN(tokens);
        std::cout << "Resultado: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}