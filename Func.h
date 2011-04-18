#ifndef FUNC_H
#define FUNC_H

#include "Type.h"
#include "Symbol.h"
#include "Expr.h"
#include <string>
#include <vector>

class Func {
protected:
  const std::string name_;
  Type *type_;
  std::vector<ParamSymbol*> *params;
public:
  Func(const std::string& n, 
       Type *t, std::vector<ParamSymbol*> *p) 
    : name_(n), type_(t), params(p) {}
  virtual ~Func() {
    for (unsigned i = 0; i < params->size(); i++)
      delete (*params)[i];
    delete params;
  }
  const std::string& name() const {return name_;}
  Type *type() const {return type_;}
  unsigned numParams() const {return params->size();}
  const ParamSymbol *param(unsigned i) const {return (*params)[i];}
  virtual bool isDefined() const = 0;
  virtual std::string str() const;
};

class UserFunc : public Func {
  Expr *body_; // may be null
public:
  UserFunc(const std::string& n, 
	   Type *t, std::vector<ParamSymbol*> *p,
	   Expr *b = 0) : Func(n,t,p), body_(b) {}
  virtual ~UserFunc() {delete body_;}
  virtual bool isDefined() const {return body_ != 0;}
  Expr *body() {return body_;}
  void setBody(Expr *b) {body_ = b;}
  virtual std::string str() const;
};

#endif // FUNC_H
