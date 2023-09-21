//
//  Scanner.h
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#ifndef Scanner_h
#define Scanner_h

#include <string>
#include <sstream>

namespace Json {

class Scanner {
    
public:
    
    Scanner(const std::string &src);
    
    enum class TokenType {
        END_OF_SRC,         // EOF
        BEGIN_OBJECT,       // oject '{' and '}'
        END_OBJECT,
        BEGIN_ARRAY,        // array '[' and ']'
        END_ARRAY,
        TOKEN_STRING,       // quote " for string
        TOKEN_NUMBER,       // 1, 2, 1.5e10 for number
        TOKEN_TRUE,         // boolean
        TOKEN_FALSE,
        TOKEN_NULL,
        PAIR_SEPARATOR,     // comma
        TOKEN_SEPARATOR,    // colon
        ERROR               // unexpected case
    };
    
    friend std::ostream & operator << (std::ostream &os, const TokenType type);
    
    TokenType   scan();
    
    std::string getTokenStr();
    
    double      getTokenNum();
    
    void        Rollback();
    
    
private:
    std::string src_;
    size_t      idx_;
    size_t      prev_idx_;
    std::string token_str_;
    double      token_num_;
    
    bool    isEnd();
    char    step();
    
    void    scanTrue();
    void    scanFalse();
    void    scanNull();
    void    scanString();
    void    scanNumber();
    
    bool    isDigit(char c);
    char    getTokenChar();
    char    getNextTokenChar();
};
}


#endif /* Scanner_h */
