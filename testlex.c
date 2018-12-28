/* testlex.c -- lexical analyzer test framework main program */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/7/2016  -- wrote main program
 * Date 9/30/2016  -- make it compatible with main.c from Kestrel compiler
 */

#include <stdio.h>
#include <stdlib.h>

#include "lexical.h"
#include "main.h"

int main(int argc, char* argv[]) {
	/* the main program for testlex */
	LogHandler::programName = DEFAULT_NAME;
	
	char** files = (char **)malloc(argc * sizeof(char**));
	int numf;

	if (1 == argc)
	{
		files[0] = NULL;
		numf = 1;
	}
	else
	{
		numf = argc - 1;
		for (int i = 0; i < numf; i ++)
			files[i] = argv[i+1];

	}

	for (int i_f = 0; i_f < numf; i_f ++)
	{
		lex_open( files[i_f] ); /* default to stdin if argv[1] not present */
		do {
			lex_put( get_lex_this(), stdout );
			putchar( '\n' ); /* output each lexeme on a new line */
			lex_advance();
		} while (get_lex_this().type != ENDFILE);
		lex_close();
	}
	

	free(files);
	return 0;
}
