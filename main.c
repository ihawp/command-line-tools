#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>

struct Flags {
	char filename[50];
	char sunsetname[50];
	uint32_t awesome;
};

int minusF(char *filename);
size_t read_bytes(FILE *file, unsigned char *buffer, size_t bufsize);

// DO SOME FILE OPERATIONS.
// Pass the filename
int minusF(char *filename) {

	FILE *file;

	printf("%s\n", filename);

	file = fopen(filename, "r");

	if (file == NULL) {
		printf("Unable to open file.\n");
		return 1;
	}

	// char max size is 1024 bytes.
	// Safer to call unsigned char because gcc compiles char as signed char, ARM makes it unsigned.
	unsigned char buffer[16];
	unsigned char *bufferpointer2 = malloc(2000);
	unsigned char *bufferpointer = buffer;

	// get the total bytes read from the file and print the file size
	size_t bytesRead = read_bytes(file, bufferpointer, 16);

	fseek(file, 0, SEEK_SET);

	// another one
	size_t bytesRead2 = read_bytes(file, bufferpointer2, 2000);

//	printf("\nFile Size: %zu\n", bytesRead);
//	printf("\nFile Size 2: %zu\n", bytesRead2);

	struct _stat st;
	if (_stat("awesome.txt", &st) == 0) {
		printf("File size: %lld bytes\n", st.st_size);
	} else {
		perror("stat failed");
	}

	fclose(file);

	return 1;

}

size_t read_bytes(FILE *file, unsigned char *buffer, size_t bufsize) {

	size_t total = 0;

	printf("start of read_bytes");

	size_t bytesRead;

	while ((bytesRead = fread(buffer, 1, sizeof(bufsize), file)) > 0) {
		total += bytesRead;
		for (size_t i = 0; i < bytesRead; i++) {
			// %c for char, Warren.
			printf("%c", buffer[i]);
		}
	}

	printf("end of read_bytes");

	return total;

}






























/*
	Flags:
	-------------
	-f: open a file and print the result *twice?
*/

void parseArgs(int argc, char **argv, struct Flags *fmuse) {

	// Can also do it like this so that it is allocated on the heap.
	// struct FileManager *fmusepointer = malloc(sizeof(struct FileManager));
	// You tell C that you want a struct FileManager, and then you allocate the space for that within this above pointer.
	// Everything is on the heap,the line: struct FileManager fmuse is now redundant because we can allocate to the heap

	for (int i = 0; i < argc; i++) {

		if (strcmp(argv[i], "-a") == 0) {


		} else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {

			char filename[50];
			strncpy(filename, argv[i + 1], sizeof(filename) - 1);
			filename[sizeof(filename) - 1] = '\0';
			char *filenamepointer = filename;
			minusF(filenamepointer);

		} else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {


		}
	}
}

int main(int argc, char **argv) {

	// Initialize the struct to track the submitted flags
	struct Flags fmuse;
	struct Flags *fmusepointer = &fmuse;

	parseArgs(argc, argv, fmusepointer);

	return 0;
}
