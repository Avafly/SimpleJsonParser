//
//  main.cpp
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

#include "Scanner.h"
#include "Parser.h"
#include "ErrorHandling.h"

using namespace Json;

int main(int argc, const char *argv[]) {
    
    try {
        // read json file
        std::string filename = "./test/test1.json";
        std::ifstream jsonFile(filename);
        if(!jsonFile.is_open()) {
            ErrorHandling("failed to open file: " + filename);
            return 1;
        }
        std::stringstream ss;
        ss << jsonFile.rdbuf();
        const std::string &config = ss.str();
        
        // scan and parse json file
        Scanner scanner(config);
        Parser parser(scanner);
        std::shared_ptr<JsonElement> element = parser.parse();
        
        // print parse result
        std::cout << element->toStr() << std::endl;
    }
    catch(std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
