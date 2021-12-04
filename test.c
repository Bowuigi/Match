#include "match.h"
#include <stdio.h>

#define TEST_MATCH(pattern, string) printf("Pattern '%s'\nString '%s'\nMatches? %i\n\n", pattern, string, Match_String(pattern, string));

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
}

/*
Pattern '1234'
String '1234'
Matches? 1

Pattern '1234'
String '12345678'
Matches? 1

Pattern '1234'
String '012345678'
Matches? 0

Pattern '%a%a%a%a%a world'
String 'hello world'
Matches? 1

Pattern '%n%n%n%n'
String '1234'
Matches? 0

Pattern '%x'
String 'abcdef1234'
Matches? 0

Pattern '%p%p%p%p'
String '.,;:'
Matches? 0

*/
