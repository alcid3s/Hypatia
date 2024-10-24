#include "Tokeniser.h"
#include <iostream>

Tokeniser::Tokeniser() {
}

Tokeniser::~Tokeniser() {
}

std::string Tokeniser::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::LITERAL: return "LITERAL";
        case TokenType::OPERATOR: return "OPERATOR";
        case TokenType::PUNCTUATION: return "PUNCTUATION";
        case TokenType::SYMBOL: return "SYMBOL";
        default: return "UNKNOWN";
    }
}

bool Tokeniser::is_keyword(std::string symbol) {
    return symbol == "int" || symbol == "char" || symbol == "float" || symbol == "double" || symbol == "void";
}

bool Tokeniser::is_operator(std::string symbol) {
    return symbol == "=" || symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "%" || symbol == "++" || symbol == "--" || symbol == "==" || symbol == "!=" || symbol == ">" || symbol == "<" || symbol == ">=" || symbol == "<=" || symbol == "&&" || symbol == "||" || symbol == "!" || symbol == "&" || symbol == "|" || symbol == "^" || symbol == "~" || symbol == "<<" || symbol == ">>";
}

bool Tokeniser::is_punctuation(std::string symbol) {
    return symbol == "{" || symbol == "}" || symbol == "(" || symbol == ")" || symbol == "[" || symbol == "]" || symbol == ";" || symbol == ",";
}

bool Tokeniser::is_identifier(std::string symbol) {
    return !this->is_keyword(symbol) && !this->is_operator(symbol) && !this->is_punctuation(symbol);
}

bool Tokeniser::is_literal(std::string symbol) {
    return std::all_of(symbol.begin(), symbol.end(), ::isdigit);
}

Token Tokeniser::identify_token(std::string symbol) {
    Token token;

    // Yeah... I don't like this either
    if(this->is_keyword(symbol)) {
        token.type = TokenType::KEYWORD;
    } else if(this->is_operator(symbol)) {
        token.type = TokenType::OPERATOR;
    } else if(this->is_punctuation(symbol)) {
        token.type = TokenType::PUNCTUATION;
    } else if(this->is_literal(symbol)) {
        token.type = TokenType::LITERAL;
    } else if(this->is_identifier(symbol)) {
        token.type = TokenType::IDENTIFIER;
    } else {
        token.type = TokenType::SYMBOL;
    }
    token.value = symbol;
    return token;
}

std::vector<std::string> Tokeniser::analyse_line(std::string line) {
    std::vector<std::string> line_symbols;
    bool bracket = false;
    bool quote = false;
    for (size_t i = 0, end = 0; i < line.length(); i++) {
       char character = line[i];
       if(character == '\"') {
            bracket = !bracket;
            std::string symbol = line.substr(end, (bracket ? i - end : i - end + 1));
            end = i;
            line_symbols.push_back(symbol);
            //std::cout << "before or after string symbol: " << symbol << "\n";
       } else if(character == '\'') {
            quote = !quote;
            std::string symbol = line.substr(end, (quote ? i - end : i - end + 1));
            end = i;
            line_symbols.push_back(symbol);
            //std::cout << "before quote symbol: " << symbol << "\n";
       }

       if(!bracket && !quote) {
            if(character == ' ' || character == '\n' || character == '\t') {
                std::string symbol = line.substr(end, i - end);
                std::remove_if(symbol.begin(), symbol.end(), isspace);
                end = i + 1;
                if(!symbol.empty()) {
                    line_symbols.push_back(symbol);
                    //std::cout << "symbol: " << symbol << "\n";
                }
            } else if(character == ';' || character == '{' || character == '}') {
                std::string symbol = line.substr(end, i - end + 1);
                end = i + 1;
                line_symbols.push_back(symbol);
                //std::cout << "delimiter symbol: " << symbol << "\n";
            }
       }
    }
    return line_symbols;
}

std::vector<std::vector<std::string>> Tokeniser::analyse(std::ifstream &file) {
    std::vector<std::vector<std::string>> file_symbols;
    if(file.is_open()) {
        // Get content from file
        std::string content((std::istreambuf_iterator<char>(file) ),(std::istreambuf_iterator<char>()));
        
        // space content by ;, { and }
        std::vector<std::string> lines;
        for (size_t i = 0, end = 0; i < content.length(); i++) {
           if(content[i] == ';' || content[i] == '{' || content[i] == '}') {
                std::string substr = content.substr(end, i - end + 1);
                end = i + 1;
                lines.push_back(substr);
           }
        }
        
        // identify symbol by space
        for (size_t i = 0; i < lines.size(); i++) {
            std::string line = lines[i];
            auto line_symbols = this->analyse_line(line);
            file_symbols.push_back(line_symbols);
        }
    }
    return file_symbols;
}

std::vector<Token> Tokeniser::tokenise(std::vector<std::vector<std::string>> symbols) {
    std::vector<Token> tokens;
    std::vector<std::string> line_symbols;

    // for every line with symbols
    for (size_t i = 0; i < symbols.size(); i++){
        line_symbols = symbols[i];

        // for every symbol in line
        for (size_t j = 0; j < line_symbols.size(); j++) {
            std::string symbol = line_symbols[j];
            Token token = this->identify_token(symbol);
            std::string tokenType = this->tokenTypeToString(token.type);
            std::cout << "------------------------\nToken: \"" << token.value << "\" Type: \"" << tokenType << "\"\n------------------------------------\n\n";
            tokens.push_back(token);
        }
    }
    return tokens;
}