#include <sstream>
#include "Func.h"

using namespace std;

ostream& Func::print(ostream& os) const {
  os << type_->str() << " " << name_ << "(";
  const unsigned n = this->numParams();
  for (unsigned int i = 0; i < n; i++) {
    const ParamSymbol *arg = this->param(i);
    os << arg->type()->str() << " " << arg->str();
    if (i < n-1) os << ",";
  }
  os << ")";
  return os;
}

ostream& UserFunc::print(ostream& os) const  {
  Func::print(os);
  if (body_ != 0) {
    os << " {" << endl; 
    body_->print(os,1) << endl;
    os << "}" << endl;
  }
  return os;
}
