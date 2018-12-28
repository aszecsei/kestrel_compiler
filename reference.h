/* 
 * File:   reference.h
 * Author: aszecsei
 *
 * Created on October 30, 2016, 3:25 PM
 */

#ifndef REFERENCE_H
#define	REFERENCE_H

#include "environment.h"

typedef enum {
    REF_NULL, REF_AT, REF_DOT, REF_EXPRLIST
} ref_type;

class ExpressionList : public Attribute {
public:
    static ExpressionList * compile( Environment * e );
    
    ExpressionList * next;
};

class Reference : public Attribute {
public:
    static Reference * compile( Environment * e );
    
    ref_type refType;
    Attribute * dot;
    ExpressionList * expList;
};

#endif	/* REFERENCE_H */

