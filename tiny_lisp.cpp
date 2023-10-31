// Description: Pequeño intérprete de Lisp. Implementa las funciones + y * y permite definir y llamar funciones.
// Version: 0.1
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <functional>
#include <stdexcept>

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

// Definición de un entorno para almacenar funciones y variables globales
struct Environment {
    std::stack<int> stack;
    std::map<std::string, std::function<void(Environment&)>> functions;
};

void define_function(Environment& env, const std::string& name, std::function<void(Environment&)> func) {
    env.functions[name] = func;
}

void call_function(Environment& env, const std::string& name) {
    if (env.functions.find(name) != env.functions.end()) {
        env.functions[name](env);
    } else {
        throw std::runtime_error("Función no definida: " + name);
    }
}

int evaluate(Environment& env, Tokens& tokens) {
    while (!tokens.empty()) {
        std::string token = tokens.back();
        tokens.pop_back();

        if (token == "+") {
            int a = env.stack.top();
            env.stack.pop();
            int b = env.stack.top();
            env.stack.pop();
            env.stack.push(a + b);
        } else if (token == "*") {
            int a = env.stack.top();
            env.stack.pop();
            int b = env.stack.top();
            env.stack.pop();
            env.stack.push(a * b);
        } else if (token == "define") {
            if (tokens.empty()) {
                throw std::runtime_error("Falta el nombre de la variable en la definición.");
            }
            std::string var_name = tokens.back();
            tokens.pop_back();
            if (tokens.empty()) {
                throw std::runtime_error("Falta el valor de la variable en la definición.");
            }
            int var_value = std::stoi(tokens.back());
            tokens.pop_back();
            env.functions[var_name] = [var_value, &env](Environment& local_env) {
                local_env.stack.push(var_value);
            };
        } else if (token == "call") {
            if (tokens.empty()) {
                throw std::runtime_error("Falta el nombre de la función en la llamada.");
            }
            std::string func_name = tokens.back();
            tokens.pop_back();
            call_function(env, func_name);
        } else {
            env.stack.push(std::stoi(token));
        }
    }

    if (env.stack.size() != 1) {
        throw std::runtime_error("Expresión mal formada.");
    }

    return env.stack.top();
}

int main() {
    Environment env;

    define_function(env, "dup", [](Environment& env) {
        int value = env.stack.top();
        env.stack.push(value);
    });

    try {
        std::string input;
        std::getline(std::cin, input);
        Tokens tokens = tokenize(input);
        std::cout << evaluate(env, tokens) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}