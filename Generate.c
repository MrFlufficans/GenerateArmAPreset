#include "tre/tre.h"
#include <stdio.h>
#include <regex.h>

int fileLength(char *filename) {
	int lineCount; // Line Count Number
	char singleChar; // Single Char Buffer
	FILE *pInFile; // File Pointer

	pInFile = fopen(filename, "r");

	do {
		singleChar = fgetc(pInFile);
		if (singleChar == '\n') {
			lineCount++;
		}
	} while (singleChar != EOF);

	fclose(pInFile);
	return lineCount;
}

void printFile(char *filename, int lineCount) {
	FILE *pInFile;
	int i;

	pInFile = fopen(filename, "r");
	for (; i < lineCount; i++) {
		char line[100];
		regex_t regex;
		int regResult;
		regmatch_t *pMatch;
		char pattern[] = "([0-9]\\{8, 15\\})";

		fgets(line, 100, pInFile);
		regResult = regcomp(&regex, pattern, 0);
		regResult =	regexec(&regex, line, 0, pMatch, 0);

		printf("%.*s", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
		regfree(&regex);
	}
	fclose(pInFile);
}

int main(int argc, char *argv[]) {

	char lineCount;
	char *pInput = argv[1];

	lineCount = fileLength(pInput);
	printFile(pInput, lineCount);
	return 0;
}
