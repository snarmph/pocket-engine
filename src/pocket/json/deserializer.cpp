#include "deserializer.hpp"

#include <iostream>

namespace json {

    Value Deserializer::run() {
        // check if the first token is a {, otherwise print error
        // and return null
        if(tokens[current].type == TokenType::LEFT_BRACE) {
            return createObject();
        }
        else
            std::cout << "ERROR, json needs to start with a {\n";

        return Value();
    }

    Value Deserializer::createObject() {
        // create empty object
        Value result = Object();
        
        // recurse until it finishes object
        while(tokens[current].type != TokenType::RIGHT_BRACE) {
            
            // get next key
            std::string key = tokens[++current].as_string(text);

            // travel to next value (skip [:])
            current += 2;

            // check what type the value is
            switch(tokens[current].type) {
                case TokenType::LEFT_BRACE:     result[key] = createObject();   break;
                case TokenType::STRING:         result[key] = createString();   break;
                case TokenType::NUMBER:         result[key] = createNumber();   break;
                case TokenType::BOOLEAN:        result[key] = createBoolean();  break;
                case TokenType::JSONNULL:       result[key] = Value();          break;
                case TokenType::LEFT_BRACKET:   result[key] = createArray();    break;
                
                default:
                    std::cout << "unexpected tokens: [ " << tokens[current].as_string(text) << " ]\n";
                    exit(1);
            }

            current++;
        }
        
        return result;
    }

    std::string Deserializer::createString() {
        return tokens[current].as_string(text);
    }

    double Deserializer::createNumber() {
        return std::stod(tokens[current].as_string(text));
    }

    bool Deserializer::createBoolean() {
        return tokens[current].as_string(text) == "true";
    }

    Array Deserializer::createArray() {
        Array result;

        while(tokens[++current].type != TokenType::RIGHT_BRACKET) {
            // check what type the value is
            switch(tokens[current].type) {
                case TokenType::LEFT_BRACE:     result.push_back(createObject());   break;
                case TokenType::STRING:         result.push_back(createString());   break;
                case TokenType::NUMBER:         result.push_back(createNumber());   break;
                case TokenType::BOOLEAN:        result.push_back(createBoolean());  break;
                case TokenType::JSONNULL:       result.push_back(Value());          break;
                case TokenType::LEFT_BRACKET:   result.push_back(createArray());    break;
                case TokenType::COMMA:          continue;                           break;

                default:
                    std::cout << "unexpected tokens: [ " << tokens[current].as_string(text) << " ]\n";
                    exit(1);
            }
        }

        return result;
    }

}