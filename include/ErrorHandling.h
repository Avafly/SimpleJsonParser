//
//  ErrorHandling.h
//  SimpleJsonParser
//
//  Created by CX Lin on 2023/09/20.
//

#ifndef ErrorHandling_h
#define ErrorHandling_h

#include <stdexcept>
#include <string>

namespace Json {
inline void ErrorHandling(const std::string &error_msg) {
    throw std::logic_error(error_msg);
}
}

#endif /* ErrorHandling_h */
