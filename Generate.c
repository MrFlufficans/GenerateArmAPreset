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

int printFile(char *filename, int lineCount) {
	FILE *pInFile;
	int i = 0;
	
	pInFile = fopen(filename, "r");
	for (; i < lineCount; i++) {
		regex_t regex;
		char line[200];
		int regResult;
		regmatch_t pMatch[2];
		char *pattern = "([0-9]{8,15})";

		fgets(line, 200, pInFile);
		regResult = regcomp(&regex, pattern, REG_EXTENDED);
		regResult =	regexec(&regex, line, 0, pMatch, 0);
		if (!regResult) {
			printf("%.*s", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);

			//printf("%.*s", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
		}
		regfree(&regex);
	}
	fclose(pInFile);
	return 0;
}

int main(int argc, char *argv[]) {

	int lineCount;
	char *pInput = argv[1];
	lineCount = fileLength(pInput);
	printFile(pInput, lineCount);
	return 0;
}
