/*
	Test: Test Bowuigi/Match to see if it works properly

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
*/

#include "match.h"
#include <stdio.h>

#define TEST_MATCH(pattern, string) printf("Pattern '%s'\nString '%s'\nMatches? %i\n\n", pattern, string, Match_String(pattern, string))

int main() {
	TEST_MATCH("1234", "1234");
	TEST_MATCH("1234", "12345678");
	TEST_MATCH("1234", "012345678");
	TEST_MATCH("%a%a%a%a%a world", "hello world");
	TEST_MATCH("%n%n%n%n", "1234");
	TEST_MATCH("%x", "abcdef1234");
	TEST_MATCH("%p%p%p%p", ".,;:");
	TEST_MATCH("WRONG", "RIGHT");
	TEST_MATCH("%A", "that should fail on any condition");
	TEST_MATCH("%5a", "should match five chars");
	TEST_MATCH("%2a", "t");
}

