#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "create.h"

struct Values {
	char awesome[50];
	int awesomeint;
};

void parseArgs(int argc, char **argv);

void parseArgs(int argc, char **argv) {

// I create a struct and return the struct?

// create the struct here and return it.

// Use strcmp(first, compareTO);

	for (int i = 0; i < argc; i++) {


		if (strcmp(argv[i], "-a")) {

			printf("%s", argv[i]);

		}


	}
}

int main(int argc, char **argv) {

	printf("%d", argc);

	parseArgs(argc, &argv);

	char wow[50] = "great";

	awesome(wow);

	return 1;

	// Create the struct
	// pass the pointer to functions
	// struct Values awesome;

	// strcpy(awesome.awesome, "Great!");

	// parseArgs(argv, *awesome);

	// Build CLI tool with C (far less useful than python versions)	

	// accept some arguments

	// for (i = 1; i < sizeof(argv); i++) {
	//	printf("\nArg %d: %s", i, argv[i]);
	// }

	// parseArgs(argv);

}
