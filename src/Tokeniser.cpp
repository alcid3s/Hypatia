#include "Tokeniser.h"
#include <iostream>

Tokeniser::Tokeniser() {
}

Tokeniser::~Tokeniser() {
}

void Tokeniser::tokenise(std::ifstream &file) {
    std::string line;
     if(file.is_open()) {
        while(getline(file, line)) {
            for (size_t i = 0, end = 0; i < line.length(); i++){
                if (line[i] == ' '){
                    std::string substr = line.substr(end, i - end);
                    std::remove_if(substr.begin(), substr.end(), isspace);
                    end = i + 1;
                    if(!substr.empty())
                        std::cout << "substr: " << substr << "\n";
                } else if(line[i] == '{' || line[i] == '}' || isdigit(line[i])) {
                    char substr = line[i];
                    end = i + 1;
                    std::cout << "substr: " << substr << "\n";
                }
            }
        }
    }
}

