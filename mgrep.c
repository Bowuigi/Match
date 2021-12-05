#include "match.h"
#include <stdio.h>

int main(int argc, char **argv) {
	switch (argc-1) {
		case 0:
			puts("mgrep, search files or stdin using Match patterns");
			break;
		case 1: {
			char *line;
			size_t len;
			while (getline(&line, &len, stdin) != -1) {
				if (Match_String(argv[1], line))
					printf("%s",line);
			}
			break;
		}
		case 2: {
			FILE *fp = fopen(argv[2], "r");
			char *line;
			size_t len;
			while (getline(&line, &len, fp) != -1) {
				if (Match_String(argv[1], line))
					printf("%s",line);
			}
			fclose(fp);
			break;
		}
	}
}
