#include "scope.h"

using namespace std;

Scope::Scope(Scope *enclosing) 
    : _enclosing(enclosing) {
}

void Scope::insert(Symbol *symbol) {
    _symbols.push_back(symbol);
}

void Scope::remove(const string &name) {
    for(auto it = _symbols.begin(); it != _symbols.end(); it++) {
        if((*it)->name() == name) {
            _symbols.erase(it);
            return;
        }
    }

    return;
}


Symbol *Scope::find(const string &name) const {
    //symbols::iterator it = find_if(_symbols.begin(), _symbols.end(), [&name](const Symbol& sym) { })
    for(auto it = _symbols.begin(); it != _symbols.end(); it++) {
        if((*it)->name() == name) {
            return *it;
        }
    }

    return nullptr;
}

Symbol *Scope::lookup(const string &name) const {
    const Scope *curScope = this;

    while(curScope != nullptr) {
        Symbol *symbol = curScope->find(name);
        if(symbol != nullptr) {
            return symbol;
        } else {
            curScope = curScope->_enclosing;
        }
    }

    return nullptr;
}