/* log.h -- logging/error reporting mechanism interface specificaton */

/* Author: Douglas W. Jones
 * Date 9/7/2016 -- pasted from Lecture 7 with pro-forma improved comments
 * Date 9/9/2016 -- added errors raised by string pool
 * Date 9/12/2016 -- added errors raised by symbol table
 */

#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

typedef enum {
	/* intended for use in calls to error_fatal */
	ER_BADARG,
	ER_EXTRAINFILE,
	ER_EXTRAOUTFILE,
	ER_MISSINGFILE,
	ER_BADFILE,
	ER_POOLOVF,
	ER_SYMTAB,
	/* intended for use in calls to error_warn */
	ER_TOOBIG,
	ER_BADSTR,
	ER_TOOLONG,
	ER_SYNTAX,
	ER_ZERORAD,
	/* intended for as suffixes on got-but-want messages */
	ER_WANT_ENDFILE,
	ER_WANT_BLOCK,
	ER_WANT_ENDBLOK,
	ER_WANT_STATE,
	/*for got but want in lex_forcepunc in lexsupport*/
	ER_NO_TYPE,
	ER_INV_TYPE_DEF,
	ER_FOUND_BUT_WANT,
	ER_UNDEF_REF,
	ER_MAX_ERRORS,
	ER_CUSTOM
} error_message;

class Log {
public:
	enum Level {
		NONE = 0,
		FATAL = 1,
		ERROR = 2,
		WARN = 3,
		INFO = 4,
		DEBUG = 5
	};

	Log(Log::Level l, error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "");

	static Log Fatal(error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "") {
		return Log(FATAL, error, line, ci, got, wanted);
	};

	static Log Error(error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "") {
		return Log(ERROR, error, line, ci, got, wanted);
	};

	static Log Warn(error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "") {
		return Log(WARN, error, line, ci, got, wanted);
	};

	static Log Info(error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "") {
		return Log(INFO, error, line, ci, got, wanted);
	};

	static Log Debug(error_message error, int line = 0, int ci = 0, const string &got = "", const string &wanted = "") {
		return Log(DEBUG, error, line, ci, got, wanted);
	};


	error_message error;
	string got;
	string wanted;
	int line;
	int char_index;
	Level level;
};

class LogHandler {
public:
	static string programName;
	static vector<Log> errors;
	static vector<Log> warnings;
	static Log::Level verbosity;
	static void Print(Log *e);
	static void ProgramHelp();
};

#endif // ERRORS_H
