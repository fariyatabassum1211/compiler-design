#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm> // For std::all_of
#include <set>       // For std::set

// --- Keyword Definitions ---
const std::set<std::string> KEYWORDS = {
    "int", "char", "float", "double", "void", "return", "if",
    "else", "while", "for", "do", "break", "continue", "main"
};

bool isKeyword(const std::string& str) {
    return KEYWORDS.count(str) > 0;
}

// --- Utility Functions ---

bool isDelimiter(char c) {
    // Contains all operators and separators
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' ||
            c == '(' || c == ')' || c == '{' || c == '}' || c == ';' ||
            c == ',' || c == '<' || c == '>');
}

bool isValidIdentifier(const std::string &str) {
    if (str.empty() || (!isalpha(str[0]) && str[0] != '_')) {
        return false;
    }
    for (size_t i = 1; i < str.length(); i++) {
        if(!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return true;
}

bool isNumericConstant(const std::string& input) {
    // Note: This only checks for non-negative integers
    for (char c : input) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// --- Classification Logic ---

void classifyToken(const std::string& token) {
    if (token.empty()) {
        return;
    }

    if (isKeyword(token)) {
        std::cout << token << " is a Keyword" << std::endl;
        return;
    }

    // Check if the token is a single-character arithmetic operator
    if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
                             token[0] == '/' || token[0] == '%' || token[0] == '=')) {
        std::cout << token << " is an Arithmetic Operator" << std::endl;
    } else if (isNumericConstant(token)) {
        std::cout << token << " is a Numeric Constant" << std::endl;
    } else if (isValidIdentifier(token)) {
        std::cout << token << " is a Valid Identifier" << std::endl;
    } else {
        std::cout << token << " is an Unknown Token" << std::endl;
    }
}

// --- Tokenization Logic ---

void tokenizeAndClassify(const std::string& line) {
    std::string token = "";
    for (size_t i = 0; i < line.size(); ++i) {
        char currentChar = line[i];

        // 1. String Literal Handler
        if (currentChar == '"') {
            classifyToken(token);
            token = "";

            size_t j = i + 1;
            std::string literal = "\"";

            while (j < line.size() && line[j] != '"') {
                literal += line[j];
                j++;
            }

            if (j < line.size() && line[j] == '"') {
                literal += line[j];
                std::cout << literal << " is a String Literal" << std::endl;
                i = j;
            } else {
                std::cout << literal << " is an Unknown Token (Unclosed String)" << std::endl;
                i = j - 1;
            }
            continue;
        }

        // 2. Whitespace Handler
        if (isspace(currentChar)) {
            classifyToken(token);
            token = "";
            continue;
        }

        // 3. Delimiter Handler
        if (isDelimiter(currentChar)) {
            classifyToken(token);
            token = "";

            // Classify the delimiter itself
            if (currentChar == '+' || currentChar == '-' || currentChar == '*' ||
                currentChar == '/' || currentChar == '%' || currentChar == '=') {
                std::cout << currentChar << " is an Arithmetic Operator" << std::endl;
            } else if (currentChar == '<' || currentChar == '>') {
                std::cout << currentChar << " is a Comparison/Stream Operator" << std::endl;
            } else {
                std::cout << currentChar << " is a Separator/Delimiter" << std::endl;
            }
            continue;
        }

        // 4. Accumulation
        token += currentChar;
    }

    classifyToken(token);
}

// --- Main Execution ---

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file 'input.txt'. Make sure it exists." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {

        // Skip lines that are empty or contain only whitespace
        if (line.empty() || std::all_of(line.begin(), line.end(), ::isspace)) {
            continue;
        }

        std::cout << "\nProcessing line: " << line << std::endl;
        tokenizeAndClassify(line);
    }

    inputFile.close();
    return 0;
}
