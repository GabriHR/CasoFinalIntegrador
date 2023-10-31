//
// Created by Jaime on 31/10/2023.
//
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

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

int evaluate(Tokens& tokens) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (token == "+") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a + b);
        } else if (token == "*") {
            int a = stack.top();
            stack.pop();
            int b = stack.top();
            stack.pop();
            stack.push(a * b);
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.top();
}

int main() {
    while (true) {
        std::string input;
        std::cout << "Ingresa una expresion o escribe 'salir' para terminar: ";
        std::getline(std::cin, input);

        if (input == "salir") {
            break;
        }

        Tokens tokens = tokenize(input);
        int result = evaluate(tokens);
        std::cout << "Resultado: " << result << std::endl;
    }

    return 0;
}
