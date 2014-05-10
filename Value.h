#ifndef _VALUE_H
#define _VALUE_H

#include <string>
#include <iostream>
#include <sstream>

class Value {
  public:
    virtual std::string str() const = 0;   
};

class NameValue : public Value {
  private:
    std::string name;
  public:
    NameValue(const std::string &name) : name(name) {}
    virtual std::string str() const { std::stringstream ss; ss << "%" << name; return ss.str(); }
};

class ConstValue : public Value {
   private:
    std::string value;
   public:
    ConstValue(const std::string& value);
    ConstValue(int i);
    ConstValue(float f);
    ConstValue(bool b);
    ConstValue(double d);
    virtual std::string str() const { return value; }
};

class TempValue : public Value {
  private: 
   const unsigned num;
   static unsigned next;
  public:
    TempValue(void);
    virtual std::string str() const { std::stringstream ss; ss << "%" << num; return ss.str(); }
    static void reset(void);
};

inline std::ostream& operator<<(std::ostream& out, const Value& val){
	out << val.str();
	return out;
}

#endif
