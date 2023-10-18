// Get length of String
#include <stdio.h>

// Get Total Character Count with extra for escaping Spaces
int stringInfo(char *str) {
	
	int count = 0;

	for (; *str != '\0'; str++) {
		if (*str == 32) {
			count++;
		}
		count++;
	}


	return count;
}

int clean(char *filePath, char *newPath) {
	for (; *filePath != '\0'; filePath++) {
		
		if (*filePath == 32) {
			*newPath = 92;
			newPath++;
		}
		*newPath = *filePath;
		newPath++;
	}
	*newPath = '\0';
	return 0;
}

int main(int argc, char **argv) {
	char *pTestPath = "Test Folder\\Another Test Folder\\test.txt";
	FILE *testFile = 0;
	int charCount = stringInfo(pTestPath);

	
	char newPath[charCount];
	char *pNewPath = newPath;
	clean(pTestPath, pNewPath);
	testFile = fopen(pNewPath, "w");
	fprintf(testFile, "First String\nSecond String");
	fclose(testFile);
	return 0;
}
