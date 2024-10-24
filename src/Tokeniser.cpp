#include "Tokeniser.h"
#include <iostream>

Tokeniser::Tokeniser() {
}

Tokeniser::~Tokeniser() {
}

std::vector<std::string> Tokeniser::analyse_default_line(std::string line) {
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
            std::cout << "before or after string symbol: " << symbol << "\n";
       } else if(character == '\'') {
            quote = !quote;
            std::string symbol = line.substr(end, (quote ? i - end : i - end + 1));
            end = i;
            line_symbols.push_back(symbol);
            std::cout << "before quote symbol: " << symbol << "\n";
       }

       if(!bracket && !quote) {
            if(character == ' ' || character == '\n' || character == '\t') {
                std::string symbol = line.substr(end, i - end);
                std::remove_if(symbol.begin(), symbol.end(), isspace);
                end = i + 1;
                if(!symbol.empty()) {
                    line_symbols.push_back(symbol);
                    std::cout << "symbol: " << symbol << "\n";
                }
            } else if(character == ';' || character == '{' || character == '}') {
                std::string symbol = line.substr(end, i - end + 1);
                end = i + 1;
                line_symbols.push_back(symbol);
                std::cout << "delimiter symbol: " << symbol << "\n";
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
            auto line_symbols = this->analyse_default_line(line);
            file_symbols.push_back(line_symbols);
        }
    }
    return file_symbols;
}

void Tokeniser::tokenise(std::vector<std::vector<std::string>> symbols) {
    std::vector<Token> tokens;
    std::vector<std::string> line_symbols;
    for (size_t i = 0; i < symbols.size(); i++){
        line_symbols = symbols[i];
    }
}