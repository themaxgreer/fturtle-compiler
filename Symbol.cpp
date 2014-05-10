#include "Symbol.h"

using namespace std;

SymbolTable *symtab;

Symbol *SymbolTable::get(const std::string& name) {
  for (SymbolTable *s = this; s != 0; s = s->prev_) {
    map<string,Symbol*>::iterator iter = s->tbl.find(name);
    if (iter != s->tbl.end())
      return iter->second;
  }
  return 0; // not found
}

