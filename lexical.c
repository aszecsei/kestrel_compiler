/* lexical.c -- lexical analyzer implementation */

/* Author: Douglas W. Jones
 * Date 8/13/2016 -- existence of file inferred from Lecture 4
 * Date 9/9/2016  -- code for identifiers and strings from Lecture 8
 * Date 9/13/2016 -- works for strings and identifers through Lecture 9
 * Date 9/23/2016 -- works for keywords through Lecture 14
 */

#include "lexical.h"

/******
 * the character classifier
 ******/

typedef enum {
	OTHER=0, WHITESPACE=1, LETTER=2, DIGIT=4, PUNCTUATION=8
} char_type;

/* short forms of character types used in the classifier table */
#define OTH OTHER
#define WIT WHITESPACE
#define LET LETTER
#define DIG DIGIT
#define PUN PUNCTUATION

/* character classifier table */
static const char_type char_class[256] = {
     /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,WIT,WIT,WIT,WIT,WIT,OTH,OTH,
     /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  */
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
     /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /  */
        WIT,OTH,OTH,OTH,OTH,PUN,PUN,OTH,PUN,PUN,PUN,PUN,PUN,PUN,PUN,PUN,
     /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?  */
	DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,DIG,PUN,PUN,PUN,PUN,PUN,OTH,
     /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  */
        PUN,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
     /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _  */
        LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,OTH,PUN,OTH,OTH,
     /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o  */
        OTH,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,
     /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL */
        LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,LET,PUN,PUN,PUN,PUN,OTH,
     /* beyond ascii */
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
        OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,OTH,
};

/* to handle bases greater than 10 */
static const int num_value[256] = {
     /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /  */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
     /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?  */
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1,
     /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  */
	-1, 10, 11, 12, 13, 14, 15, 16, 17,  1, 18, 19,  1, 20, 21,  0,
     /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _  */
	22, 23, 24, 25, 26, 32, 27, 28, 29, 30, 31, -1, -1, -1, -1, -1,
     /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o  */
	-1, 10, 11, 12, 13, 14, 15, 16, 17,  1, 18, 19,  1, 20, 21,  0,
     /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL */
	22, 23, 24, 25, 26, 32, 27, 28, 29, 30, 31, -1, -1, -1, -1, -1,
     /* beyond ascii */
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

/* get rid of short definitions */
#undef OTH
#undef WIT
#undef LET
#undef DIG
#undef PUN

#define ISCLASS(ch,class) (char_class[ch]&(class))

/******
 * the punctuation classifier
 ******/

/* table mapping from characters to punctuation names */
static const punct_type punct_class[256] = {
     /* NUL SOH STX ETX EOT ENQ ACK BEL BS  HT  LF  VT  FF  CR  SO  SI  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /* DLE DC1 DC2 DC3 DC4 NAK SYN ETB CAN EM  SUB ESC FS  GS  RS  US  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*      !   "   #   $   %   &   '   (   )   *   +   ,   -   .   /  */
        PTX,PTX,PTX,PTX,PTX,PT_MOD,
			        PT_AND,
        			    PTX,PT_LPAREN,
        				    PT_RPAREN,
        					PT_TIMES,
        					    PT_PLUS,
							PT_COMMA,
							    PT_MINUS,
								PT_DOT,
								    PT_DIV,
     /*  0   1   2   3   4   5   6   7   8   9   :   ;   <   =   >   ?  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_COLON,
						    PT_SEMI,
							PT_LT,
							    PT_EQUALS,
								PT_GT,
								    PTX,
     /*  @   A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  */
	PT_ATSIGN,
	    PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*  P   Q   R   S   T   U   V   W   X   Y   Z   [   \   ]   ^   _  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_LBRAKT,
        						PTX,PT_RBRAKT,
								PTX,PTX,
     /*  `   a   b   c   d   e   f   g   h   i   j   k   l   m   n   o  */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
     /*  p   q   r   s   t   u   v   w   x   y   z   {   |   }   ~  DEL */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PT_LBRACE,
        						PT_OR,
							    PT_RBRACE,
								PT_NOT,
								    PTX,
     /* beyond ascii */
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
	PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,PTX,
};

/* table mapping from punctuation names to text strings for lex_put */
/* WARNING:  strings must be given in the order enumerated in punct_type */
static const char * punct_name[] = {
    /* PTX */ "?WHAT?", /* this should never happen */
    /* "PT_SEMI   */ ";", /* PT_EQUALS */ "=", /* PT_COLON  */ ":",
    /* "PT_LPAREN */ "(", /* PT_LBRAKT */ "[", /* PT_LBRACE */ "{",
    /* "PT_RPAREN */ ")", /* PT_RBRAKT */ "]", /* PT_RBRACE */ "}",
    /* "PT_COMMA  */ ",", /* PT_ATSIGN */ "@", /* PT_ELIPS  */ "..",
    /* "PT_NOTEQL */ "/=", /*PT_GT     */ ">", /* PT_GE     */ ">=",
    /* "PT_LT     */ "<", /* PT_LE     */ "<=", /*PT_PLUS   */ "+",
    /* "PT_MINUS  */ "-", /* PT_TIMES  */ "*", /* PT_DIV    */ "/",
    /* "PT_MOD    */ "%", /* PT_AND    */ "&", /* PT_OR     */ "|",
    /* "PT_NOT    */ "~", /* PT_DOT    */ "."
};

/******
 * global variables for the lexical analyzer
 ******/

static FILE * infile;  /* the name file */
static int ch;         /* the most recent character */
static int line_number;/* the line number in infile */
static int char_index;/* the char number in infile */
lexeme lex_this;
lexeme lex_next;

/******
 * implementation
 ******/
char* get_punct_type(int type) {
	char* copy = strdup(punct_name[type]);
	return copy;
}

void lex_open( char * f ) {
	/* open file f for name, or use stdin if f is null */
	if (f != NULL) {
		infile = fopen( f, "r" );
		if (infile == NULL) Log::Fatal(ER_BADFILE);
	} else {
		infile = stdin;
	}


	symbol_init();
	key_init(); /* initialize the keyword package */
	

	/* initialize the sliding window */
	ch = fgetc( infile );
	line_number = 1;
	char_index = 1;
	lex_advance();
	lex_advance();
}

void lex_close() {
	symbol_uninit();
	fclose(infile);	
}

void lex_advance() {

	/* slide the lexical analysis window forward */
	lex_this = lex_next;
	while ((ch != EOF) && ISCLASS(ch,WHITESPACE)) {
		/* skip whitespace */
		ch = getc( infile );
		char_index++;
		if (ch == '\n') {
			line_number++;
			char_index = 0;
		}
	}
	lex_next.line = line_number;
	lex_next.char_index = char_index;
	if (ch == EOF) {
		lex_next.type = ENDFILE;
		lex_next.value = 0; /* irrelevant */
	} else if (ISCLASS(ch,LETTER)) {
		/* identifier or possibly a keyword */
		lex_next.type = IDENT;
		symbol_start( line_number, char_index ); /* =BUG= ? */
		do {
			/* save the character */
			symbol_append( ch );
			/* get the next character */
			ch = getc( infile );
			char_index++;
		} while ((ch != EOF) && ISCLASS(ch,LETTER|DIGIT));
		lex_next.value = symbol_lookup();
		{
			/* check to see if it is a keyword */
			key_handle key = key_lookup( lex_next.value );
			if (key != KEY_INVALID) {
				lex_next.type = KEYWORD;
				lex_next.value = key;
			}
		}
		
		if(ch == '\n') {
			line_number++;
			char_index = 0;
		}
	} else if (ISCLASS(ch,DIGIT)) {
		/* decimal digit */
		lex_next.type = NUMBER;
		lex_next.value = 0;
		int base = 10; // default radix
		bool hasSetBase = false;
		do {
			if(ch == '#') {
				if(hasSetBase) {
					/* throw an error? we have something like 13#24#3 */
					Log::Error(ER_SYNTAX, line_number, char_index);
				} else {
					base = lex_next.value;
					if(base == 0) {
						/* throw an error - we have a radix of 0 */
						Log::Error(ER_ZERORAD, line_number, char_index);
                                                /* pretend they meant base 10 */
                                                base = 10;
					}
					lex_next.value = 0;
                                        hasSetBase = true;
				}
			} else if ( lex_next.value > ((UINT32_MAX - (ch - '0'))/10) ) {
				Log::Error(ER_TOOBIG, line_number, char_index);
                        } else {
                                int value = num_value[ch];
                                /* check if our number is greater than our radix */
                                if( value >= base ) {
									Log::Error(ER_TOOBIG, line_number, char_index);
                                } else {
									/* accumulate value of digit */
									lex_next.value = (lex_next.value*base)+value;
                                }
			}

			/* get the next digit */
			ch = getc( infile );
			char_index++;
		} while ((ch != EOF) && ISCLASS(ch,DIGIT) || ch == '#' || ISCLASS(ch,LETTER));
		if(ch == '\n') {
			line_number++;
			char_index = 0;
		}
	} else if ((ch == '"') || (ch == '\'')) {
		/* string */
	       	unsigned char quote = ch; /* remember what quote mark to use */

		/* Keep track of what type of quote was used */
		lex_next.is_single_quote = (quote != '"');

		lex_next.type = STRING;
		symbol_start( line_number, char_index );
		ch = getc( infile );
		char_index++;
		while ((ch != EOF) && (ch != '\n') && (ch != quote)) {
			symbol_append( ch );
			/* get the next letter of the string */
			ch = getc( infile );
			char_index++;
		}
		lex_next.value = symbol_lookup();
		if (ch == quote) {
			/* get the next character after the closing quote */
			ch = getc( infile );
			char_index++;
		} else {
			Log::Error(ER_BADSTR, line_number, char_index);
		}
		
		if (ch == '\n') {
			line_number++;
			char_index = 0;
		}
	} else if (ISCLASS(ch,PUNCTUATION)) {
		int old_ch = ch;
		ch = getc( infile );
		char_index++;
		bool is_valid_two_char = false;
		/* Check to see if the next character is also punctuation */
		if (ISCLASS(ch,PUNCTUATION)) {
			switch(punct_class[old_ch]) {
				case PT_GT:
					// ">="
					if (punct_class[ch] == PT_EQUALS) {
						lex_next.value = PT_GE;
						is_valid_two_char = true;
					}
				break;
				case PT_LT:
					// "<="
					if (punct_class[ch] == PT_EQUALS) {
						lex_next.value = PT_LE;
						is_valid_two_char = true;
					}
				break;
				case PT_DOT:
					// ".."
					if (punct_class[ch] == PT_DOT) {
						lex_next.value = PT_ELIPS;
						is_valid_two_char = true;
					}
				break;
				case PT_DIV:
					// "/="
					if (punct_class[ch] == PT_EQUALS) {
						lex_next.value = PT_NOTEQL;
						is_valid_two_char = true;
					}
				break;
				case PT_MINUS:
					/* Handle comments */
					// "--"
					if (punct_class[ch] == PT_MINUS) {
						while ((ch != EOF) && (ch != '\n')) {
							ch = getc( infile );
						}
						line_number++;
						char_index = 0;
						lex_advance();
					}
				break;
				default:
					lex_next.type = PUNCT;
					lex_next.value = punct_class[old_ch];
				break;
			}

			// If it was valid 2 char punct, get the next char
			if(is_valid_two_char) {
				ch = getc( infile );
				char_index++;
				lex_next.type = PUNCT;
			}
		} else {
			// Was not a two character punctuation mark
			if (ch == '\n') {
				line_number++;
				char_index = 0;
			}
			
			lex_next.type = PUNCT;
			lex_next.value = punct_class[old_ch];
		}
	} else {
		/* =BUG= what about identifiers, strings */
	}
}

void lex_put( lexeme lex, FILE * f ) {
	/* reconstruct the text of the lexeme */
	switch (lex.type) {
	case IDENT:
		symbol_put( (symbol_handle) lex.value, f );
		break;
	case KEYWORD:
		key_put( (key_handle) lex.value, f );
		break;
	case NUMBER:
		fprintf( f, "%" PRId32, lex.value );
		break;
	case PUNCT:
		fputs( punct_name[lex.value], f );
		break;
	case STRING:
		if (lex.is_single_quote) {
			fputc( '\'', f );
			key_put( (key_handle) lex.value, f );
			fputc( '\'', f );
		} else {
			fputc( '"', f );
			symbol_put( lex.value, f );
			fputc( '"', f );
		}
		break;
	case ENDFILE:
		fputs( "EOF", f );
		break;
	}
}

/* reconstruct and return the text of the lexeme */
char* lex_get( lexeme lex ) {
	switch (lex.type) {
		case IDENT:
			return symbol_get( (symbol_handle) lex.value );
		case KEYWORD:
			return key_get( (key_handle) lex.value );
		case NUMBER:
			return (char *) lex.value;
		case PUNCT:
			return (char *) punct_name[lex.value];
		case STRING:
			return symbol_get(lex.value);
		case ENDFILE:
			return "EOF"; // Maybe this should just be empty?
		default:
			return "";
	}
}

// lex_this getter
lexeme get_lex_this() {
	return lex_this;
}
// lex_next getter
lexeme get_lex_next() {
	return lex_next;
}
