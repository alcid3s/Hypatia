#ifndef TOKENISER_H
#define TOKENISER_H

#include <string>
#include <vector>
#include <fstream>
#include "Token.h"


class Tokeniser {
    private:
        //debug / logging
        std::string tokenTypeToString(TokenType type);

        // identify symbol
        bool is_keyword(std::string symbol);
        bool is_operator(std::string symbol);
        bool is_punctuation(std::string symbol);
        bool is_literal(std::string symbol);
        bool is_identifier(std::string symbol);
        bool is_symbol(std::string symbol);
        Token identify_token(std::string string);

        std::vector<std::string> analyse_line(std::string line);
    public:
        Tokeniser();
        ~Tokeniser();

        std::vector<std::vector<std::string>> analyse(std::ifstream &file);
        std::vector<Token> tokenise(std::vector<std::vector<std::string>> symbols);
};

#endif