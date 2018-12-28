#include "reference.h"
#include "lexical.h"
#include "lexsupport.h"
#include "sets.h"
#include "expression.h"

Reference * Reference::compile( Environment* e ) {
    Reference * eThis = new Reference();
    eThis->dot = NULL;
    eThis->expList = NULL;
    eThis->refType = REF_NULL;
    
    // =BUG= Lookup a set of possible attributes this refers to
    //       and set that to eThis->attr
    
    set32_t parens = to_set32_3(PT_LPAREN, PT_RBRAKT, PT_LBRACE);
    lex_advance(); // advance over the identifier
    
    if(lex_ispunc(get_lex_this(), PT_ATSIGN)) {
        eThis->refType = REF_AT;
        lex_advance(); // advance over the '@'
    } else if(lex_ispunc(get_lex_this(), PT_DOT)) {
        eThis->refType = REF_DOT;
        lex_advance(); // advance over the '.'
        // =BUG= lookup a set of possible attributes this refers to
        //       and set that to eThis->dot
        lex_advance(); // advance over the identifier
    } else if(lex_ispuncset(get_lex_this(),parens)) {
        eThis->refType = REF_EXPRLIST;
        eThis->expList = ExpressionList::compile(e);
    }
    
    return eThis;
}

ExpressionList * ExpressionList::compile( Environment * e ) {
    ExpressionList * eThis = new ExpressionList();
    eThis->next = NULL;
    
    uint32_t closeParen = PT_RPAREN;
    if(lex_ispunc(get_lex_this(), PT_LBRAKT)) {
        closeParen = PT_RBRAKT;
    } else if(lex_ispunc(get_lex_this(), PT_LBRACE)) {
        closeParen = PT_RBRACE;
    }
    
    lex_advance(); // advance over the lparen
    
    ExpressionList * current = eThis;
    while(true) {
        current->attr = Expression::compile(e);
        
        if(lex_ispunc(get_lex_this(), closeParen)) {
            break;
        }
        
        if(lex_ispunc(get_lex_this(), PT_COMMA)) {
            lex_advance(); // advance over the optional comma
        }
        
        ExpressionList * newCurr = new ExpressionList();
        newCurr->next = NULL;
        current->next = newCurr;
        current = newCurr;
    }
    
    lex_advance(); // advance over the end paren
    
    return eThis;
}
