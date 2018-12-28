/* config.h -- configuration constants for compiler */

/* Author: Douglas W. Jones
 * Date 9/9/2016 -- created to support the string pool
 * Date 9/12/2016 -- extended to support the symbol table
 */

#ifndef CONFIG_H
#define CONFIG_H

#define DASH '-'
/* the filename path delimeter on this system, - for Unix, / for Windows */

#define DEFAULT_NAME "Kestrel"
/* the default name for this program if no name is given on the command line */
#ifdef DYNAMIC_POOL
#define POOL_GROW 512
#else
#define POOL_SIZE 300
#endif
/* the size of the string pool where all the text of identifiers and strings
 * is stored.  This constant is used in stringpool.h and stringpool.c
 */
#ifdef DYNAMIC_SYMBOLSZ
#define SYMBOL_BLK 64
#else
#define SYMBOL_SIZE 100
#endif
/* the number of distinct symbols and strings permitted in the program
 * This constant is used in symboltable.h and symboltable.c
 */

#define SYMBOL_HASH 7
/* this should be relatively prime to SYMBOL_SIZE, used in the hash function
 * we speculate that values near its square root are good
 * This constant is used in symboltable.h and symboltable.c
 */

#endif // CONFIG_H
