/*
Bowuigi/Match: Simple (and tiny) string matching library

Uses syntax similar to the Lua one, the options are the following:

+-------+--------------+
| Token |   Matches    |
|-------+--------------|
|  %a   |   Anything   |
|  %h   | Alphanumeric |
|  %l   |    Letters   |
|  %n   |    Numbers   |
|  %p   |  Punctuation |
|  %s   |    Spaces    |
|  %u   |   Uppercase  |
|  %x   |   Hex [0-F]  |
+-------+--------------+

If the tokens are in uppercase, then that match would be inverted, for example, %n matches numbers, but %N matches anything but numbers.

If the token doesn't start with % then it is just a normal exact match

If the token is %%, then it matches '%'

Usage
-----

Although there is a lot of functions here, the only one that you might want to use is Match_String, since the other ones are for expanding the library
*/

#ifndef MATCH_H
#define MATCH_H

#ifndef MATCH_NO_STDIO
#include <stdio.h>
#endif

#ifndef MATCH_NO_STDBOOL
#include <stdbool.h>
#endif

#ifndef MATCH_NO_STDLIB
#include <stdlib.h>
#endif

#ifndef MATCH_NO_CTYPE
#include <ctype.h>
#endif

#define MATCH_ERR(cond, msg) \
	if (cond==true) {        \
		fprintf(stderr, "Match, fatal: %s", msg); \
		exit(1);             \
	}

enum Match_Type {
		M_ANY,
		M_ALPHANUM,
		M_LETTER,
		M_NUM,
		M_PUNCT,
		M_SPACE,
		M_UPPER,
		M_HEX,
		M_EXACT
};

struct Match_Char {
	enum Match_Type type;
	bool isUpper;
	char c;
};

struct Match_State {
	struct Match_Char *c;
	size_t length;
};

struct Match_State Match_ParsePattern(const char *pattern) {
	bool nextIsSpecial = false;

	size_t i = 0;
	size_t size = 10;

	struct Match_Char *chars = malloc(size*sizeof(struct Match_Char));

	while (*pattern) {
		if (i>size) {

			size *= 2;
			chars = realloc(chars, size*sizeof(struct Match_Char));

			MATCH_ERR(chars==NULL,"Out of memory");
		}
		chars[i].isUpper = isupper(*pattern);

		if (*pattern =='%' && !nextIsSpecial) {
			nextIsSpecial = true;
			pattern++;
			continue;
		}

		chars[i].type = M_EXACT;

		if (nextIsSpecial) {
			switch (*pattern) {
				case 'a':
					chars[i].type = M_ANY;
					break;
				case 'h':
					chars[i].type = M_ALPHANUM;
					break;
				case 'l':
					chars[i].type = M_LETTER;
					break;
				case 'n':
					chars[i].type = M_NUM;
					break;
				case 'p':
					chars[i].type = M_PUNCT;
					break;
				case 's':
					chars[i].type = M_SPACE;
					break;
				case 'u':
					chars[i].type = M_UPPER;
					break;
				case 'x':
					chars[i].type = M_HEX;
					break;
				default:
					chars[i].type = M_EXACT;
					break;
			}
		}

		nextIsSpecial = false;

		if (chars[i].type==M_EXACT)
			chars[i].c = *pattern;

		pattern++;
		i++;
	}

	return (struct Match_State){.c=chars, .length=i};
}

void Match_DeleteState(struct Match_State *S) {
	free(S->c);
	S->length = 0;
	S = NULL;
}

void Match_PrintPattern(struct Match_State S) {
	for (size_t i=0; i<S.length; i++) {
		if (S.c[i].isUpper && S.c[i].type!=M_EXACT)
			printf("Inverted ");

		switch (S.c[i].type) {
			case M_ANY:
				puts("Any character");
				break;
			case M_ALPHANUM:
				puts("Alphanumeric character");
				break;
			case M_LETTER:
				puts("Letter");
				break;
			case M_NUM:
				puts("Number");
				break;
			case M_PUNCT:
				puts("Punctuation");
				break;
			case M_SPACE:
				puts("Space");
				break;
			case M_UPPER:
				puts("Uppercase character");
				break;
			case M_HEX:
				puts("Hex [0-F] character");
				break;
			case M_EXACT:
				printf("Character '%c'\n", S.c[i].c);
				break;
		}
	}
}

bool Match_String(char *pattern, char *string) {
	struct Match_State S = Match_ParsePattern(pattern);

	bool matches=true;
	for (size_t i=0; i<sizeof(string)-sizeof(string[0]); i++) {
		switch (S.c[i].type) {
			case M_ANY      : matches = true; break;
			case M_ALPHANUM : matches = isalnum(string[i])      ; break;
			case M_LETTER   : matches = isalpha(string[i])      ; break;
			case M_NUM      : matches = isdigit(string[i])      ; break;
			case M_PUNCT    : matches = ispunct(string[i])      ; break;
			case M_SPACE    : matches = isspace(string[i])      ; break;
			case M_UPPER    : matches = isupper(string[i])      ; break;
			case M_HEX      : matches = isxdigit(string[i])     ; break;
			case M_EXACT    : matches = (S.c[i].c == string[i]) ; break;
		}

		if (matches == false) {
			Match_DeleteState(&S);
			return false;
		}
	}

	Match_DeleteState(&S);
	return true;
}

#endif
