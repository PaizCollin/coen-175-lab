#include "type.h"
#include <cassert>

using namespace std;

Type::Type(int specifier, unsigned indirection) 
    : _specifier(specifier), _indirection(indirection), _declarator(SCALAR) {
}

Type::Type(int specifier, unsigned indirection, unsigned long length)
    : _specifier(specifier), _indirection(indirection), _declarator(ARRAY), _length(length) {
}

Type::Type(int specifier, unsigned indirection, Parameters *parameters)
    : _specifier(specifier), _indirection(indirection), _declarator(FUNCTION), _parameters(parameters) { 
}

Type::Type()
    : _declarator(ERROR) {
}

bool Type::operator==(const Type &rhs) const {
    if(_declarator != rhs._declarator) {
        return false;
    }

    if(_declarator == ERROR) {
        return true;
    }

    if(_specifier != rhs._specifier) {
        return false;
    }

    if(_indirection != rhs._indirection) {
        return false;
    }

    if(_declarator == SCALAR) {
        return true;
    }

    if(_declarator == ARRAY) {
        return _length == rhs._length;
    }

    assert(_declarator == FUNCTION);

    if(!_parameters || !rhs._parameters) {
        return true;
    }

    return *_parameters == *rhs._parameters;
}

bool Type::operator!=(const Type &rhs) const {
    return !operator==(rhs);
}

std::ostream &operator<<(std::ostream &ostr, const Type &type) {
    ostr << type.specifier();

    for(int i = 0; i < type.indirection(); i++) {
        ostr << " *";
    }

    if(type.isScalar()) {
        return ostr;
    } else if(type.isArray()) {
        ostr << "[" << type.length() << "]";
    } else if(type.isFunction()) {
        ostr << "()";
    }

    return ostr;
}