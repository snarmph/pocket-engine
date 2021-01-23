#pragma once
#include <string>
#include <vector>
#include <map>

#include "token.hpp"
#include "value.hpp"

namespace json {

    class Parser {
    public:
        Value parse(std::string jsonstring);

        std::string getText();

    private:
        void scanToken();
        void addToken(TokenType type);

        bool isDigit(char c);
        bool isAlpha(char c);

        void addNumber();
        void addString();
        void addOther();

        bool isAtEnd();
        char peek();
        char peekNext();

        std::vector<Token> tokens;
        size_t start = 0;
        size_t current = 0;

        std::string text = "";
    };

}