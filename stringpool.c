/* stringpool.c -- string pool implementation */

/* Author: Douglas W. Jones
 * Date: 9/9/2016  -- initial version of implementation inferred from .h file
 * Date: 9/12/2016 -- supports fast interface from Lecture 9
 */

#include "stringpool.h"
#include "main.h"

#ifdef DYNAMIC_POOL
unsigned char *_string_pool;
unsigned int _pool_size;
#else
unsigned char _string_pool[POOL_SIZE];
#endif

/* private, the address of the next unused location in the pool */
string_handle _string_limit;

/* private, used in accumulating a new string (provisionally) */
string_handle _string_pos;

/* private, used for error reporting, the line from which the string came */
int _string_line;

/* private, used for error reporting, the character index from which the string came */
int _string_char_index;

/* initializer */
#ifdef DYNAMIC_POOL
void string_init() {
	_pool_size = POOL_GROW;
	_string_pool = (unsigned char *)malloc(_pool_size * sizeof(unsigned char));
	_string_limit = 1;
}

void string_uninit() {
	free(_string_pool);
	_string_pool = NULL;
	_pool_size = 0;
	_string_limit = 0;
}
#else
void string_init() {
	_string_limit = 1;
}
void string_uninit() {
	string_init();
}
#endif


/* setup to accumulate a new string, from given line (for error reporting) */
string_handle string_start(int line, int char_index) {
	_string_line = line;
	_string_char_index = char_index;
	_string_pos = _string_limit + 2;
	return _string_limit;
}

#ifdef DYNAMIC_POOL
void string_append( unsigned char ch )
{
	if (_string_pos > (_pool_size - 1)) {
		_pool_size += POOL_GROW;
		_string_pool = (unsigned char *)realloc(_string_pool, _pool_size);
	}
	_string_pool[_string_pos] = ch;
	_string_pos++;
}
#else
void string_append( unsigned char ch ) {
	if (_string_pos > (POOL_SIZE - 1)) {
		Log::Error(ER_POOLOVF, _string_line, _string_char_index);
	}
	_string_pool[_string_pos] = ch;
	_string_pos++;
}
#endif
/* add one character to the string */

/* mark the end of the string */
void string_done() {
	int length = _string_pos - (_string_limit + 2);
	if (length > 65535) {
		Log::Error(ER_TOOLONG, _string_line, _string_char_index);
		length = 65535;
	}
	_string_pool[_string_limit] = length & 0xFF;
	_string_pool[_string_limit + 1] = length >> 8;
}

/* accept the new string, it is permanently in the string pool */
void string_accept() {
	_string_limit = _string_pos;
}

/* reject the new string, recover the space in the stirng pool */
void string_reject() {
}

void string_put( string_handle h, FILE* f ) {
	/* output the string to the human-readable file */
	int limit = h + 2 + _string_pool[h] + (_string_pool[h + 1] << 8);
	h = h + 2;
	while (h < limit) {
		putc( _string_pool[h], f );
		h = h + 1;
	}
}

char* string_get( string_handle h ) {
    char* tmp = (char *)malloc(256 * sizeof(char*));
    int limit = h + 2 + _string_pool[h] + (_string_pool[h + 1] << 8);
    h = h + 2;

	int i = 0;
    while (h < limit) {
        tmp[i] = _string_pool[h];
        h = h + 1;
		i++;
    }

	return tmp;
}

bool string_eq( string_handle h1, string_handle h2 ) {
	/* compare the strings h1 and h2 for textual equality */
	int limit = h1 + 2 + _string_pool[h1] + (_string_pool[h1 + 1] << 8);
	while (h1 < limit) {
		if (_string_pool[h1] != _string_pool[h2]) return false;
		h1 = h1 + 1;
		h2 = h2 + 1;
	}
	/* tricky code: since the string lengths are encoded in the first 2
	 * characters, the above loop exits early if the string lengths differ
	 */
	return true;
}
