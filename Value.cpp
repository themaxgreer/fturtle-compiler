#include <iostream>
#include <sstream>
#include "Value.h"

ConstValue::ConstValue(const std::string& value) : value(value) {};
ConstValue::ConstValue(int i){
	std::stringstream ss; 
	ss << i; 
	this->value = ss.str();
}
ConstValue::ConstValue(double d){
         std::stringstream ss;
	 ss.precision(8);
         ss << std::scientific << d;
         this->value = ss.str();
}

ConstValue::ConstValue(float f){
	std::stringstream ss; 
	ss.precision(8); 
	ss << std::scientific << f; 
	this->value = ss.str();
}
ConstValue::ConstValue(bool b){
        this->value = (b == false) ? "0" : "1";
}
unsigned TempValue::next;
TempValue::TempValue() : num(next++) {}
void TempValue::reset(){
	next = 0;
}
