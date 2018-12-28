/* lexical.h -- lexical analyzer interface specificaton */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- pasted from Lecture 4 with pro-forma improved comments
 */

#ifndef LEXICAL_H
#define LEXICAL_H

#include "symboltable.h"
#include "keywords.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"

typedef enum { IDENT, KEYWORD, NUMBER, STRING, PUNCT, ENDFILE } lex_types;

/* names for specific punctuation marks */
typedef enum {
    PTX       /* not a punctuation mark */,
    PT_SEMI   /* ; */,   PT_EQUALS /* = */,   PT_COLON  /* : */, 
    PT_LPAREN /* ( */,   PT_LBRAKT /* [ */,   PT_LBRACE /* { */,
    PT_RPAREN /* ) */,   PT_RBRAKT /* ] */,   PT_RBRACE /* } */, 
    PT_COMMA  /* , */,   PT_ATSIGN /* @ */,   PT_ELIPS  /* .. */,
    PT_NOTEQL /* /= */,  PT_GT     /* > */,   PT_GE     /* >= */, 
    PT_LT     /* < */,   PT_LE     /* <= */,  PT_PLUS   /* + */,
    PT_MINUS  /* - */,   PT_TIMES  /* * */,   PT_DIV    /* / */, 
    PT_MOD    /* % */,   PT_AND    /* & */,   PT_OR     /* | */, 
    PT_NOT    /* ~ */,   PT_DOT    /* . */
} punct_type;

typedef struct lexeme {
	lex_types type;	/* type of this lexeme */
	uint32_t value;	/* value of this lexeme, meaning depends on type */
	bool is_single_quote;
	int line;		/* line number from which this lexeme came */
	int char_index;		/* start char from which this lexeme came */
} lexeme;

char* get_punct_type(int type); //helper function to get a type of punctuation
void lex_open( char * f );
void lex_close();
void lex_advance();
void lex_put( lexeme lex, FILE * f );
char* lex_get( lexeme lex );

lexeme get_lex_this();  /* return the current lexeme */
lexeme get_lex_next();	/* return the next lexeme */

#endif // LEXICAL_H
