#ifndef TOKENISER_H
#define TOKENISER_H

#include <string>
#include <vector>
#include <fstream>
#include "Token.h"


class Tokeniser {
    private:
        std::vector<Token> tokens;

        Token identify_token(std::string string);
        std::vector<int> identify_delimeter(std::string line, char delimiter);
        std::vector<std::string> analyse_default_line(std::string line);
        std::vector<std::string> analyse_delimiter_line(std::string line);

    public:
        Tokeniser();
        ~Tokeniser();

        std::vector<std::vector<std::string>> analyse(std::ifstream &file);
        void tokenise(std::vector<std::vector<std::string>> symbols);
};

#endif