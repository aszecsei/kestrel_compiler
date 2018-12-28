
#include "expression.h"

/*
 * <expression> ::= <comparand> [ <comparing operator> <comparand> ]
 * <comparand> ::= <term> { <adding operator> <term> }
 * <term> ::= <factor> { <multiplying operator> <factor> }
 */

Expression * Expression::compile(Environment* e) {
    Expression * eThis = new Expression();
    eThis->compareType = COMP_NULL;
    eThis->secondComparand = NULL;
    
    eThis->attr = Comparand::compile(e);
    
    // if there's a comparing operator, add it
    if(lex_ispunc(get_lex_this(), PT_EQUALS)) {
        eThis->compareType = COMP_EQ;
    } else if(lex_ispunc(get_lex_this(), PT_NOTEQL)) {
        eThis->compareType = COMP_NOTEQ;
    } else if(lex_ispunc(get_lex_this(), PT_GT)) {
        eThis->compareType = COMP_GT;
    } else if(lex_ispunc(get_lex_this(), PT_GE)) {
        eThis->compareType = COMP_GTE;
    } else if(lex_ispunc(get_lex_this(), PT_LT)) {
        eThis->compareType = COMP_LT;
    } else if(lex_ispunc(get_lex_this(), PT_LE)) {
        eThis->compareType = COMP_LTE;
    } else if(lex_iskey(get_lex_this(), KEY_IN)) {
        eThis->compareType = COMP_IN;
    }
    
    if(eThis->compareType != COMP_NULL) {
        lex_advance();
        eThis->secondComparand = Comparand::compile(e);
    }

    return eThis;
}

Comparand * Comparand::compile( Environment * e ) {
    Comparand * eThis = new Comparand();
    eThis->attr = Term::compile(e);
    eThis->addType = ADD_NULL;
    eThis->next = NULL;
    
    if(lex_ispunc(get_lex_this(), PT_PLUS)) {
        eThis->addType = ADD_PLUS;
    } else if(lex_ispunc(get_lex_this(), PT_MINUS)) {
        eThis->addType = ADD_MINUS;
    } else if(lex_ispunc(get_lex_this(), PT_OR)) {
        eThis->addType = ADD_OR;
    }
    
    if(eThis->addType != ADD_NULL) {
        lex_advance();
        eThis->next = Comparand::compile(e);
    }
    
    return eThis;
}

Term * Term::compile( Environment * e ) {
    Term * eThis = new Term();
    eThis->attr = Factor::compile(e);
    eThis->multType = MULT_NULL;
    eThis->next = NULL;
    
    if(lex_ispunc(get_lex_this(), PT_TIMES)) {
        eThis->multType = MULT_TIMES;
    } else if(lex_ispunc(get_lex_this(), PT_DIV)) {
        eThis->multType = MULT_DIV;
    } else if(lex_ispunc(get_lex_this(), PT_MOD)) {
        eThis->multType = MULT_MOD;
    } else if(lex_ispunc(get_lex_this(), PT_AND)) {
        eThis->multType = MULT_AND;
    }
    
    if(eThis->multType != MULT_NULL) {
        lex_advance();
        eThis->next = Term::compile(e);
    }
    
    return eThis;
}

Factor * Factor::compile( Environment * e ) {
    Factor * eThis = new Factor();
    eThis->factorType = FACT_NULL;
    
    if(lex_ispunc(get_lex_this(), PT_MINUS)) {
        eThis->factorType = FACT_MINUS;
    } else if(lex_ispunc(get_lex_this(), PT_NOT)) {
        eThis->factorType = FACT_NOT;
    }
    if(eThis->factorType != FACT_NULL) {
        lex_advance();
    }
    
    eThis->attr = Value::compile(e);
    
    return eThis;
}

Value * Value::compile( Environment * e ) {
    Value * eThis = new Value();
    
    set32_t parens = to_set32_3(PT_LPAREN, PT_LBRAKT, PT_LBRACE);
    
    if(lex_islex(get_lex_this(), NUMBER)) {
        eThis->valueType = VAL_NUMBER;
        eThis->val = get_lex_this().value;
        lex_advance();
    } else if(lex_islex(get_lex_this(), STRING)) {
        eThis->valueType = VAL_STRING;
        eThis->val = get_lex_this().value;
        lex_advance();
    } else if(lex_iskey(get_lex_this(), KEY_NULL)) {
        eThis->valueType = VAL_NULL;
        lex_advance();
    } else if(lex_islex(get_lex_this(), IDENT)) {
        eThis->valueType = VAL_REF;
        eThis->attr = Reference::compile(e);
    } else if(lex_ispuncset(get_lex_this(), parens)) {
		uint32_t open_paren_type = get_lex_this().value;

        lex_advance(); // advance over the begin paren
        eThis->valueType = VAL_EXP;
        eThis->attr = Expression::compile(e);

		// A little trick to get the closing punct type, all closing punct's are offset by 3
		lex_forcepunc((punct_type)(open_paren_type + 3)); // Advance over the closing paren
    }
    
    return eThis;
}