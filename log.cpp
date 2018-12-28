/* errors.cpp -- logging/error reporting mechanism implementation */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 */

#include "log.h"
#include "symboltable.h"
#include "lexical.h"

string LogHandler::programName;
vector<Log> LogHandler::errors;
vector<Log> LogHandler::warnings;
Log::Level LogHandler::verbosity = Log::ERROR;

/* the error messages
 * NOTE:  this array must have one entry for each
 * member of the error_message enumeration, in exactly the same order
 */
static const char *messageLookup[] = {
		/* ER_BADARG       */ "Bad command line argument",
		/* ER_EXTRAINFILE  */ "Duplicate input file name",
		/* ER_EXTRAOUTFILE */ "Duplicate output file name",
		/* ER_MISSINGFILE  */ "Missing file name",
		/* ER_BADFILE */      "Cannot open input file.",
		/* ER_POOLOVF */      "String pool overflow.",
		/* ER_SYMTAB  */      "Symbol table overflow.",
		/* ER_TOOBIG  */      "Value too large.",
		/* ER_BADSTR  */      "Unclosed string.",
		/* ER_TOOLONG */      "Identifier or string too long.",
		/* ER_SYNTAX  */      "Syntax error.",
		/* ER_ZERORAD */      "The radix of a number cannot be zero.",
		/* ER_WANT_ENDFILE */ "%s found when end of file expected.",
		/* ER_WANT_BLOCK   */ "%s found when declaration or statement expected.",
		/* ER_WANT_ENDBLOK */ "%s found when end of block expected.",
		/* ER_WANT_STATE   */ "%s found when statement expected.",
		/* ER_NO_TYPE      */ "%s no type found ",
		/* ER_INV_TYPE_DEF */ " =BUG=",
		/* ER_FOUND_BUT_WANT */"Found %s, but wanted %s.",
		/* ER_UNDEF_REF */      "Undefined reference to %s of attribute type %s.",
		/* ER_MAX_ERRORS   */ "%s errors have been encountered. Compilation has stopped.",
		/* ER_CUSTOM   	   */ "%s"
};

/* output the help message and exit the program */
void LogHandler::ProgramHelp() {
	std::cout << LogHandler::programName << " compiler [infile] [-o outfile]" << std::endl;
	std::cout << "  infile defaults to standard input" << std::endl;
	std::cout << "  infile = - forces input from standard input" << std::endl;
	std::cout << "  outfile defaults to standard output if infile not given" << std::endl;
	std::cout << "  outfile defaults i.s if infile = i.xxx" << std::endl;
	std::cout << "  outfile = - forces output to standard output" << std::endl;
	std::cout << "  -v = Turns on all debugging and info messages." << std::endl;

	exit(EXIT_SUCCESS);
}

void LogHandler::Print(Log *e) {
	char final_message[256];
	sprintf(final_message, messageLookup[e->error], e->got.c_str(), e->wanted.c_str());

	switch (e->level) {
		case Log::FATAL: {
			errors.push_back(*e);

			if (LogHandler::verbosity >= Log::FATAL) {
				std::cerr << LogHandler::programName << ":" << e->line << ":" << e->char_index << ": ";
				std::cerr << "fatal error: " << final_message << std::endl;
			}

			exit(EXIT_FAILURE);
		}
		case Log::ERROR: {
			errors.push_back(*e);

			if (LogHandler::verbosity >= Log::ERROR) {
				std::cerr << LogHandler::programName << ":" << e->line << ":" << e->char_index << ": ";
				std::cerr << "error: " << final_message << std::endl;
			}

			break;
		}
		case Log::WARN: {
			warnings.push_back(*e);

			if (LogHandler::verbosity >= Log::WARN) {
				std::cout << LogHandler::programName << ":" << e->line << ":" << e->char_index << ": ";
				std::cout << "warning: " << final_message << std::endl;
			}

			break;
		}
		case Log::INFO: {
			if (LogHandler::verbosity >= Log::INFO) {
				std::cout << LogHandler::programName << ":" << e->line << ":" << e->char_index << ": ";
				std::cout << "info: " << final_message << std::endl;
			}
			break;
		}
		case Log::DEBUG: {
			if (LogHandler::verbosity >= Log::DEBUG) {
				std::cout << LogHandler::programName << ":" << e->line << ":" << e->char_index << ": ";
				std::cout << "debug: " << final_message << std::endl;
			}
			break;
		}
		case Log::NONE:
			break;
	}

	if (LogHandler::errors.size() >= 20) {
		Log::Fatal(ER_MAX_ERRORS, get_lex_this().line, get_lex_this().char_index, "20");
	}
}


Log::Log(Level l, error_message error, int line, int ci, const string &got, const string &wanted) : level(l),
																									error(error),
																									line(line),
																									char_index(ci),
																									got(got),
																									wanted(wanted) {
	LogHandler::Print(this);
}
