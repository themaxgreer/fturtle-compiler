#include <sstream>
#include "Expr.h"
#include "Symbol.h"
#include "Value.h"
#include "Label.h"
#include "Type.h"

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

Value *BoolConstExpr::genCode(ostream &os) const{
  return new ConstValue(this->b);
}

Value *OrExpr::genCode(ostream &os) const {
  Value *leftValue = this->left->genCode(os);
  Value *rightValue = this->right->genCode(os);
  Value *temp = new TempValue();
  os << *temp << " = or i1" << *leftValue << ", " << *rightValue << endl;
  return temp;	
}

Value *AndExpr::genCode(ostream &os) const {
  Value *leftValue = this->left->genCode(os);
  Value *rightValue = this->right->genCode(os);
  Value *temp = new TempValue();
  os << *temp << " = and i1" << *leftValue << ", " << *rightValue << endl;
  return temp;
}

Value *NotExpr::genCode(ostream &os) const {
  Value *rightValue = this->expr->genCode(os);
  Value *temp = new TempValue();
  os << *temp << " = xor i1 1, " << *rightValue << endl;
  return temp;
}

Value *EQExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp oeq double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp eq i32 " << *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *NEExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp one double " << *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp ne i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *LTExpr::genCode(ostream &os) const{
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp olt double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp slt i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *LEExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp ole double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp sle i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *GTExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp ogt double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp sgt i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *GEExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fcmp oge double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = icmp sge i32 " <<  *leftValue << ", " << *rightValue << std::endl;
    }
    return temp;
}

Value *IntConstExpr::genCode(ostream &os) const {
    return new ConstValue(this->i);
}

Value *FloatConstExpr::genCode(ostream &os) const {
    return new ConstValue(this->f);
}

Value *AddExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fadd double " << *leftValue << ", " << *rightValue << endl;
    } else{
        os << *temp << " = add i32 " << *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *SubExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fsub double " << *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = sub i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *MulExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fmul double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = mul i32 " << *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *DivExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = fdiv double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = sdiv i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *RemExpr::genCode(ostream &os) const {
    Value *leftValue = this->left->genCode(os);
    Value *rightValue = this->right->genCode(os);
    Value *temp = new TempValue();
    if(this->left->type()->isFloatType()){
        os << *temp << " = frem double " <<  *leftValue << ", " << *rightValue << endl;
    } else {
        os << *temp << " = srem i32 " <<  *leftValue << ", " << *rightValue << endl;
    }
    return temp;
}

Value *IntToFloatExpr::genCode(ostream &os) const {
    Value *rightValue = this->expr->genCode(os);
    Value *temp = new TempValue();
        os << *temp << " = sitofp i32 " <<  *rightValue << " to double" << endl;
    return temp;
}

Value *FloatToIntExpr::genCode(ostream &os) const {
    Value *rightValue = expr->genCode(os);
    Value *temp = new TempValue();
        os << *temp << " = fptosi double " <<  *rightValue << " to i32" << endl;
    return temp;
}
Value *NegExpr::genCode(ostream &os) const {
    Value *rightValue = expr->genCode(os);
    Value *result = new TempValue();
    if(this->expr->type()->isFloatType()){
       os << *result << " = fsub double -0.0, " <<  *rightValue<< endl;
    } else {
       os << *result << " = sub i32 0, " <<  *rightValue << endl;
    }
    return result;
}
//Done?
Value *IfExpr::genCode(ostream &os) const {
    Label yesLabel, noLabel, lastLabel, doneLabel;
    Value *condVal = this->cond->genCode(os);
    cout << "br i1 " << *condVal <<
         ", label %" << yesLabel.str() <<
         ", label %" << noLabel.str() << endl;
    //yes block
    cout << yesLabel.str() << ": "<< endl;
    Value *yesVal = this->then_->genCode(os);
    cout << "br label %" << doneLabel.str() << endl;
	cout << endl;
    //no block
    cout << noLabel.str() << ": "<< endl;
    Value *noVal = else_->genCode(os);
    cout << "br label %" << lastLabel.str() << endl;
	cout << endl;
    //beg of outgoing block
    cout << lastLabel.str() << ": "<< endl;
	cout << "br label %" << doneLabel.str() << endl;
	//cout << endl; erroneous extra line
    cout << doneLabel.str() << ":" << endl;
    Value *resultVal = new TempValue();
    cout << *resultVal << " = phi i32 "
    << "["  << *yesVal << ", "
    << "%" << yesLabel.str() << "], "
    "[" << *noVal << ", %"
    << lastLabel.str() << "]" << endl;
    return resultVal;
}

Value *LexicalInitExpr::genCode(ostream &os) const {
    //Value *rightValue = this->expr->genCode(os); wrong order
    Value *result = new NameValue(this->ident);
    //cout << "in init" << endl;
    Value *rightValue = this->expr->genCode(os);
     if(this->expr->type()->isFloatType()){
       os << *result << " = fadd double 0.0e0, " << *rightValue << endl;
    } else {
       os << *result << " = add i32 0, " <<  *rightValue << endl;
    }
    return result;
}

Value *LetExpr::genCode(ostream &os) const {
    //like in turtle interpreter, eval the let expr
    for(auto iter_lexExpr = this->lexicalExprs->begin(); iter_lexExpr != this->lexicalExprs->end(); ++iter_lexExpr){
        //eval let parameters
		(*iter_lexExpr)->genCode(os);
    }
	//eval body
    Value *result = this->body->genCode(os);
    return result;
}


Value *FuncCallExpr::genCode(ostream &os) const {
    //hold all of the values from arguments
    std::vector<Value *>values;
    for(auto it = this->args->begin(); it != this->args->end(); ++it){
       //push values into vector
	//cout << "Push" << endl;
       values.push_back((*it)->genCode(os));
    }
	//Make a value for function call
	Value *ret = new TempValue();
	cout << *ret << " = call ";
	//hack
	if(this->type()->isIntType()){	 
		cout << "i32 @";
	} else if(this->type()->isBoolType()){
		cout << "i1 @";
	} else {
		cout << "double @";
	}
	cout << this->name << "(";
	//get iterators for arguments and values
	//helpful to go through all of the elements
	auto iter_args = this->args->begin();
	auto iter_values = values.begin();
	while (iter_values != values.end()) {
		//check argument type
		if((*iter_args)->type()->isFloatType()){
			cout << "double ";
		 } else if((*iter_args)->type()->isBoolType()){
			cout << "i1 ";
		 } else {
		 	cout << "i32 ";
		 } 
		cout << *(*iter_values);
		++iter_args;
		++iter_values;
		//NOTE: This had to be added for mutiple arguments
		if (iter_values != values.end()) {
			cout << ", ";
		}
	}
	//finish the statement
	cout << ")" << endl;
    return ret;
}

Value *VarExpr::genCode(ostream &os) const {
    if (this->sym->isConst()) {
            //check for each type of constant
            auto b = dynamic_cast<const ConstBoolSymbol *>(this->sym);
                //dynamic cast returns 0 or null if it can't be cas
		if (b != 0) {
                        return new ConstValue(b->value());
                }
		//Not boolean
                auto i = dynamic_cast<const ConstIntSymbol *>(this->sym);
                if (i != 0) {
                        return new ConstValue(i->value());
                }
		//Not int
                auto f = dynamic_cast<const ConstFloatSymbol *>(this->sym);
                if (f != 0) {
                        return new ConstValue(f->value());
                }
    }
	//cout << "DEBUG: NameValue created" << endl;
        //cout << "Name: " << this->sym->str() << endl;
	return new NameValue(this->sym->str());
}

Value *BlockExpr::genCode(ostream &os) const {
   //eval all of the expr
    Value *lastExprVal;
    for (auto it = this->exprList->begin(); it != this->exprList->end(); ++it) {
	//get*temp for last expression
	lastExprVal = (*it)->genCode(os);
    }
    return lastExprVal;
}
