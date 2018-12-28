// block.h -- interface specificatio for parser/compiler for blocks

// Author: Douglas W. Jones
// Date 10/13/2016 -- framework established
//

// BNF
// <block> ::= { <block element> [ ; ] }
// <block element> ::= <declaration> | <statement>

#ifndef BLOCK_H
#define BLOCK_H

#include "lexical.h"
#include "sets.h"
#include "environment.h"
#include "declaration.h"
#include "statement.h"

class Block : public Attribute {
public:
	static Block * compile( Environment * e );
	// factory method

	// =BUG= blocks certainly have attributes, they are missing here
};

#endif // BLOCK_H
