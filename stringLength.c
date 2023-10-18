// Get length of String
#include <stdio.h>

// Get Total Character Count with extra for escaping Spaces
int stringInfo(char *str) {
	int count = 0;
	for (; *str != '\0'; str++) {
		count++;
	}
	return count;
}

// Clean up the Path of Spaces for use in cmd
int clean(char *filePath, char *newPath) {
	for (; *filePath != '\0'; filePath++) {
		*newPath = *filePath;
		newPath++;
	}
	*newPath = '\0';
	return 0;
}

int main(int argc, char **argv) {
	
	// Test Path
	char *pTestPath = "Test Folder\\Another Test Folder\\test.txt";
	FILE *OutFile = 0; // Output File
	int charCount = stringInfo(pTestPath);
	char finalPath[charCount];

	char newPath[charCount];
	char *pNewPath = newPath;
	clean(pTestPath, pNewPath);
	snprintf(finalPath, charCount+1, "%s", pNewPath);
	OutFile = fopen(finalPath, "w");
	fprintf(OutFile, "First String");
	fclose(OutFile);
	return 0;
}
