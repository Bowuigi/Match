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

