#include "Type.h"

namespace {

  BoolType boolType;
  IntType intType;
  FloatType floatType;

}

Type *Type::getBoolType() {return &boolType;}

Type *Type::getIntType() {return &intType;}
 
Type *Type::getFloatType() {return &floatType;}
