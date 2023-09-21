//
//  Parser.h
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#ifndef Parser_h
#define Parser_h

#include <memory>

#include "Scanner.h"
#include "JsonElement.h"
#include "ErrorHandling.h"

namespace Json {
class Parser {
public:
    Parser(const Scanner &scanner);
    std::shared_ptr<JsonElement>    parse();
    
private:
    Scanner scanner_;
    
    std::shared_ptr<JsonObject>     parseObject();
    std::shared_ptr<JsonArray>      parseArray();
};
}

#endif /* Parser_h */
