// program.cpp -- implementation of parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established

// BNF
// <kestrel program> :: <block> <end of file>

#include "program.h"

/* follow set for programs */
#define FOLLOW_PUNCS SET32_EMPTY
#define FOLLOW_KEYS SET32_EMPTY
#define FOLLOW_LEXS to_set32( ENDFILE )

Program * Program::compile(std::string infileName, std::string outfileName) {

	Environment * e = NULL;
        
        // =BUG= Set up default environment (putstring def, etc)

	CodeGen::Prologue(infileName, outfileName);
	List<uint32_t> lstParamIds = List<uint32_t>();

	CodeGen::StartFunc("main", lstParamIds, e);
	Block * b = Block::compile( e );
	CodeGen::Return(NULL, 0, e);

	CodeGen::Epilogue();

	lex_wantinset( FOLLOW_PUNCS, FOLLOW_KEYS, FOLLOW_LEXS,
		       ER_WANT_ENDFILE
	);
        
	((Environment *)b->attr)->print();

	return NULL;
}
