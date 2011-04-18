#include <sstream>
#include "Func.h"

using namespace std;

std::string Func::str() const {
  stringstream ss;
  ss << type_->str() << " " << name_ << "(";
  const unsigned n = this->numParams();
  for (unsigned int i = 0; i < n; i++) {
    const ParamSymbol *arg = this->param(i);
    ss << arg->type()->str() << " " << arg->str();
    if (i < n-1) ss << ",";
  }
  ss << ")";
  return ss.str();
}

std::string UserFunc::str() const {
  stringstream ss;
  ss << Func::str();
  if (body_ != 0) {
    ss << " {" << endl << body_->str() << endl << "}";
  }
  return ss.str();
}
