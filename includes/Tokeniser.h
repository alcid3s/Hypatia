#ifndef TOKENISER
#define TOKENISER

#include <string>
#include <vector>
#include <fstream>

enum class TokenType {
    _if,
    _elif,
    _else,
    _while,
    _for,
    _open_param,
    _close_param,
    _function,
    _return,
    _var_type,
};

struct Token {
    TokenType type;
    std::string value;
};

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