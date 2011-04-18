#ifndef SYMBOL_H
#define SYMBOL_H

#include "Type.h"
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
  virtual std::string str() const {return name();}
};

class ParamSymbol : public Symbol {
public:
  ParamSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
};
  
class LexicalSymbol : public Symbol {
public:
  LexicalSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
};

class ConstantSymbol : public Symbol {
public:
  ConstantSymbol(const std::string& n, Type *t) : Symbol(n,t) {}
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

#endif // SYMBOL_H
