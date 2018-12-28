// environment.h -- interface specification for the semantic environment

// Author: Douglas W. Jones
// Date 10/13/2016 -- framework established
//
// Note, the user must include something before including this file

// Environments are collections of identifier, attribute bindings.
// Bindings may be added to environments.
// The environment permits identifiers to be looked up to find their binding

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <stdint.h>
#include <cstddef>
#include "sets.h"

typedef enum {
    ATTR_BLOCK,  ATTR_CONST, ATTR_FINAL, ATTR_TYPE,
    ATTR_EXCEPT, ATTR_VAR,   ATTR_PROC,  ATTR_FUNC,
    ATTR_REF
} attribute_type;

typedef enum {
    ACCESS_PUBLIC, ACCESS_PRIVATE, ACCESS_RESTRICTED
} access_level;

class Attribute {
public:
	uint32_t identifier;
        attribute_type type;
        access_level access;
        Attribute * attr;
};

// =BUG= subclass for the different types
// for code generation, this class is responsible for managing the registers(alloc/dealloc a register) and
// the variable/constant binding map: (variable/constant)->register and (variable/constant)->stack
class Environment : public Attribute {
public:
    Environment();
	Attribute * lookup(uint32_t identifier, attribute_type t);
        Attribute * lookup(uint32_t identifier,  set32_t types);
	Environment * add(uint32_t identifier, Attribute * a, attribute_type t, access_level ac);
        void print();

    void Out();
    static void EnterBlk();
    static void LeaveBlk();
    static Environment *Head();
private:
    Environment* m_nextEvn;
    int m_blkLevel;
    static Environment* s_Head;
    static int s_blkLevel;
};

#endif // ENVIRONMENT_H
