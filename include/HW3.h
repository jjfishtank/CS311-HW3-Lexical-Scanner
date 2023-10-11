#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>

using namespace std;

class SourceCodeScanner {
public:
  SourceCodeScanner(const string fileName);
  string printSummary();

private:
  struct TokenInfo {
    int count;
    string tokenClass;
    TokenInfo(int c, string t) : count(c), tokenClass(t) {}
  };
  unordered_map<string, TokenInfo> symbolTable;
  vector<string> tokens;
  ifstream file;

  void scan(const string fileName);
};

SourceCodeScanner::SourceCodeScanner(const string fileName) {
  scan(fileName);
}

void SourceCodeScanner::scan(const string fileName) {
  file.open(fileName);

  /*
  scan input and update symbolTable and tokens. Keep a count of each token
  class as symbol table updates.
  */

  file.close();
}

string SourceCodeScanner::printSummary() {

  // Iterate over symbolTable to generate summary report.

  return string();
}



/*
keyword ::= if | then | else | begin | end

    identifier -> character | character identifier

    integer -> digit | digit integer

    real -> integer.integer

    special -> ( | ) | [ | ] | + | - | = | , | ;

    digit -> 0|1|2|3|4|5|6|7|8|9

    character -> a|b|c ... |z|A|B|C ... |Z
*/