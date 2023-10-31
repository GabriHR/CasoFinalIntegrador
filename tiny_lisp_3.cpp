#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <unordered_map>
#include <algorithm>

enum TokenType {
    NUMBER,
    OPERATOR,
    VARIABLE
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, std::string v) : type(t), value(std::move(v)) {}
};

using Tokens = std::vector<Token>;

Tokens tokenize(const std::string& input) {
    Tokens tokens;
    std::string token;
    std::istringstream stream(input);

    while (stream >> token) {
        tokens.emplace_back(NUMBER, std::move(token));
    }

    return tokens;
}

Tokens categorizeTokens(const Tokens& tokens) {
    Tokens categorizedTokens;

    for (const auto& token : tokens) {
        if (token.value == "+" || token.value == "-" || token.value == "*" || token.value == "/" ||
            token.value == "min" || token.value == "max") {
            categorizedTokens.emplace_back(OPERATOR, token.value);
        } else if (std::isdigit(token.value[0]) || (token.value[0] == '-' && std::isdigit(token.value[1]))) {
            categorizedTokens.emplace_back(NUMBER, token.value);
        } else {
            categorizedTokens.emplace_back(VARIABLE, token.value);
        }
    }

    return categorizedTokens;
}

int evaluate(Tokens tokens, std::unordered_map<std::string, int>& variables) {
    std::stack<int> stack;

    while (!tokens.empty()) {
        Token token = tokens.back();
        tokens.pop_back();

        if (token.type == NUMBER) {
            stack.push(std::stoi(token.value));
        } else if (token.type == VARIABLE) {
            // Check if the variable is defined
            if (variables.find(token.value) != variables.end()) {
                stack.push(variables[token.value]);
            } else {
                std::cerr << "Error: Undefined variable '" << token.value << "'\n";
                return 0;
            }
        } else if (token.type == OPERATOR) {
            if (token.value == "+") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for operator '+'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                stack.push(a + b);
            } else if (token.value == "-") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for operator '-'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                stack.push(b - a);
            } else if (token.value == "*") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for operator '*'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                stack.push(a * b);
            } else if (token.value == "/") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for operator '/'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                if (a != 0) {
                    stack.push(b / a);
                } else {
                    std::cerr << "Error: Division by zero\n";
                    return 0;
                }
            } else if (token.value == "min") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for 'min'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                stack.push(std::min(a, b));
            } else if (token.value == "max") {
                if (stack.size() < 2) {
                    std::cerr << "Error: Insufficient operands for 'max'\n";
                    return 0;
                }
                int a = stack.top();
                stack.pop();
                int b = stack.top();
                stack.pop();
                stack.push(std::max(a, b));
            }
        }
    }

    if (stack.size() == 1) {
        return stack.top();
    } else {
        std::cerr << "Error: Invalid expression\n";
        return 0;
    }
}

int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    Tokens rawTokens = tokenize(input);
    Tokens tokens = categorizeTokens(rawTokens);

    std::unordered_map<std::string, int> variables;

    // Example: let x = 5
    variables["x"] = 5;

    int result = evaluate(tokens, variables);
    if (result != 0) {
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}
