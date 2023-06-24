#ifndef SCOPE_H
#define SCOPE_H

#include <vector>
#include "symbol.h"

typedef std::vector<Symbol *> symbols;

class Scope {
private:
    typedef std::string string;

    Scope *_enclosing;
    symbols _symbols;

public:
    Scope(Scope *enclosing = nullptr);
    void insert(Symbol *symbol);
    void remove(const string &name);
    Symbol *find(const string &name) const;
    Symbol *lookup(const string &name) const;
    Scope *enclosing() const { return _enclosing; }

};

#endif