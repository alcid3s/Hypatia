#ifndef TOKENISER
#define TOKENISER

#include <string>
#include <vector>

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

    public:
        Tokeniser();
        ~Tokeniser();
};

#endif