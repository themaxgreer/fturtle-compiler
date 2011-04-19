#include "Expr.h"
#include <sstream>

using namespace std;

ostream&  LetExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << "LET(" << endl;
  const unsigned n = lexicalExprs->size();
  for (unsigned i = 0; i < n; i++)
    (*lexicalExprs)[i]->print(os, level+1) << endl;
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
