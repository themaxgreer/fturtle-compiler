#ifndef EXPR_H
#define EXPR_H

#include <string>
#include <vector>
#include <sstream>
#include "Type.h"
#include "Symbol.h"

class Expr {
  Type *type_;
public:
  Expr(Type *t) : type_(t) {}
  virtual ~Expr() {if (!type_->isBasicType()) delete type_;}
  Type *type() {return type_;}
  virtual std::string str() const = 0;
};

class BoolExpr : public Expr {
public:
  BoolExpr() : Expr(Type::getBoolType()) {}
};

class ArithExpr : public Expr {
public:
  ArithExpr(Type *t) : Expr(t) {}
};

class BoolLitExpr : public BoolExpr {
  const bool b;
public:
  BoolLitExpr(bool v) : b(v) {}
  virtual std::string str() const {return b ? "true" : "false";}
};

class OrExpr : public BoolExpr {
  Expr *left;
  Expr *right;
public:
  OrExpr(Expr *l, Expr *r) : BoolExpr(), left(l), right(r) {}
  virtual ~OrExpr() {delete left; delete right;}
  virtual std::string str() const {
    return "or(" + left->str() + ", " + right->str() + ")";
  };
};

class AndExpr : public BoolExpr {
  Expr *left;
  Expr *right;
public:
  AndExpr(Expr *l, Expr *r) : BoolExpr(), left(l), right(r) {}
  virtual ~AndExpr() {delete left; delete right;}
  virtual std::string str() const {
    return "and(" + left->str() + ", " + right->str() + ")";
  };
};

class NotExpr : public BoolExpr {
  Expr *expr;
public:
  NotExpr(Expr *e) : BoolExpr(), expr(e) {}
  virtual ~NotExpr() {delete expr;}
  virtual std::string str() const {
    return "not(" + expr->str() + ")";
  };
};

class CmpExpr : public BoolExpr {
protected:
  Expr *left;
  Expr *right;
public:
  CmpExpr(Expr *l, Expr *r) : left(l), right(r) {}
  virtual ~CmpExpr() {delete left; delete right;}
};

class EQExpr : public CmpExpr {
public:
  EQExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "eq(" + left->str() + "," + right->str() + ")";
  };
};

class NEExpr : public CmpExpr {
public:
  NEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "ne(" + left->str() + "," + right->str() + ")";
  };
};

class LTExpr : public CmpExpr {
public:
  LTExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "lt(" + left->str() + "," + right->str() + ")";
  };
};

class LEExpr : public CmpExpr {
public:
  LEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "le(" + left->str() + "," + right->str() + ")";
  };
};

class GTExpr : public CmpExpr {
public:
  GTExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "gt(" + left->str() + "," + right->str() + ")";
  };
};

class GEExpr : public CmpExpr {
public:
  GEExpr(Expr *l, Expr *r) : CmpExpr(l, r) {}
  virtual std::string str() const {
    return "ge(" + left->str() + "," + right->str() + ")";
  };
};

class IntLitExpr : public ArithExpr {
  const int i;
public:
  IntLitExpr(int v) : ArithExpr(Type::getIntType()), i(v) {}
  virtual std::string str() const {
    std::stringstream ss; ss << i; return ss.str();
  }
};

class FloatLitExpr : public ArithExpr {
  const double f;
public:
  FloatLitExpr(double v) : ArithExpr(Type::getFloatType()), f(v) {}
  virtual std::string str() const {
    std::stringstream ss; ss << f; return ss.str();
  }
};

class ArithBinExpr : public ArithExpr {
protected:
  Expr *left;
  Expr *right;
public:
  ArithBinExpr(Expr *l, Expr *r)
    : ArithExpr(l->type()), left(l), right(r) {}
};

class AddExpr : public ArithBinExpr {
public:
  AddExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual std::string str() const {
    return "add(" + left->str() + "," + right->str() + ")";
  };
};

class SubExpr : public ArithBinExpr {
public:
  SubExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual std::string str() const {
    return "sub(" + left->str() + "," + right->str() + ")";
  };
};

class MulExpr : public ArithBinExpr {
public:
  MulExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual std::string str() const {
    return "mul(" + left->str() + "," + right->str() + ")";
  };
};

class DivExpr : public ArithBinExpr {
public:
  DivExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual std::string str() const {
    return "div(" + left->str() + "," + right->str() + ")";
  };
};

class RemExpr : public ArithBinExpr {
public:
  RemExpr(Expr *l, Expr *r) : ArithBinExpr(l,r) {}
  virtual std::string str() const {
    return "rem(" + left->str() + "," + right->str() + ")";
  };
};

class IntToFloatExpr : public ArithExpr {
  Expr *expr;
public:
  IntToFloatExpr(Expr *e) : ArithExpr(Type::getFloatType()), expr(e) {}
  virtual std::string str() const {
    return "itof(" + expr->str() + ")";
  };
};

class FloatToIntExpr : public ArithExpr {
  Expr *expr;
public:
  FloatToIntExpr(Expr *e) : ArithExpr(Type::getIntType()), expr(e) {}
  virtual std::string str() const {
    return "ftoi(" + expr->str() + ")";
  };
};

class NegExpr : public ArithExpr {
  Expr *expr;
public:
  NegExpr(Expr *e) : ArithExpr(e->type()), expr(e) {}
  virtual std::string str() const {
    return "neg(" + expr->str() + ")";
  };
};

class IfExpr : public Expr {
  Expr *cond;
  Expr *then_;
  Expr *else_;
public:
  IfExpr(Expr *c, Expr *t, Expr *e)
    : Expr(then_->type()), cond(c), then_(t), else_(e) {}
  virtual std::string str() const {
    return 
      "if(" + cond->str() + ", " + 
      then_->str() + ", " + else_->str() + ")";
  }
};

class LexicalInitExpr : public Expr {
  const std::string& ident;
  Expr *expr;
public:
  LexicalInitExpr(const std::string& n, Expr *e) 
    : Expr(e->type()), ident(n), expr(e) {}
  virtual std::string str() const {
    return ident + "=" + expr->str();
  };
};

class LetExpr : public Expr {
  std::vector<Expr*> *lexicalExprs;
  Expr *body;
public:
  LetExpr(std::vector<Expr*> *l, Expr *b) :
    Expr(b->type()), lexicalExprs(l), body(b) {}
  virtual std::string str() const;
};

class FuncCallExpr : public Expr {
  const std::string& name;
  std::vector<Expr*> *args;
public:
  FuncCallExpr(Type *retType, const std::string& n, std::vector<Expr*>* a) 
    : Expr(retType), name(n), args(a) {}
  virtual std::string str() const;
};

class VarExpr : public Expr {
  Symbol *sym;
public:
  VarExpr(Symbol *s) : Expr(s->type()) {}
  virtual std::string str() const {return sym->str();}
};

class BlockExpr : public Expr {
  std::vector<Expr*> *exprList;
public:
  BlockExpr(std::vector<Expr*> *list) 
    : Expr(list->back()->type()), exprList(list) {}
  virtual std::string str() const;
};

#endif // EXPR_H
