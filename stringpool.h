/* stringpool.h -- string pool interface specification */

/* Author: Douglas W. Jones
 * Date: 9/9/2016  -- initial version of interface
 * Date: 9/12/2016 -- supports fast interface from Lecture 9
 */

/* users of this file must first include
 *   <stdlib.h>
 * users should define (probably from a global config file)
 *   POOL_SIZE -- how much space should be set aside for text of strings
 */

#ifndef STRINGPOOL_H
#define STRINGPOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "log.h"

typedef uint32_t string_handle;
/* the string handle type.  C and C++ don't let us say so, but
 * the value is between 0 and POOL_SIZE-1, inclusive.
 */

#define STRING_NULL 0
/* the null string handle, refers to no string */

/* private, the actual location where the text of strings is stored */

/* private, used in accumulating a new string (provisionally) */
void string_init();
void string_uninit();

string_handle string_start( int line, int char_index );
void string_append( unsigned char ch );
void string_done();
void string_accept();
void string_reject();

/* note:
 * to add a string to the pool
 *   handle = string_start( current_line )
 *   for each character ch in string { string_append( ch ) }
 *   string_done()
 *   either string_accept() or string_reject() -- symboltable's decision
 */

/* output the text of the string to the human-readable file */
void string_put( string_handle h, FILE * f );

/* return the text of the string */
char* string_get( string_handle h );

/* compare the strings h1 and h2 for textual equality */
bool string_eq( string_handle h1, string_handle h2 );

#endif // STRINGPOOL_H
