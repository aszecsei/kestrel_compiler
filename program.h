// program.h -- interface specificatio for parser/compiler for programs

// Author: Douglas W. Jones
// Date 10/11/2016 -- framework established
//

// BNF
// <kestrel program> :: <block> <end of file>

#include "lexical.h"
#include "sets.h"
#include "log.h"
#include "block.h"
#include "CodeGen.h"

#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
public:
	static Program *compile(std::string infileName, std::string outfileName);
	// factory method

	// it may well be that programs have no attributes
	// but we'll follow the standard pattern here
};

#endif // PROGRAM_H
