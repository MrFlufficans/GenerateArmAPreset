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
	FILE *pOutFile;



	pInFile = fopen(filename, "r");
	for (int i = 0; i < lineCount; i++) {
		regex_t regex;
		char line[200];
		int regResult;
		size_t nMatch = 2;
		regmatch_t pMatch[2];
		char *pPattern = "([0-9]{8,15})";
		fgets(line, 200, pInFile);
		regResult = regcomp(&regex, pPattern, REG_EXTENDED);
		regResult =	regexec(&regex, line, nMatch, pMatch, 0);
		if (!regResult) {
			printf("%.*s\n", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);

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
