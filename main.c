#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openFile(char *filename, int *userLineCount);
int isInteger(char *integer);

// Incrementally read file

/*

To incrementally read a file, you need to:

1) Open the file

2) Create buffer: check the file and store information about how large the first X lines are.

3) Read the lines to stdout

4) 

?) Close the file

*/

void openFile(char *filename, int *userLineCount) {

	FILE *file = fopen(filename, "r");

	if (!file) return;

	char buffer[50];
	int lineCount = 0;

	while (fgets(buffer, sizeof(buffer), file) != NULL && lineCount < *userLineCount) {
		printf("%s", buffer);
		lineCount++;
	}

	fclose(file);

}

int isInteger(char *integer) {
	char *endpt;

	int val = (int)strtol(integer, &endpt, 10);

	if (errno == ERANGE || *endpt != '\0') {
		errno = EINVAL;
		printf("Invalid integer\n");
		return 0;
	}

	printf("converted with strtol");
	return val;
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Too few arguments passed.");
		return 1;
	}

	char filename[50];
	strcpy(filename, argv[1]);

	int userLineCount = isInteger(argv[2]);

	if (errno == EINVAL) {
		printf("Invalid integer for file line read-count");
		return 1;
	}

	openFile(filename, &userLineCount);

	printf("working");

}
