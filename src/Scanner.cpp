//
//  Scanner.cpp
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#include "Scanner.h"
#include "ErrorHandling.h"

namespace Json {

Scanner::Scanner(const std::string &src) : src_(src), idx_(0) {}

std::ostream & operator << (std::ostream &os, const Scanner::TokenType type) {
    switch(type) {
        case Scanner::TokenType::END_OF_SRC:        os << "EOF";    break;
        case Scanner::TokenType::BEGIN_OBJECT:      os << "{";      break;
        case Scanner::TokenType::END_OBJECT:        os << "}";      break;
        case Scanner::TokenType::BEGIN_ARRAY:       os << "[";      break;
        case Scanner::TokenType::END_ARRAY:         os << "]";      break;
            
        case Scanner::TokenType::TOKEN_STRING:      os << "string"; break;
        case Scanner::TokenType::TOKEN_NUMBER:      os << "number"; break;
        case Scanner::TokenType::TOKEN_TRUE:        os << "true";   break;
        case Scanner::TokenType::TOKEN_FALSE:       os << "false";  break;
        case Scanner::TokenType::TOKEN_NULL:        os << "null";   break;
        case Scanner::TokenType::PAIR_SEPARATOR:    os << ",";      break;
        case Scanner::TokenType::TOKEN_SEPARATOR:   os << ":";      break;
        default:
            break;
    }
    return os;
}

Scanner::TokenType Scanner::scan() {
    if(isEnd()) {
        return TokenType::END_OF_SRC;
    }
    
    prev_idx_ = idx_;
    
    char c = step();
    switch(c) {
        case '{':
            return TokenType::BEGIN_OBJECT;
        case '}':
            return TokenType::END_OBJECT;
        case '[':
            return TokenType::BEGIN_ARRAY;
        case ']':
            return TokenType::END_ARRAY;
        case '"':
            scanString();
            return TokenType::TOKEN_STRING;
        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            scanNumber();
            return TokenType::TOKEN_NUMBER;
        case 't':
            scanTrue();
            return TokenType::TOKEN_TRUE;
        case 'f':
            scanFalse();
            return TokenType::TOKEN_FALSE;
        case 'n':
            scanNull();
            return TokenType::TOKEN_NULL;
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            return scan();
        case ',':
            return TokenType::PAIR_SEPARATOR;
        case ':':
            return TokenType::TOKEN_SEPARATOR;
        default:
            ErrorHandling("unsupported token: " + std::string(1, c));
            return TokenType::ERROR;
    }
}

std::string Scanner::getTokenStr() {
    return token_str_;
}

double Scanner::getTokenNum() {
    return token_num_;
}

void Scanner::Rollback() {
    idx_ = prev_idx_;
}

bool Scanner::isEnd() {
    return idx_ >= src_.size();
}
char Scanner::step() {
    if(idx_ >= src_.size()) {
        ErrorHandling("attempted to read beyond the end of the string");
    }
    return src_[idx_++];
}

void Scanner::scanTrue() {
    if(src_.compare(idx_, 3, "rue") == 0) {
        idx_ += 3;
    }
    else {
        ErrorHandling("scan true error");
    }
}

void Scanner::scanFalse() {
    if(src_.compare(idx_, 4, "alse") == 0) {
        idx_ += 4;
    }
    else {
        ErrorHandling("scan false error");
    }
}

void Scanner::scanNull() {
    if(src_.compare(idx_, 3, "ull") == 0) {
        idx_ += 3;
    }
    else {
        ErrorHandling("scan null error");
    }
}

void Scanner::scanString() {
    size_t i = idx_;
    
    // scan until meet a colon or reach the end of json file
    while(getTokenChar() != '"' && !isEnd()) {
        if(getTokenChar() == '\\' && getNextTokenChar() == '"') {
            step();
        }
        step();
    }
    
    // scanning should stop due to the colon, otherwise means the json syntax error
    if(isEnd()) {
        ErrorHandling("missing closing quote");
    }
    
    step();
    token_str_ = src_.substr(i, idx_ - i - 1);
    
    // replace escaped double quotes with regular double quotes
    size_t found = token_str_.find("\\\"");
    while(found != std::string::npos) {
        token_str_.replace(found, 2, "\"");
        found = token_str_.find("\\\"", found + 1);
    }
}

void Scanner::scanNumber() {
    size_t i = idx_ - 1;
    
    while(isDigit(getTokenChar())) {
        step();
    }
    
    if(getTokenChar() == '.' && isDigit(getNextTokenChar())) {
        step();
        while(isDigit(getTokenChar())) {
            step();
        }
    }
    
    token_num_ = std::stod(src_.substr(i, idx_ - i));
}

bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}

char Scanner::getTokenChar() {
    if(isEnd()) {
        return 0;
    }
    return src_[idx_];
}

char Scanner::getNextTokenChar() {
    if(idx_ + 1 >= src_.size()) {
        return 0;
    }
    return src_[idx_ + 1];
}

}
