#include "type.h"
#include "lexical.h"
#include "sets.h"
#include "environment.h"
#include "lexsupport.h"

Type * Type::compile(Environment* e) {
    if(lex_iskey(get_lex_this(), KEY_ENUM)) {
        // Enumeration type
        lex_advance(); // Move over enum
        EnumType * newType = new EnumType();

        // =BUG= Handle this

        return newType;
    } else if(lex_iskey(get_lex_this(), KEY_ARRAY)) {
        // Array type
        lex_advance(); // Move over array

        ArrayType * newType = new ArrayType();

        // For the "array of <type> case
        if(lex_iskey(get_lex_this(), KEY_OF)) {
            lex_advance(); // move over of
            newType->attr = Type::compile(e);
        } else {
            newType->indexType = Type::compile(e);

            // optional "of" in between the two types
            if(lex_iskey(get_lex_this(), KEY_OF)) {
                lex_advance(); // move over "of"
            }

            newType->attr = Type::compile(e);
        }

        return newType;
    } else if(lex_iskey(get_lex_this(), KEY_SET)) {
        lex_advance(); // move over "set"
        // optional "of"
        if(lex_iskey(get_lex_this(), KEY_OF)) {
            lex_advance(); // move over "of"
        }
        SetType * newType = new SetType();
        newType->attr = Type::compile(e);
        return newType;
    } else if(lex_iskey(get_lex_this(), KEY_RECORD)) {
        // Record type
        lex_advance(); // move over "record"
        // =BUG= Handle this
        return NULL;
    } else if(get_lex_this().type == PUNCT && get_lex_this().value == PT_ATSIGN) {
        // Pointer type
        lex_advance(); // move over @
        PointerType * newType = new PointerType();
        newType->attr = Type::compile(e);
        return newType;
    } else {
        // This might be either a subrange or a reference
        // Test whether the attribute is a type or a variable
        set32_t lookups = to_set32_4(ATTR_TYPE, ATTR_VAR, ATTR_CONST, ATTR_FINAL) | to_set32(ATTR_REF);
        // =BUG= Determine how to tell the difference between the two
        // For now: assume it's a reference
        Attribute * mLookup = e->lookup(get_lex_this().value, lookups);
        if(mLookup != NULL && mLookup->type == ATTR_TYPE) {
            ReferenceType * newType = new ReferenceType();
            newType->attr = mLookup;
            lex_advance(); // advance over the identifier
            return newType;
        } else {
            // it's a subrange
            SubrangeType * newType = new SubrangeType();
            newType->leftExpr = Expression::compile(e);
            if(lex_ispunc(get_lex_this(), PT_ELIPS)) {
                lex_advance(); // advance over ellipsis
                newType->rightExpr = Expression::compile(e);
            }
            return newType;
        }
    }
    Log::Error(ER_CUSTOM,get_lex_this().line, get_lex_this().char_index,"Illegal Environment Initialization");
    //  We should never get here...almost certainly an error
    lex_advance(); // ignore whatever's causing the error i guess
    return NULL;
}