// statement.h -- interface specificatio for parser/compiler for statements

// Author: Douglas W. Jones
// Date 10/15/2016 -- framework established
//

// BNF
// <statement> ::= <if> | <case> | <for loop> | <while loop> | <do loop>
//              |  <exception handler> | <raise> | <procedure call>
//              |  <assignment>
// this grammar splits <loop> and folds <do end> into <do loop>

#ifndef STATEMENT_H
#define STATEMENT_H

#include "lexical.h"
#include "sets.h"
#include "environment.h"
#include "lexsupport.h"

class Statement {
public:
	static Statement * compile( Environment * e );
};


#endif // STATEMENT_H
