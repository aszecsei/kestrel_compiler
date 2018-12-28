/* symboltable.h -- symbol table interface specification */

/* Author: Douglas W. Jones
 * Date: 9/12/2016  -- initial version of interface, from Lecture 9
 * Date: 10/10/2016 -- bug fix in declaration of _symbol_table
 */

/* users of this file must first include
 * users should define (probably from a global config file)
 *   SYMBOL_SIZE -- how many distinct symbols are allowed
 *   SYMBOL_HASH -- used in the hash function, relatively prime to SYMBOL_SIZE
 */

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <stdbool.h>
#include <stdint.h>
#include "stringpool.h"
#include "config.h"
#include "log.h"

/* the symbol handle type.  C and C++ don't let us say so, but
 * the value is between 0 and SYMBOL_SIZE-1, inclusive.
 */
typedef uint32_t symbol_handle;

/* initialize the symbol table */
void symbol_init();

/* uninitialize the symbol table */
void symbol_uninit();

string_handle symbol_start( int line, int char_index );
void symbol_append( unsigned char ch );

/* mark the end of the symbol and return its handle */
symbol_handle symbol_lookup();

/* add the null terminated character string s to the symbol table,
 * returning its handle.  This is used during initialization only.
 */
symbol_handle symbol_add( const char * s );

void symbol_put( symbol_handle h, FILE * f );

char* symbol_get( symbol_handle h );

#endif // SYMBOLTABLE_H
