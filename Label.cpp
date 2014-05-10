#include <iostream>
#include "Label.h"

unsigned Label::next;
Label::Label(void) : num(next++) {}
