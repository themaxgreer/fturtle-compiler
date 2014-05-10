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
    body_->print(os,1);
    os << "}" << endl;
  }
  return os;
}

void UserFunc::genCode(ostream& os) const {
        //reset temp value
	TempValue::reset();
	
	//TODO: check for bool body
	os << "define ";
	if(this->body_->type()->isFloatType()){
		os << "float" << " @" << this->name_ << " (";
	} else if(this->body_->type()->isIntType()){
		os << "i32" << " @" << this->name_ << " (";
	} else {
		os << "i1" << " @" << this->name_ << " (";
	}
	//os << " @" << this->name_ << " (";

	auto iter_params = this->params->begin();
	while (iter_params != this->params->end()) {
		if((*iter_params)->type()->isFloatType()){
			cout << "double";
		} else {
			cout << "i32";
		}
		cout << " %" << (*iter_params)->str();
		++iter_params;
		if (iter_params != this->params->end()) {
			cout << ", ";
		}
	}
	os << ") {" << endl;
	os << "entry:" << endl;
	if(this->body_->type()->isFloatType()){
                os << "ret " << "float " <<  *this->body_->genCode(os) << endl;
        } else if(this->body_->type()->isIntType()){
                os << "ret " << "i32 " << *this->body_->genCode(os) << endl;
        } else {
		os << "ret " << "i1 " << *this->body_->genCode(os) << endl;
	}
       //finish the body of the statement
	os << "}" << endl;
	return;
}
