#include "LexicalScanner.h"

int main(char* filePath[]) {
	ifstream ifile(filePath[1]);
	SourceCodeScanner scanner(" \t\n");
	scanner.scan(ifile);
	scanner.printSummary();

	return 0;
}