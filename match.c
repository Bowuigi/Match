#include "match.h"

struct Match_State Match_ParsePattern(const char *pattern) {
	bool nextIsSpecial = false;

	size_t i = 0;
	size_t size = 10;

	struct Match_Char *chars = malloc(size*sizeof(struct Match_Char));

	while (*pattern) {
		if (i>size) {

			size *= 2;
			chars = realloc(chars, size*sizeof(struct Match_Char));

			MATCH_ERR(chars==NULL,"Out of memory")
		}
		chars[i].isUpper = isupper(*pattern);

		if (*pattern =='%' && !nextIsSpecial) {
			nextIsSpecial = true;
			pattern++;
			continue;
		}

		chars[i].type = M_EXACT;
		chars[i].n = 1;

		if (nextIsSpecial) {
			char repeat[4] = {0};
			size_t n = 0;

			while (isdigit(*pattern)) {
				if (n < 4) {
					repeat[n] = *pattern;
					n++;
				}
				pattern++;
			}

			long num_times = strtol(repeat, NULL, 10);

			if (num_times > 0) {
				chars[i].n = num_times;
			}

			switch (tolower(*pattern)) {
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

	size_t str_len = strlen(string);
	size_t pat_len = S.length;

	bool matches = true;
	bool skip_char = false;

	size_t str_i = 0;
	size_t pat_i = 0;

	for (; str_i < str_len; str_i++, skip_char = false) {
		switch (S.c[pat_i].type) {
			case M_ANY      : matches = true                            ; break ;
			case M_ALPHANUM : matches = isalnum(string[str_i])          ; break ;
			case M_LETTER   : matches = isalpha(string[str_i])          ; break ;
			case M_NUM      : matches = isdigit(string[str_i])          ; break ;
			case M_PUNCT    : matches = ispunct(string[str_i])          ; break ;
			case M_SPACE    : matches = isspace(string[str_i])          ; break ;
			case M_UPPER    : matches = isupper(string[str_i])          ; break ;
			case M_HEX      : matches = isxdigit(string[str_i])         ; break ;
			case M_EXACT    : matches = (S.c[pat_i].c == string[str_i]) ; break ;
		}

		if (S.c[pat_i].isUpper && S.c[pat_i].type != M_EXACT) matches = !matches;

		if (str_i >= str_len - 1 && S.c[pat_i].n > 1) break;

		if (matches == true) {
			if (pat_i >= pat_len - 1) {
				Match_DeleteState(&S);
				return true;
			}

			S.c[pat_i].n--;
			if (S.c[pat_i].n > 0) skip_char = true;
		}

		if (matches == false) {
			skip_char = true;
			pat_i = 0;
		}

		if (skip_char == false) pat_i++;
	}

	Match_DeleteState(&S);
	return false;
}
