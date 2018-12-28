/* symboltable.c -- symbol table implementation */

/* Author: Douglas W. Jones
 * Date: 9/12/2016 -- initial version of interface, from Lecture 9
 */
/* this defines
 *   SYMBOL_SIZE -- how many distinct symbols are allowed
 *   SYMBOL_HASH -- used in hash function, relatively prime to SYMBOL_SIZE
 */

#include "symboltable.h"
#include <assert.h>

/* private, the actual location where the text of strings is stored */
#ifdef DYNAMIC_SYMBOLSZ
string_handle* _symbol_table;
unsigned int _symbol_size;
unsigned int _hashfac;
#else
string_handle _symbol_table[SYMBOL_SIZE];
#endif
string_handle get_symbol_table(int index) {
	return _symbol_table[index];
}

/* private, used to accumulate the hash of the symbol */
symbol_handle _symbol_hash;

/* private, tentative handle for the string being accumulated */
string_handle _symbol_string;

/* private, used for error reporting, the line from which the symbol came */
int _symbol_line;

/* private, used for error reporting, the character index from which the symbol came */
int _symbol_char_index;

/* output the text of the symbol to the human-readable file */
void symbol_put( symbol_handle h, FILE * f ) {
	string_put( get_symbol_table(h), f );
}

char* symbol_get( symbol_handle h ) {
	return string_get( get_symbol_table(h) );
}

#ifdef DYNAMIC_SYMBOLSZ
void symbol_grow()
{
	unsigned int prev_sz = _symbol_size;
	_hashfac ++;
	_symbol_size = _hashfac * SYMBOL_BLK;
	if (_symbol_table)
		_symbol_table = (string_handle *)realloc(_symbol_table, _symbol_size * sizeof(string_handle));
	else
		_symbol_table = (string_handle *)malloc(_symbol_size * sizeof(string_handle));
	for (symbol_handle i = prev_sz; i < _symbol_size; i ++)
		_symbol_table[i] = STRING_NULL;

#ifdef _DEBUG
	printf("symbol table grows to %u \n", _symbol_size);
#endif
}
#endif

/* initialize the symbol table */
void symbol_init() {
	string_init();
#ifdef DYNAMIC_SYMBOLSZ
	_symbol_table = NULL;
	_symbol_size = 0;
	_hashfac = 0;
	symbol_grow();
#else
	symbol_handle i;
	for (i = 0; i < SYMBOL_SIZE; i++) _symbol_table[i] = STRING_NULL;
#endif
}

void symbol_uninit() {
#ifdef DYNAMIC_SYMBOLSZ
	free(_symbol_table);
#endif	
	string_uninit();
}

/* setup to accumulate a new symbol, from given line (for error reporting) */
string_handle symbol_start(int line, int char_index) {
	_symbol_hash = 0;
	_symbol_string = string_start( line, char_index );
	_symbol_line = line;
	_symbol_char_index = char_index;
}

/* add one character to the symbol */
void symbol_append(unsigned char ch) {
#ifdef DYNAMIC_SYMBOLSZ
	_symbol_hash = ((_symbol_hash * SYMBOL_HASH ) + (ch * _hashfac)) % _symbol_size;
#else
	_symbol_hash = ((_symbol_hash * SYMBOL_HASH ) + (ch)) % SYMBOL_SIZE;
#endif
	string_append(ch);
}


#ifdef DYNAMIC_SYMBOLSZ
// this is a work around solution for hashkey 0, since the multiplication k' = n*k for k = 0 holds constant 0, then we use a linear search
// it causes the hash table low efficiently working, however with very low probability of 1/_symbol_size, hence we could still have a 
// good complexity expectation value.
symbol_handle symbol_lookup_0hashkey () {
	bool found = false;
	symbol_handle h = 0;
	do {
		for (; h < _symbol_size; h ++) {
			if (_symbol_table[h] == STRING_NULL) {
				_symbol_table[h] = _symbol_string;
				string_accept();
				found = true;
				break;
			}
			else if(string_eq(_symbol_table[h], _symbol_string)) {
				string_reject();
				found = true;
				break;
			}
		}

		if (!found)
			symbol_grow();

	}while (!found);

	return h;
}

symbol_handle symbol_lookup() {
	/* mark the end of the symbol and return its handle */
	string_done();
	if (0 == _symbol_hash)
		return symbol_lookup_0hashkey();
	symbol_handle h0 = _symbol_hash/_hashfac;
	assert(_symbol_hash%_hashfac == 0);
	symbol_handle hi = h0;
	int i = 0;
	for (; i <= _hashfac; i ++, hi = i * h0) {
		if (_symbol_table[hi] == STRING_NULL) {
			/* add symbol to table */
			_symbol_table[hi] = _symbol_string;
			string_accept();
			break;
		}
		else if(string_eq(_symbol_table[hi], _symbol_string)) {
#ifdef _DEBUG
			static int hit = 0;
			hit ++;
			printf("hash hit happens %d times\n", hit);
#endif
			string_reject();
			break;
		}
#ifdef _DEBUG
		else
		{
			static int collision = 0;
			collision ++;
			printf("hash collision happens %d times\n", collision);
		}
#endif
	}

	if (i > _hashfac){
		symbol_grow();
		assert(hi < _symbol_size);
		_symbol_table[hi] = _symbol_string;
		string_accept();
	}

	return hi;
}
#else
symbol_handle symbol_lookup() {
	/* mark the end of the symbol and return its handle */
	string_done();
	symbol_handle place = _symbol_hash;
	for (;;) { /* loop exits by embedded returns */
		if (_symbol_table[place] == STRING_NULL ) {
			/* add symbol to table */
			_symbol_table[place] = _symbol_string;
			string_accept();
			return place;
		}
		if (string_eq( _symbol_table[place], _symbol_string )) {
			/* symbol is already in table */
			string_reject();
			return place;
		}
#ifdef _DEBUG
		else
		{
			static int collision = 0;
			collision ++;
			printf("hash collision happens %d times\n", collision);
		}
#endif
		/* circular increment */
		place = place + 1;
		if (place == SYMBOL_SIZE) place = 0;

		/* if we get back to our starting point, trouble */
		if (place == _symbol_hash) {
			Log::Fatal(ER_SYMTAB, _symbol_line, _symbol_char_index);
		}
	}
}
#endif

/* note:
 * to add a symbol
 *   symbol_start( current_line, char_index )
 *   for each character ch in symbol { symbol_append( ch ) }
 *   handle = symbol_lookup()
 */

symbol_handle symbol_add( const char * s ) {
	/* add the null terminated character string s to the symbol table,
	 * returning its handle.  This is used during initialization only.
         */
	symbol_start( 0, 0 );
	while ( *s != '\0' ) {
		symbol_append( *s );
		s++;
	}
	return symbol_lookup();
}

/* void symbol_put( symbol_handle h, FILE * f ); */
/* implemented in symboltable.h */
