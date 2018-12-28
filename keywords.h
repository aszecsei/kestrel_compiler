/* keywords.h -- keyword recognition mechanism interface */

/* Author: Douglas W. Jones
 * Date: 8/23/2016 -- pasted from lecture 14 with pro-forma improved comments
 */

#ifndef KEYWORDS_H
#define KEYWORDS_H

#include "symboltable.h"

/* list of all the keywords in the language */
typedef enum {
        KEY_INVALID, /* the null keyword handle */
        KEY_END,        KEY_CONST,      KEY_FINAL,      KEY_TYPE,
        KEY_EXCEPTION,  KEY_VAR,        KEY_PROCEDURE,  KEY_FUNCTION,
        KEY_PRIVATE,    KEY_RESTRICTED, KEY_EXTERNAL,   KEY_ARRAY,
        KEY_SET,        KEY_OF,         KEY_RECORD,     KEY_IF,
        KEY_THEN,       KEY_ELSE,       KEY_SELECT,     KEY_CASE,
        KEY_WHILE,      KEY_DO,         KEY_UNTIL,      KEY_FOR,
        KEY_IN,         KEY_CATCH,      KEY_RAISE,      KEY_ENUM,
	KEY_NULL
} key_handle;
/* the range of valid key_handle values is KEY_INVALID + 1 to KEY_NULL
 * always keep KEY_NULL at the end!
 */

/* initializer for keyword mechanism */
void key_init();

/* output the indicated keyword to the human readable file */
void key_put( key_handle k, FILE * f );

/* return the indicated keyword */
char* key_get( key_handle k );

/* return the keyword handle corresponding to the given symbol handle
 * if the symbol is not a keyword, returns KEY_INVALID
 */
key_handle key_lookup( symbol_handle s );


#endif // KEYWORDS_H
