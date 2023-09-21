//
//  Parser.cpp
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#include "Parser.h"
#include <iostream>

namespace Json {

Parser::Parser(const Scanner &scanner) : scanner_(scanner) {}

std::shared_ptr<JsonElement> Parser::parse() {
    std::shared_ptr<JsonElement> element = std::make_shared<JsonElement>();
    Scanner::TokenType token_type = scanner_.scan();
    
    switch(token_type) {
        case Scanner::TokenType::END_OF_SRC:
        case Scanner::TokenType::TOKEN_NULL: {
            break;
        }
            
        case Scanner::TokenType::BEGIN_OBJECT: {
            std::shared_ptr<JsonObject> object = parseObject();
            element->setValue(object);
            break;
        }
            
        case Scanner::TokenType::BEGIN_ARRAY: {
            std::shared_ptr<JsonArray> array = parseArray();
            element->setValue(array);
            break;
        }
            
        case Scanner::TokenType::TOKEN_STRING: {
            std::shared_ptr<std::string> str = std::make_shared<std::string>(scanner_.getTokenStr());
            element->setValue(str);
            break;
        }
            
        case Scanner::TokenType::TOKEN_NUMBER: {
            element->setValue(scanner_.getTokenNum());
            break;
        }
        
        case Scanner::TokenType::TOKEN_TRUE: {
            element->setValue(true);
            break;
        }
            
        case Scanner::TokenType::TOKEN_FALSE: {
            element->setValue(false);
            break;
        }
            
        default:
            break;
    }
    
    return element;
}

std::shared_ptr<JsonObject> Parser::parseObject() {
    std::shared_ptr<JsonObject> obj = std::make_shared<JsonObject>();
    Scanner::TokenType next = scanner_.scan();
    if(next == Scanner::TokenType::END_OBJECT) {
        return obj;
    }
    
    scanner_.Rollback();
    
    while(true) {
        next = scanner_.scan();
        if(next != Scanner::TokenType::TOKEN_STRING) {
            ErrorHandling("key must be string");
        }
        std::string key = scanner_.getTokenStr();
        
        next = scanner_.scan();
        if(next != Scanner::TokenType::TOKEN_SEPARATOR) {
            ErrorHandling("expected ':'");
        }
        (*obj)[key] = parse();
        
        next = scanner_.scan();
        if(next == Scanner::TokenType::END_OBJECT) {
            break;
        }
        if(next != Scanner::TokenType::PAIR_SEPARATOR) {
            ErrorHandling("expected ','");
        }
    }
    
    return obj;
}

std::shared_ptr<JsonArray> Parser::parseArray() {
    std::shared_ptr<JsonArray> arr = std::make_shared<JsonArray>();
    Scanner::TokenType next = scanner_.scan();
    if(next == Scanner::TokenType::END_ARRAY) {
        return arr;
    }
    
    scanner_.Rollback();
    while(true) {
        arr->push_back(parse());
        
        next = scanner_.scan();
        if(next == Scanner::TokenType::END_ARRAY) {
            break;
        }
        if(next != Scanner::TokenType::PAIR_SEPARATOR) {
            ErrorHandling("expected ','");
        }
    }
    return arr;
}
}

