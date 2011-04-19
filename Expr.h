#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cmath>
#include "Type.h"
#include "Symbol.h"
#include "Error.h"

inline std::ostream& indent(std::ostream& os, unsigned n) {
  for (unsigned i = 0; i < n; i++)
    os << " ";
  return os;
}

class Expr {
  Type *type_;
public:
  Expr(Type *t) : type_(t) {}
  virtual ~Expr() {if (!type_->isBasicType()) delete type_;}
  Type *type() {return type_;}
  virtual bool boolValue() const {return false;}
  virtual int intValue() const {return 0;}
  virtual double floatValue() const {return 0.0;}
  virtual std::ostream& print(std::ostream& os, unsigned level) const = 0;
};

class BoolExpr : public Expr {
public:
  BoolExpr() : Expr(Type::getBoolType()) {}
};

class ArithExpr : public Expr {
public:
  ArithExpr(Type *t) : Expr(t) {}
};

class BoolConstExpr : public BoolExpr {
  const bool b;
public:
  BoolConstExpr(bool v) : b(v) {}
  virtual bool boolValue() const {return b;}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    const bool v = b ? "true" : "false";
    return indent(os,level) << v << std::endl;
  }
};

class OrExpr : public BoolExpr {
  Expr *left;
  Expr *right;
public:
  OrExpr(Expr *l, Expr *r) : BoolExpr(), left(l), right(r) {}
  virtual ~OrExpr() {delete left; delete right;}
  virtual bool boolValue() const {
    return left->boolValue() || right->boolValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "or" << std::endl;
    left->print(os,level+1);
    return right->print(os,level+1);
  }
};

class AndExpr : public BoolExpr {
  Expr *left;
  Expr *right;
public:
  AndExpr(Expr *l, Expr *r) : BoolExpr(), left(l), right(r) {}
  virtual ~AndExpr() {delete left; delete right;}
  virtual bool boolValue() const {
    return left->boolValue() && right->boolValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "and" << std::endl;
    left->print(os,level+1);
    return right->print(os,level+1);
  }
};

class NotExpr : public BoolExpr {
  Expr *expr;
public:
  NotExpr(Expr *e) : BoolExpr(), expr(e) {}
  virtual ~NotExpr() {delete expr;}
  virtual bool boolValue() const {return !expr->boolValue();}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "not" << std::endl;
    return expr->print(os,level+1);
  }
};

class CmpExpr : public BoolExpr {
protected:
  Expr *left;
  Expr *right;
public:
  CmpExpr(Expr *l, Expr *r) : left(l), right(r) {}
  virtual ~CmpExpr() {delete left; delete right;}
  std::ostream& print(const std::string& op, 
		      std::ostream& os, unsigned level) const {
    indent(os,level) << op << std::endl;
    left->print(os,level+1);
    return right->print(os,level+1);
  }
};

class EQExpr : public CmpExpr {
public:
  EQExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() == right->intValue();
    return left->floatValue() == right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("EQ",os,level);
  }
};

class NEExpr : public CmpExpr {
public:
  NEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() != right->intValue();
    return left->floatValue() != right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("NE",os,level);
  }
};

class LTExpr : public CmpExpr {
public:
  LTExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() < right->intValue();
    return left->floatValue() < right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("LT",os,level);
  }
};

class LEExpr : public CmpExpr {
public:
  LEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() <= right->intValue();
    return left->floatValue() <= right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("LE",os,level);
  }
};

class GTExpr : public CmpExpr {
public:
  GTExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() > right->intValue();
    return left->floatValue() > right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("GT",os,level);
  }
};

class GEExpr : public CmpExpr {
public:
  GEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual bool boolValue() const {
    if (left->type()->isIntType())
      return left->intValue() >= right->intValue();
    return left->floatValue() >= right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return CmpExpr::print("GE",os,level);
  }
};

class IntConstExpr : public ArithExpr {
  const int i;
public:
  IntConstExpr(int v) : ArithExpr(Type::getIntType()), i(v) {}
  virtual int intValue() const {return i;}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return indent(os,level) << i << std::endl;
  }
};

class FloatConstExpr : public ArithExpr {
  const double f;
public:
  FloatConstExpr(double v) : ArithExpr(Type::getFloatType()), f(v) {}
  virtual double floatValue() const {return f;}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return indent(os,level) << f << std::endl;
  }
};

class ArithBinExpr : public ArithExpr {
protected:
  Expr *left;
  Expr *right;
public:
  ArithBinExpr(Expr *l, Expr *r)
    : ArithExpr(l->type()), left(l), right(r) {}
  std::ostream& print(const std::string& op, 
		      std::ostream& os, unsigned level) const {
    indent(os,level) << op << std::endl;
    left->print(os,level+1);
    return right->print(os,level+1);
  }
};

class AddExpr : public ArithBinExpr {
public:
  AddExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual int intValue() const {
    return left->intValue() + right->intValue();
  }
  virtual double floatValue() const {
    return left->floatValue() + right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return ArithBinExpr::print("ADD",os,level);
  }
};

class SubExpr : public ArithBinExpr {
public:
  SubExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual int intValue() const {
    return left->intValue() - right->intValue();
  }
  virtual double floatValue() const {
    return left->floatValue() - right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return ArithBinExpr::print("SUB",os,level);
  }
};

class MulExpr : public ArithBinExpr {
public:
  MulExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual int intValue() const {
    return left->intValue() * right->intValue();
  }
  virtual double floatValue() const {
    return left->floatValue() * right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return ArithBinExpr::print("MUL",os,level);
  }
};

class DivExpr : public ArithBinExpr {
public:
  DivExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual int intValue() const {
    return left->intValue() / right->intValue();
  }
  virtual double floatValue() const {
    return left->floatValue() / right->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return ArithBinExpr::print("DIV",os,level);
  }
};

class RemExpr : public ArithBinExpr {
public:
  RemExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual int intValue() const {
    return left->intValue() % right->intValue();
  }
  virtual double floatValue() const {
    return fmod(left->floatValue(),right->floatValue());
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return ArithBinExpr::print("REM",os,level);
  }
};

class IntToFloatExpr : public ArithExpr {
  Expr *expr;
public:
  IntToFloatExpr(Expr *e) : ArithExpr(Type::getFloatType()), expr(e) {}
  virtual double floatValue() const {return (double) expr->intValue();}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "ITOF" << std::endl;
    return expr->print(os,level+1);
  }
};

class FloatToIntExpr : public ArithExpr {
  Expr *expr;
public:
  FloatToIntExpr(Expr *e) : ArithExpr(Type::getIntType()), expr(e) {}
  virtual int intValue() const {return (int) expr->floatValue();}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "FTOI" << std::endl;
    return expr->print(os,level+1);
  }
};

class NegExpr : public ArithExpr {
  Expr *expr;
public:
  NegExpr(Expr *e) : ArithExpr(e->type()), expr(e) {}
  virtual int intValue() const {
    return -expr->intValue();
  }
  virtual double floatValue() const {
    return -expr->floatValue();
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "NEG" << std::endl;
    return expr->print(os,level+1);
  }
};

class IfExpr : public Expr {
  Expr *cond;
  Expr *then_;
  Expr *else_;
public:
  IfExpr(Expr *c, Expr *t, Expr *e)
    : Expr(t->type()), cond(c), then_(t), else_(e) {}
  virtual bool boolValue() const;
  virtual int intValue() const;
  virtual double floatValue() const;
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << "IF" << std::endl;
    cond->print(os,level+1);
    then_->print(os,level+1);
    return else_->print(os,level+1);
  }
};

class LexicalInitExpr : public Expr {
  const std::string& ident;
  Expr *expr;
public:
  LexicalInitExpr(const std::string& n, Expr *e) 
    : Expr(e->type()), ident(n), expr(e) {}
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    indent(os,level) << ident << "=" << std::endl;
    return expr->print(os,level+1);
  }
};

class LetExpr : public Expr {
  std::vector<Expr*> *lexicalExprs;
  Expr *body;
public:
  LetExpr(std::vector<Expr*> *l, Expr *b) :
    Expr(b->type()), lexicalExprs(l), body(b) {}
  virtual bool boolValue() const {
    throw Error("let-expressions can not be statically evaluated");
    return false;
  }
  virtual int intValue() const  {
    throw Error("let-expressions can not be statically evaluated");
    return 0;
  }
  virtual double floatValue() const {
    throw Error("let-expressions can not be statically evaluated");
    return 0.0;
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const;
};

class FuncCallExpr : public Expr {
  const std::string& name;
  std::vector<Expr*> *args;
public:
  FuncCallExpr(Type *retType, const std::string& n, std::vector<Expr*>* a) 
    : Expr(retType), name(n), args(a) {}
  virtual bool boolValue() const {
    throw Error("function calls can not be statically evaluated");
    return false;
  }
  virtual int intValue() const  {
    throw Error("function calls can not be statically evaluated");
    return 0;
  }
  virtual double floatValue() const {
    throw Error("function calls can not be statically evaluated");
    return 0.0;
  }
  virtual std::ostream& print(std::ostream& os, unsigned level) const;
};

class VarExpr : public Expr {
  Symbol *sym;
public:
  VarExpr(Symbol *s) : Expr(s->type()), sym(s) {}
  virtual bool boolValue() const;
  virtual int intValue() const;
  virtual double floatValue() const;
  virtual std::ostream& print(std::ostream& os, unsigned level) const {
    return indent(os,level) << sym->str() << std::endl;
  }
};

class BlockExpr : public Expr {
  std::vector<Expr*> *exprList;
public:
  BlockExpr(std::vector<Expr*> *list) 
    : Expr(list->back()->type()), exprList(list) {}
  virtual std::ostream& print(std::ostream& os, unsigned level) const;
  virtual bool boolValue() const {
    throw Error("block expressions can not be statically evaluated");
    return false;
  }
  virtual int intValue() const  {
    throw Error("block expressions can not be statically evaluated");
    return 0;
  }
  virtual double floatValue() const {
    throw Error("block expressions can not be statically evaluated");
    return 0.0;
  }
};

#endif // EXPR_H
