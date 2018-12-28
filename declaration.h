// declaration.h -- interface specificatio for parser/compiler for declarations

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established
//

// BNF
// <declaration> ::= <identifier> : [ <private> | <restricted> ] <declarator>

#ifndef DECLARATION_H
#define DECLARATION_H

#include "lexical.h"
#include "sets.h"
#include "environment.h"
#include "lexsupport.h"
#include "type.h"

typedef enum {
    FORM_REF, FORM_VAR, FORM_FINAL
} formal_parameter_type;
class FormalParameterList : public Attribute { 
public:
	static FormalParameterList * compile( Environment * e );
	formal_parameter_type paramType;
        FormalParameterList * nextParam;
        Environment * internalEnv;
};

class Procedure : public Attribute {
public:
        static Procedure * compile( Environment * e );
        FormalParameterList * parameters;
};

class Function : public Attribute {
public:
    static Function * compile( Environment * e );
    FormalParameterList * parameters;
    Type * returnType;
};

class Body : public Attribute { 
public:
	static Body * compile( Environment * e );
	// factory method?

	// =BUG= add attributes
};

class Declaration {
public:
	static Environment * compile( Environment * e );
	// factory method?
	// =BUG= perhaps Declaration could be a subclass of Environment?

	// =BUG= do declarations have any attributes?  they are missing here
};

#endif // DECLARATION_H
