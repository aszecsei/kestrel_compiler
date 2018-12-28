// block.cpp -- implementation of parser/compiler for blocks

// Author: Douglas W. Jones
// Date 10/12/2016 -- framework established

// BNF
// <block> ::= { <block element> [ ; ] }
// <block element> ::= <declaration> | <statement>

#include "block.h"

// start sets
#define START_PUNCS SET32_EMPTY
#define START_KEYS ( to_set32_4( KEY_DO, KEY_IF, KEY_SELECT, KEY_CATCH ) \
		   | to_set32_3( KEY_RAISE, KEY_WHILE, KEY_FOR )         \
		   )
#define START_LEXS to_set32( IDENT )

// follow sets
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS to_set32_4( KEY_END, KEY_ELSE, KEY_CASE, KEY_UNTIL )
#define FOLLOW_LEXS to_set32( ENDFILE )

// internal sets

Block * Block::compile( Environment * e ) {
        Block * newBlock = new Block();
        
	lex_wantinset( START_PUNCS, START_KEYS, START_LEXS, ER_WANT_BLOCK );

	while (lex_isinset( START_PUNCS, START_KEYS, START_LEXS )) {

		if ( (get_lex_this().type == IDENT)
		&&   lex_ispunc( get_lex_next(), PT_COLON ) ) {
			// all declarations begin with ident:
			e = Declaration::compile( e );
		} else {
			// if not a declaration must be a statement
			Statement * s = Statement::compile( e );
		}
		if (lex_ispunc( get_lex_this(), PT_SEMI )) lex_advance();
	}

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS, ER_WANT_ENDBLOK);

	newBlock->attr = e;
	return newBlock;
}
