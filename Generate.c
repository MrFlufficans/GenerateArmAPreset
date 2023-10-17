#include <stdio.h>
#include <regex.h>

int fileLength(char *filename) {
	int lineCount; // Line Count Number
	char singleChar; // Single Char Buffer
	FILE *pInFile; // File Pointer

	pInFile = fopen(filename, "r"); // Open the Input File and store it in the pointer 

	// Crawl through the File and look for Newline Characters to Increment the Line Count
	do {
		singleChar = fgetc(pInFile); // Grab a Single Character
		// See if it's a New Line Character
		if (singleChar == '\n') {
			lineCount++; // Increment lineCount
		}
	} while (singleChar != EOF); // As long as the Character is not a 'E'nd 'O'f 'F'ile Character

	fclose(pInFile); // Close the File after we have read it
	return lineCount; // Return Line Count
}

// Output the File contents to another File after being Filtered with Regex
int printFile(char *filename, int lineCount) {
	FILE *pInFile; // Input File Pointer
	FILE *pOutFile; // Output File Pointer

	pInFile = fopen(filename, "r"); // Open the Input file and store it in the pointer
	pOutFile = fopen("GeneratedPreset.preset2", "w");


	// Print all the Header text to File
	fprintf(pOutFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf(pOutFile, "<addons-presets>\n");
	fprintf(pOutFile, "	<last-update>2023-10-17T15:12:23.3346581+08:00</last-update>\n");
	fprintf(pOutFile, "		<published-ids>\n");

	// Increment through the File and Sort it with Regex
	for (int i = 0; i < lineCount; i++) {

		char line[300]; // String Buffer of 200 bytes
		
		regex_t regex; // Regex Struct 
		int regResult; // Regex Compile Result
		size_t nMatch = 2; // Long Long to Store Match Count?
		regmatch_t pMatch[2]; // Match Object
		char *pPattern = "([0-9]{8,15})"; // Regex Pattern
		
		fgets(line, 300, pInFile); //Grab Line and Store it to the 'line' Buffer
		regcomp(&regex, pPattern, REG_EXTENDED); // Compile the Regex
		regResult =	regexec(&regex, line, nMatch, pMatch, 0); // Execute the Regex

		// If the Regex Matches Print the Result
		if (!regResult) {
			// I don't even want to explain how this works
			//printf("%.*s\n", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
			fprintf(pOutFile, "			<id>steam:%.*s</id>\n", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
		}
		regfree(&regex); //Free the Regex when we are done
	}
	
	// Print all the Footer Text to File
	fprintf(pOutFile, "		</published-ids>\n");
	fprintf(pOutFile, "	<dlcs-appids />\n");
	fprintf(pOutFile, "</addons-presets>\n");

	fclose(pInFile); // Close the Input File
	return 0; // Return
}

int main(int argc, char *argv[]) {

	int lineCount; // File Line Count
	char *pInput = argv[1]; // Input File
	
	lineCount = fileLength(pInput); // Get the Line Count of the File
	printFile(pInput, lineCount); // Then run it through the Regex and output it
	
	return 0; // End
}
