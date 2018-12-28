/* 
 * File:   type.h
 * Author: aszecsei
 *
 * Created on November 1, 2016, 6:53 PM
 */

#ifndef TYPE_H
#define	TYPE_H

#include "environment.h"
#include "expression.h"

class Type : public Attribute { 
public:
	static Type * compile( Environment * e );
};

class ReferenceType : public Type {
    
};

class EnumType : public Type {
    // =BUG= We need a list of possible enum values?
};

class SubrangeType : public Type {
public:
    // =BUG= We need more - we have to reference 2 expressions?
    Expression * leftExpr;
    Expression * rightExpr;
};

class PointerType : public Type {
    
};

class ArrayType : public Type {
public:
    Type * indexType;
};

class SetType : public Type {
    
};

class RecordType : public Type {
    // =BUG= We definitely need more here to define a record type
};

#endif	/* TYPE_H */

