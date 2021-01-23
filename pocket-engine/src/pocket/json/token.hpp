#pragma once

#include <string>

namespace json {
    enum class TokenType {
        NOTHING,

        // object
        LEFT_BRACE, RIGHT_BRACE, COLON, 
        COMMA, DOT,
        // array
        LEFT_BRACKET, RIGHT_BRACKET,
        // value
        DOUBLE_QUOTES, NUMBER, STRING,
        BOOLEAN, JSONNULL
    };

    const char* typeToString(TokenType type);

    struct Token {
        TokenType type = TokenType::NOTHING;
        size_t start = 0, end = 0;

        Token() {}
        Token(TokenType type, size_t start, size_t end) {
            this->type = type;
            this->start = start;
            this->end = end;
        }

        inline std::string as_string(std::string& text) {
            if(type == TokenType::STRING)
                return text.substr(start+1, end-start-2);
            else
                return text.substr(start, end-start);
        }

        std::string to_string(std::string& text) {
            return  std::string(typeToString(type)) + 
                    std::string(": ") + 
                    as_string(text);
        }
    };

    inline const char* typeToString(TokenType type) {
        switch(type) {
            case TokenType::NOTHING:        return "NOTHING"; break;
            case TokenType::LEFT_BRACE:     return "LEFT_BRACE"; break;
            case TokenType::RIGHT_BRACE:    return "RIGHT_BRACE"; break;
            case TokenType::COLON:          return "COLON"; break;
            case TokenType::COMMA:          return "COMMA"; break;
            case TokenType::DOT:            return "DOT"; break;
            case TokenType::LEFT_BRACKET:   return "LEFT_BRACKET"; break;
            case TokenType::RIGHT_BRACKET:  return "RIGHT_BRACKET"; break;
            case TokenType::DOUBLE_QUOTES:  return "DOUBLE_QUOTES"; break;
            case TokenType::NUMBER:         return "NUMBER"; break;
            case TokenType::STRING:         return "STRING"; break;
            case TokenType::BOOLEAN:        return "BOOLEAN"; break;
            case TokenType::JSONNULL:       return "JSONNULL"; break;
        }
        return "ERROR";
    }

}