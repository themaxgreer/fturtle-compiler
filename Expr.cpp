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

std::string FuncCallExpr::str() const {
  stringstream ss;
  ss << "name(";
  const unsigned n = args->size();
  for (unsigned i = 0; i < n; i++) {
    ss << (*args)[i]->str();
    if (i < n-1) ss << ",";
  }
  ss << ")";
  return ss.str();
}

std::string BlockExpr::str() const {
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
