#ifndef TOKEN_H
#define TOKEN_H

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    SYMBOL,
    PUNCTUATION
};

struct Token {
    TokenType type;
    std::string value;
};

#endif