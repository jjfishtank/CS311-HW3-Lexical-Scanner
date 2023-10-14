#include "LexicalScanner.h"

int main(int numArgs, char* filePath[]) {
	ifstream ifile(filePath[1]);
	if (!ifile) {
		std::cerr << "Failed to open file: " << filePath[1] << '\n';
		return 1;
	}
	SourceCodeScanner scanner(" \t\n()[]+-=,;");
	scanner.scan(ifile);
	cout << scanner.summary();

	return 0;
}