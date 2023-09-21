//
//  JsonElement.cpp
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#include "JsonElement.h"
#include "ErrorHandling.h"

#include <iostream>
#include <sstream>

namespace Json {
JsonElement::JsonElement() : type_(Type::JSON_NULL) {}

JsonElement::~JsonElement() {}

void JsonElement::setValue(std::shared_ptr<JsonObject> token_object) {
    type_ = Type::JSON_OBJECT;
    token_ = token_object;
}

void JsonElement::setValue(std::shared_ptr<JsonArray> token_array) {
    type_ = Type::JSON_ARRAY;
    token_ = token_array;
}

void JsonElement::setValue(std::shared_ptr<std::string> token_string) {
    type_ = Type::JSON_STRING;
    token_ = token_string;
}

void JsonElement::setValue(double token_number) {
    type_ = Type::JSON_NUMBER;
    token_ = token_number;
}

void JsonElement::setValue(bool token_bool) {
    type_ = Type::JSON_BOOL;
    token_ = token_bool;
}

std::string JsonElement::toStr() {
    std::stringstream ss;
    
    switch(type_) {
        case Type::JSON_OBJECT: {
            std::shared_ptr<JsonObject> token = std::get<std::shared_ptr<JsonObject>>(token_);
            ss << *token;
            break;
        }
        
        case Type::JSON_ARRAY: {
            std::shared_ptr<JsonArray> token = std::get<std::shared_ptr<JsonArray>>(token_);
            ss << *token;
            break;
        }

        case Type::JSON_STRING: {
            ss << "\"" << *std::get<std::shared_ptr<std::string>>(token_) << "\"";
            break;
        }

        case Type::JSON_NUMBER: {
            ss << std::get<double>(token_);
            break;
        }

        case Type::JSON_BOOL: {
            ss << (std::get<bool>(token_) == true ? "true" : "false");
            break;
        }

        case Type::JSON_NULL: {
            ss << "null";
            break;
        }
            
        default:
            break;
    }
    
    return ss.str();
}

std::ostream & operator << (std::ostream &os, const JsonObject &object) {
    os << "{";
    for(auto iter = object.begin(); iter != object.end(); ++iter) {
        os << "\"" << iter->first << "\": " << iter->second->toStr();
        if(iter != std::prev(object.end())) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

std::ostream & operator << (std::ostream &os, const JsonArray &array) {
    os << "[";
    for(size_t i = 0; i < array.size(); ++i) {
        os << array[i]->toStr();
        if(i != array.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
}
