/*
Match: Simple (and tiny) string matching library


(C) 2021 Bowuigi

zlib license
------------

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Description
-----------

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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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

struct Match_State Match_ParsePattern(const char *pattern);
void Match_DeleteState(struct Match_State *S);
void Match_PrintPattern(struct Match_State S);
bool Match_String(char *pattern, char *string);

#ifdef __cplusplus
}
#endif

#endif
