#include "Expr.h"
#include "Symbol.h"
#include <sstream>

using namespace std;

bool IfExpr::boolValue() const {
  if (cond->boolValue())
    return then_->boolValue();
  return else_->boolValue();
}

int IfExpr::intValue() const {
  if (cond->boolValue())
    return then_->intValue();
  return else_->intValue();
}

double IfExpr::floatValue() const {
  if (cond->boolValue())
    return then_->floatValue();
  return else_->floatValue();
}

bool VarExpr::boolValue() const {
  ConstBoolSymbol *s = static_cast<ConstBoolSymbol*>(sym);
  return s->value();
}

int VarExpr::intValue() const {
  ConstIntSymbol *s = static_cast<ConstIntSymbol*>(sym);
  return s->value();
}

double VarExpr::floatValue() const {
  ConstFloatSymbol *s = static_cast<ConstFloatSymbol*>(sym);
  return s->value();
}

ostream& LetExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << "LET(" << endl;
  const unsigned n = lexicalExprs->size();
  for (unsigned i = 0; i < n; i++)
    (*lexicalExprs)[i]->print(os, level+1);
  indent(os,level) << ")" << endl;
  return body->print(os,level+1);
}

ostream& FuncCallExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << name << "(" << endl;
  const unsigned n = args->size();
  for (unsigned i = 0; i < n; i++)
    (*args)[i]->print(os,level+2);
  return indent(os,level) << ")" << endl;
}

ostream& BlockExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << "{" << endl;
  const unsigned n = exprList->size();
  for (unsigned i = 0; i < n; i++)
    (*exprList)[i]->print(os,level+1);
  return indent(os,level) << "}" << endl;
}
