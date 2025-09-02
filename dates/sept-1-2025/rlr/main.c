#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 1024
#define MAX_LINE 1024

void read_file(FILE *file, long n);
void read_file_reverse(FILE *file, long n);
void parse_arguments(int *argc, char **argv);
long is_valid_long(char *integer);

char help[] = "CLT to read a file by lines backward or forward.\n"
              "Usage:\n"
              "  rlr <filename> <n>\n"
              "    n > 0 : forward from start\n"
              "    n < 0 : backward from end\n";

/*

	CLT to read a file by lines backward or forward.
	----------------------------

	Example):

	I have a file called awesome.txt and
	I want to read the first 10 lines:

	> rlr awesome.txt 10

	> ... the first N lines available, there does not have to be 10 available.

	Lets read the last 10 lines.

	> rlr awesome.txt -10

	Error Handling):

	Program will automatically check for out of range signed long.

	Program will automatically check for filename not being longer than 1023 characters.

	Though I did not know it this morning, or maybe belive it, programs like this are
	indeed useful beyond my manual use. A log monitoring program could use this program
	to get the last N lines of a file, where it is meant to monitor those certain number
	of lines and parse then print them somewhere (maybe for a human to read).
	Cool! Thank you M.K.

*/

void read_file(FILE *file, long n) {
	char buffer[MAX_LINE];

	// error handling for reuse
	// call for this check is made in main.
	if (n <= 0) return;

	long printed = 0;
	fseek(file, 0, SEEK_SET);

	while (printed < n && fgets(buffer, sizeof(buffer), file)) {
		printf("%s", buffer);
		printed++;
	}
}

// Reads the last N lines starting from total-N (bottom) in forward order
void read_file_reverse(FILE *file, long n) {

	// error handling for reuse.
	if (n >= 0) {
		read_file(file, n);
		return;
	}

	char buffer[MAX_LINE];
	long total = 0;

	// First pass: count total lines
	fseek(file, 0, SEEK_SET);
	while (fgets(buffer, sizeof(buffer), file)) total++;

	long linesToRead = -n;
	long startLine = total > linesToRead ? total - linesToRead : 0;
	linesToRead = total - startLine; // lines available from startLine to end

	// rewind and skip lines until startLine
	fseek(file, 0, SEEK_SET);
	long lineCount = 0;
	while (lineCount < startLine && fgets(buffer, sizeof(buffer), file))
	lineCount++;

	// print the next linesToRead lines
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

		} else if (strcmp(argv[i], "-h") == 0) {
			printf(help);
		}
	}
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf(help);
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

	if (userLineCount < 0) {
		read_file_reverse(file, userLineCount);
	} else {
		read_file(file, userLineCount);
	}

	fclose(file);

	return 0;

}
