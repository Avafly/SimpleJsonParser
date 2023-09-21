//
//  JsonElement.h
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#ifndef JsonElement_h
#define JsonElement_h

#include <map>
#include <string>
#include <vector>
#include <memory>
#include <variant>

namespace Json {

class JsonElement;

//using namespace std;
using JsonObject = std::map<std::string, std::shared_ptr<JsonElement>>;
using JsonArray = std::vector<std::shared_ptr<JsonElement>>;

class JsonElement {
public:
    enum class Type {
        JSON_OBJECT,
        JSON_ARRAY,
        JSON_STRING,
        JSON_NUMBER,
        JSON_BOOL,
        JSON_NULL
    };
    
    JsonElement();
    ~JsonElement();
    
    void setValue(std::shared_ptr<JsonObject> token_object);
    void setValue(std::shared_ptr<JsonArray> token_array);
    void setValue(std::shared_ptr<std::string> token_string);
    void setValue(double token_number);
    void setValue(bool token_bool);
    
    std::string toStr();
    
    friend std::ostream & operator << (std::ostream &os, const JsonObject &object);
    friend std::ostream & operator << (std::ostream &os, const JsonArray &array);
    
private:
    // use variant instead of union
    using Token = std::variant<
        std::shared_ptr<JsonObject>,
        std::shared_ptr<JsonArray>,
        std::shared_ptr<std::string>,
        double,
        bool
    >;
    
    Type type_;
    Token token_;
};
}


#endif /* JsonElement_h */
