#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

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
int printFile(char *filename, char *path, int lineCount) {
	FILE *pInFile; // Input File Pointer
	FILE *pOutFile; // Output File Pointer

	pInFile = fopen(filename, "r"); // Open the Input file and store it in the pointer
	pOutFile = fopen(path, "w");

	// Print all the Header text to File
	fprintf(pOutFile, "<?xml version='1.0' encoding='utf-8'?>\n");
	fprintf(pOutFile, "<addons-presets>\n");
	fprintf(pOutFile, "\t<last-update>2023-10-17T15:12:23.3346581+08:00</last-update>\n");
	fprintf(pOutFile, "\t\t<published-ids>\n");

	// Increment through the File and Sort it with Regex
	for (int i = 0; i < lineCount; i++) {

		char line[300]; // String Buffer of 300 bytes
		
		regex_t regex; // Regex Struct 
		int regResult; // Regex Compile Result
		size_t nMatch = 2; // Long Long to Store Match Count?
		regmatch_t pMatch[2]; // Match Object
		char *pPattern = "([0-9]{8,15})"; // Regex Pattern
		
		fgets(line, sizeof(line), pInFile); //Grab Line and Store it to the 'line' Buffer
		regcomp(&regex, pPattern, REG_EXTENDED); // Compile the Regex
		regResult =	regexec(&regex, line, nMatch, pMatch, 0); // Execute the Regex

		// If the Regex Matches Print the Result
		if (!regResult) {
			// I don't even want to explain how this works
			//printf("%.*s\n", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
			fprintf(pOutFile, "\t\t\t<id>steam:%.*s</id>\n", pMatch[1].rm_eo - pMatch[1].rm_so, &line[pMatch[1].rm_so]);
		}
		regfree(&regex); //Free the Regex when we are done
	}
	
	// Print all the Footer Text to File
	fprintf(pOutFile, "\t\t</published-ids>\n");
	fprintf(pOutFile, "\t<dlcs-appids />\n");
	fprintf(pOutFile, "</addons-presets>\n");

	fclose(pInFile); // Close the Input File
	return 0; // Return
}

// Get length of String
int stringLength(char *str) {
	int length = 0; // Length of String

	// Increment through the String and return the Length
	for (; *str != '\0'; str++) {
		length++; // Increment length
	};
	return length;
}

char* clean(char *filePath) {
	char *newPath[stringLength(filePath) + 10];
	int i = 0;

	for (; *filePath != '\0'; filePath++) {
		&newPath[i] = &filePath;
		if (*filePath == " ") {

		}
		i++;
	}
	*newPath[i+1] = "\0";
	return *newPath;
}

int main(int argc, char *argv[]) {

	// Regular Variables
	int lineCount; // File Line Count
	int length; // String Length
	char *pInput = argv[1]; // Input File
	FILE *pOutput = 0; // Debug File Pointer
	
	// File Path Shenanigens
	length = stringLength(argv[0]); // Get String Length of Path to Executable
	char newPath[length+30]; // Normal Path if the Output Directory exists
	char backUp[length+40]; // Backup Path incase we need to create the Directory
	
	// Output Path for the Preset File
	sprintf(newPath, "%s\\..\\Output\\GeneratedPreset.preset2", argv[0]);
	puts(newPath);

	pOutput = fopen(newPath, "w");
	if (pOutput == 0) {
		sprintf(backUp, "mkdir %s\\..\\Output", argv[0]);
		system(backUp);
	} else {
		fclose(pOutput);
	}

	//char *pDir = argv[0];
	
	//fprintf(pOutput, "%s\\..\\\n", argv[0]);
	//printf("%s", argv[0]);
	//fclose(pOutput);

	lineCount = fileLength(pInput); // Get the Line Count of the File
	printFile(pInput, newPath, lineCount); // Then run it through the Regex and output it
	
	return 0; // End
}
