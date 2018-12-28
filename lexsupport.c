/* lexsupport.c -- lexical analyzer support package implementation */

/* Author: Douglas W. Jones
 * Date 8/19/2016 -- pasted from Lecture 12 with pro-forma improved comments
 * Date 10/17/2016 -- support routines for testing set membership added
 */

#include "lexsupport.h"

/* bool lex_is( lexeme lex, lex_types t ) { */
/* implemented in header file */

/* bool lex_isset( lexeme lex, set32_t s ) { */
/* implemented in header file */

/* bool lex_ispunc( lexeme lex, punct_type t ) { */
/* implemented in header file */

/* bool lex_ispuncset( lexeme lex, set32_t s ) { */
/* implemented in header file */

bool lex_forcepunc( punct_type t ) {
	/* force lex_this to be the punctuation mark t and advance over it */
	if (lex_ispunc( get_lex_this(), t )) {
		lex_advance();
	} else {
		Log::Error(ER_FOUND_BUT_WANT, get_lex_this().line, get_lex_this().char_index,
			 lex_get(get_lex_this()), get_punct_type(t));
		// Note: We have to use lex_get to find the value since even though we are expecting a punct, we might find
		//  something else like an identifier and we want to get the correct value of said lexeme
	}
}

void lex_forcekey(key_handle k) {
	if(lex_iskey(get_lex_this(), k)) {
		lex_advance();
	} else {
		Log::Error(ER_FOUND_BUT_WANT, get_lex_this().line, get_lex_this().char_index,
				   lex_get(get_lex_this()), key_get(k));
	}
}

/* bool lex_iskey( lexeme lex, key_type t ) implemented in header

/* bool lex_iskeyset( lexeme lex, set32_t s ) */
/* implemented in header file */

void lex_gotbutwant( lexeme * lex, error_message e ) {
	/* error: this lexeme e, where e is typically found when x expected */
	Log::Error(e, lex->line, lex->char_index, lex_get(*lex));
}

/* bool lex_isinset( set32_t ps, set32_t ks, set32_t ls ) */
/* implemented in header file */

void lex_wantinset( set32_t ps, set32_t ks, set32_t ls, error_message e ) {
	/* force lex_this to be in one of the sets or gotbutwant e */
	/* typically used to force lex_this into start set or follow set  */
	lexeme temp = get_lex_this();
	if (lex_isinset( ps, ks, ls )) return;
	lex_gotbutwant( &temp, e );
}
