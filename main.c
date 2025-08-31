#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

struct Flags {
	char filename[50];
	char sunsetname[50];
	uint32_t awesome;
};

int minusB();
int minusF(struct Flags *fmuse, char *great);

/*
	Flags:
	-------------
	-a: ass
	-b: bass
	-f: fass: minusF()
*/

/*

	These functions have no real point.
	But that is okay,
	I am learning how to usefully move the
	memory (mainly strings) around a C program!

*/

int stringLength(char *input, struct Flags *fmuse) {
	if (strlen(input) < sizeof(fmuse->filename)) {
		printf("\nBEFORE SETTING FILENAME: %s\n", fmuse->filename);
		strcpy(fmuse->filename, input);
		printf("\nAFTER SETTING FILNAME: %s\n", fmuse->filename);
	}
}

int minusA() {
	printf("\nminus A\n");
}

// DO SOME FILE OPERATIONS.
int minusB() {

	FILE *file;

	file = fopen("awesome.txt", "r");

	if (file == NULL) {
		return 1;
	}

	unsigned char buffer[16];
	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
		for (size_t i = 0; i < bytesRead; i++) {

			// %c for char, Warren, not %s.
			printf("%c", buffer[i]);

		}
	}

	fclose(file);

	printf("\nminus B\n");
}

// Uses pointer to struct instead of copy.
int minusF(struct Flags *fmuse, char *great) {
	strcpy(fmuse->filename, "Great and so awesome");
	printf("\n%s\n", fmuse->filename);
	printf("\nGreat: %s\n", great);
	stringLength(great, fmuse);
	return 0;
}

void parseArgs(int argc, char **argv, struct Flags *fmuse) {

	// Can also do it like this so that it is allocated on the heap.
	// struct FileManager *fmusepointer = malloc(sizeof(struct FileManager));
	// You tell C that you want a struct FileManager, and then you allocate the space for that within this above pointer.
	// Everything is on the heap,the line: struct FileManager fmuse is now redundant because we can allocate to the heap

	for (int i = 0; i < argc; i++) {

		if (strcmp(argv[i], "-a") == 0) {

			minusA();

		} else if (strcmp(argv[i], "-b") == 0) {

			minusB();

		} else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {

			minusF(fmuse, argv[i + 1]);

		}

		printf("\nARG-%d: %s\n", i, argv[i]);
	}
}

int main(int argc, char **argv) {

	// Initialize the struct to track the submitted flags
	struct Flags fmuse;
	struct Flags *fmusepointer = &fmuse;

	parseArgs(argc, argv, fmusepointer);

	return 0;
}
