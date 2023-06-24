#include "checker.h"
#include "scope.h"
#include "lexer.h"
#include "tokens.h"

using namespace std;

Scope *globalScope = nullptr;
Scope *curScope = nullptr;

const string e1 = "redefinition of '%s'";
const string e2 = "conflicting types for '%s'";
const string e3 = "redeclaration of '%s'";
const string e4 = "'%s' undeclared";
const string e5 = "'%s' has type void";

void openScope() {

    if(globalScope == nullptr) {
        Scope *newScope = new Scope(nullptr);
        globalScope = newScope;
        curScope = newScope;
    } else {
        Scope *newScope = new Scope(curScope);
        curScope = newScope;
    }
    
    return;
    //cout << "open scope" << endl;
}

void closeScope() {
    Scope *temp = curScope;
    curScope = curScope->enclosing();
    free(temp);
    return;
    //cout << "close scope" << endl;
}

void defineFunction(const std::string &name, const Type &type) {

    Symbol *newFunc = new Symbol(name, type);

    // find if func previously declared in global scope
    Symbol *prior = globalScope->find(name);

    // if not previously declared, return
    if(prior == nullptr) {
        globalScope->insert(newFunc);
        return;
    }

    // if redefinition, E1 and replace definition
    if(prior->type().parameters() != nullptr) {
        report(e1, name);
        globalScope->remove(name);
        globalScope->insert(newFunc);
        return;
    }

    // if conflicting declaration (different types), E2
    if(prior->type() != type) {
        report(e2, name);
        return;
    }

    //cout << name << ": " << type << endl;
}

void declareFunction(const std::string &name, const Type &type) {

    Symbol *newFunc = new Symbol(name, type);

    // find if func previously declared in global scope
    Symbol *prior = globalScope->find(name);

    // if not previously declared, return
    if(prior == nullptr) {
        globalScope->insert(newFunc);
        return;
    }

    // if conflicting declaration (different types), E2
    if(prior->type() != type) {
        report(e2, name);
        return;
    }

    return;
    //cout << name << ": " << type << endl;
}

void declareVariable(const std::string &name, const Type &type) {

    Symbol *symbol = curScope->find(name);

    if(symbol == nullptr) {
        if(type.specifier() == VOID && type.indirection() == 0 && !name.empty()) {
            report(e5, name);
            return;
        }
        curScope->insert(new Symbol(name, type));
    } else if(curScope->enclosing() != nullptr) {
        report(e3, name);
    } else if(symbol->type() != type) {
        report(e2, name);
    }

    return;

    // Symbol *newVar = new Symbol(name, type);

    // // if void && not a pointer && has a name, E5
    // if(type.specifier() == VOID && type.indirection() == 0 && !name.empty()) {
    //     report(e5, name);
    //     curScope->insert(newVar);
    //     return;
    // }

    // // find if var previously declared in current scope
    // Symbol *prior = curScope->find(name);

    // // if prev declared
    // if(prior != nullptr) {
    //     // if global scope && conflicting types, E2
    //     if(curScope == globalScope && prior->type() != type) {
    //         report(e2, name);
    //         return;
    //     }

    //     // if not global scope, E3
    //     if(curScope != globalScope) {
    //         report(e3, name);
    //         return;
    //     }
    // }

    // curScope->insert(newVar);

    // return;

    //cout << name << ": " << type << endl;
}

void checkIdentifier(const std::string &name) {

    Symbol *prior = curScope->lookup(name);

    // if not previously declared, E4
    if(prior == nullptr) {
        report(e4, name);
    }

    return;
}
