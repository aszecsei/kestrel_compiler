
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "environment.h"
#include "lexical.h"
#include "lexsupport.h"
#include "reference.h"

typedef enum {
    COMP_EQ, COMP_NOTEQ, COMP_GT, COMP_GTE,
    COMP_LT, COMP_LTE, COMP_IN, COMP_NULL
} compare_type;

typedef enum {
    ADD_PLUS, ADD_MINUS, ADD_OR, ADD_NULL
} add_type;

typedef enum {
    MULT_TIMES, MULT_DIV, MULT_MOD, MULT_AND, MULT_NULL
} mult_type;

typedef enum {
    FACT_MINUS, FACT_NOT, FACT_NULL
} factor_type;

typedef enum {
    VAL_NUMBER, VAL_STRING, VAL_NULL, VAL_REF, VAL_EXP
} value_type;

class Comparand : public Attribute {
public:
    static Comparand * compile( Environment * e );
    
    add_type addType;
    Comparand * next;
};

class Term : public Attribute {
public:
    static Term * compile( Environment * e );
    
    mult_type multType;
    Term * next;
};

class Factor : public Attribute {
public:
    static Factor * compile( Environment * e );
    
    factor_type factorType;
};

class Value : public Attribute {
public:
    static Value * compile( Environment * e );
    
    value_type valueType;
    uint32_t val;
};



class Expression : public Attribute {
public:
    static Expression * compile( Environment * e );

    bool constantValued;
    compare_type compareType;
    Comparand * secondComparand;
};


#endif // EXPRESSION_H
