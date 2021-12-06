/*
	MGr: A grep like program used to demonstrate the capabilities of Bowuigi/Match

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

int main(int argc, char **argv) {
	switch (argc-1) {
		case 0:
			puts("mgrep, search files or stdin using Bowuigi/Match patterns");
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
