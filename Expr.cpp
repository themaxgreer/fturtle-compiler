#include "Expr.h"
#include <sstream>

using namespace std;

string LetExpr::str() const {
  stringstream ss;
  ss << "let(";
  const unsigned n = lexicalExprs->size();
  for (unsigned i = 0; i < n; i++) {
    ss << (*lexicalExprs)[i]->str();
    if (i < n-1) ss << ",";
  }
  ss << ")" << body->str();
  return ss.str();
};

ostream&  LetExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << "LET(" << endl;
  const unsigned n = lexicalExprs->size();
  for (unsigned i = 0; i < n; i++)
    (*lexicalExprs)[i]->print(os, level+1) << endl;
  indent(os,level) << ")" << endl;
  return body->print(os,level+1);
}

string FuncCallExpr::str() const {
  stringstream ss;
  ss << name << "(";
  const unsigned n = args->size();
  for (unsigned i = 0; i < n; i++) {
    ss << (*args)[i]->str();
    if (i < n-1) ss << ",";
  }
  ss << ")";
  return ss.str();
}

ostream& FuncCallExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << name << "(" << endl;
  const unsigned n = args->size();
  for (unsigned i = 0; i < n; i++)
    (*args)[i]->print(os,level+2);
  return indent(os,level) << ")" << endl;
}

string BlockExpr::str() const {
  stringstream ss;
  ss << "{";
  const unsigned n = exprList->size();
  for (unsigned i = 0; i < n; i++) {
    ss << (*exprList)[i]->str();
    if (i < n-1) ss << ",";
  }
  ss << "}";
  return ss.str();
}

ostream& BlockExpr::print(ostream& os, unsigned level) const {
  indent(os,level) << "{" << endl;
  const unsigned n = exprList->size();
  for (unsigned i = 0; i < n; i++)
    (*exprList)[i]->print(os,level+1);
  return indent(os,level) << "}" << endl;
}
