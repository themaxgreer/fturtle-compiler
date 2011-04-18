#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
  const std::string msg;
public:
  Error(const std::string& m) : msg(m) {}
  const std::string& message() const {return msg;}
};


#endif // ERROR_H
