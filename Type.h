#ifndef TYPE_H
#define TYPE_H

#include <string>

class Type {
public:
  virtual ~Type() {}
  virtual bool equals(const Type *other) const = 0;
  virtual bool isBasicType() const {return false;}
  virtual bool isBoolType() const {return false;}
  virtual bool isNumericType() const {return false;}
  virtual bool isIntType() const {return false;}
  virtual bool isFloatType() const {return false;}  
  virtual std::string str() const = 0;
  static Type *getBoolType();
  static Type *getIntType();
  static Type *getFloatType();
};

class BasicType : public Type {
public:
  virtual bool isBasicType() const {return true;}
};

class BoolType : public BasicType {
public:
  virtual bool isBoolType() const {return true;}
  virtual bool equals(const Type *other) const {return other->isBoolType();}
  virtual std::string str() const {return "bool";}
};

class NumericType : public BasicType {
public:
  virtual bool isNumericType() const {return true;}
};

class IntType : public NumericType {
public:
  virtual bool isIntType() const {return true;}
  virtual bool equals(const Type *other) const {return other->isIntType();}
  virtual std::string str() const {return "int";}
};

class FloatType : public NumericType {
public:
  virtual bool isFloatType() const {return true;}
  virtual bool equals(const Type *other) const {return other->isFloatType();}
  virtual std::string str() const {return "float";}
};

#endif // TYPE_H
