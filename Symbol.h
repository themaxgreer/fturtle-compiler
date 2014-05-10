#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
#include <sstream>
#include <string>
#include <map>

class Symbol {
  const std::string name_;
  Type *type_;
public:
  Symbol(const std::string& n, Type *t) : name_(n), type_(t) {}
  const std::string& name() const {return name_;}
  Type *type() const {return type_;}
  virtual ~Symbol() {}
  virtual bool isConst() const {return false;}
  virtual std::string str() const {return name();}
};

class ParamSymbol : public Symbol {
public:
  ParamSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
};
  
class LexicalSymbol : public Symbol {
	/* Deleted spec suggestion, only can make it work using
	* original Symbol.h */
	//std::string alias; 
       //replacement name for symbol
public:
  LexicalSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
 // virtual std::string str() const { return alias; }
  //void setAlias(const std::string& a) { alias = a; }
};

class ConstSymbol : public Symbol {
public:
  ConstSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
  virtual bool isConst() const {return true;}
};

class ConstBoolSymbol : public ConstSymbol {
  const bool val;
public:
  ConstBoolSymbol(const std::string& n, bool v) 
    : ConstSymbol(n, Type::getBoolType()), val(v) {} 
  bool value() const {return val;}
  virtual std::string str() const {
    const std::string& s = val ? "true" : "false";
    return name() + "(=" + s + ")";
  }
};

class ConstIntSymbol : public ConstSymbol {
  const int val;
public:
  ConstIntSymbol(const std::string& n, int v) 
    : ConstSymbol(n, Type::getIntType()), val(v) {} 
  int value() const {return val;}
  virtual std::string str() const {
    std::stringstream ss;
    ss << name() << "(=" << val << ")";
    return ss.str();
  }
};

class ConstFloatSymbol : public ConstSymbol {
  const double val;
public:
  ConstFloatSymbol(const std::string& n, double v) 
    : ConstSymbol(n, Type::getFloatType()), val(v) {} 
  double value() const {return val;}
  virtual std::string str() const {
    std::stringstream ss;
    ss << name() << "(=" << val << ")";
    return ss.str();
  }
};

class SymbolTable {
  SymbolTable *prev_;
  std::map<std::string,Symbol*> tbl;
public:
  explicit SymbolTable(SymbolTable *p = 0) : prev_(p) {}
  SymbolTable *prev() {return prev_;}
  void put(const std::string& name, Symbol *sym) {tbl[name] = sym;}
  Symbol *get(const std::string& name);
};

extern SymbolTable *symtab;

#endif // SYMBOL_H
