#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 1024
#define MAX_LINE 1024

void read_file(FILE *file, long *userLineCount);
void parse_arguments(int *argc, char **argv);
long is_valid_long(char *integer);

/*

	CLT to read a file by lines backward or forward.
	----------------------------

	Example):

	I have a file called awesome.txt and
	I want to read the first 10 lines:

	> rlr awesome.txt 10

	> ... the first N lines available, there does not have to be 10 available.

	Let's read the last 10 lines.

	> rlr awesome.txt -10

	Error Handling):

	Program will automatically check for out of range signed long.

	Program will automatically check for filename not being longer than 1023 characters.

*/

void read_file_reverse(FILE *file, long *userLineCount) {
	char buffer[MAX_LINE];
	long total = 0;
}

void read_file(FILE *file, long *userLineCount) {
	char buffer[MAX_LINE];
	long total = 0;

	// First pass: count total lines
	while (fgets(buffer, sizeof(buffer), file) != NULL) total++;

	long startLine = 0;
	long linesToRead = *userLineCount;

	if (*userLineCount < 0) {
		// Negative N: start total + n lines from top
		linesToRead = -*userLineCount;
		startLine = total > linesToRead ? total - linesToRead : 0;
		linesToRead = total - startLine;
	} else {
		if (*userLineCount > total) linesToRead = total;
	}

	// Rewind file to start
	fseek(file, 0, SEEK_SET);
	long lineCount = 0;

	// Deal with positive.
	while (lineCount < startLine && fgets(buffer, sizeof(buffer), file)) {
		lineCount++;
	}

	// Deal with negative.
	long printed = 0;
	while (printed < linesToRead && fgets(buffer, sizeof(buffer), file)) {
		printf("%s", buffer);
		printed++;
	}
}

long is_valid_long(char *integer) {
	errno = 0;

	char *endpt;
	long val = strtol(integer, &endpt, 10);

	if (errno == ERANGE || *endpt != '\0') {
		errno = EINVAL;
		return 0;
	}

	return val;
}

void parse_arguments(int *argc, char **argv) {
	errno = 0;

	for (int i = 1; i < *argc; i++) {

		if (strcmp(argv[i], "-a") == 0) {

		}
	}
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Too few arguments passed.");
		return 1;
	}

	parse_arguments(&argc, argv);

	char filename[MAX_FILENAME];
	if (strlen(argv[1]) >= MAX_FILENAME) {
		fprintf(stderr, "Filename too long\n");
		return 1;
	}

	strncpy(filename, argv[1], sizeof(filename) - 1);

	FILE *file = fopen(filename, "r");
	if (!file) return 1;

	long userLineCount = is_valid_long(argv[2]);
	if (errno == EINVAL) {
		fprintf(stderr, "Invalid integer.");
		return 1;
	}

	read_file(file, &userLineCount);

	fclose(file);

	return 0;

}
