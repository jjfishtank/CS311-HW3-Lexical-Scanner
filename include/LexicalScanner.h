#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class SourceCodeScanner {
public:
  SourceCodeScanner(string delim) : delimiters(delim) {}
  void scan(const ifstream& file);
  string printSummary() const;

private:
  struct TokenInfo {
    int count;
    string tokenClass;
    //TokenInfo(int c, string t) : count(c), tokenClass(t) {}
  };
  unordered_map<string, TokenInfo> symbolTable;
  vector<string> tokens;
  string delimiters;

  void generateTokens(string str);
  string classify(const string& token);
};

void SourceCodeScanner::scan(const ifstream& codeFile) {
  stringstream buffer;
  buffer << codeFile.rdbuf();  // get file buffer to make string
  generateTokens(buffer.str());

  for (const string& token : tokens) {
    if (symbolTable.find(token) == symbolTable.end()) { // new token
      symbolTable[token] = { 1, classify(token) };
    } else { // repeat token
      symbolTable[token].count++;
    }
  }

}

string SourceCodeScanner::printSummary() const {

  // Iterate over symbolTable to generate summary report.

  return string();
}


void SourceCodeScanner::generateTokens(string str) {
  size_t start = 0; // position in string to search from
  size_t delim = 0; // found delimiter position

  // find first delimiter
  delim = str.find_first_of(delimiters);

  while (delim != string::npos) {
    //skip 0 length
    if (start != delim) {
      // token is all characters from start pos to found delim
      tokens.push_back(str.substr(start, delim - start));
    }

    start = delim + 1;
    delim = str.find_first_of(delimiters, start);
  }

  // Add last token if str does not end with delimiter
  if (start != str.length()) {
    tokens.push_back(str.substr(start));
  }
}

string SourceCodeScanner::classify(const string& token) {
  if (isdigit(token[0])) {
    if (token.find('.')) {
      return "real";
    } else {
      return "integer";
    }
  } else if (isalpha(token[0])) {
    if (token == "if" || token == "then" || token == "else" ||
        token == "begin" || token == "end") {
      return "keyword";
    } else {
      return "identifier";
    }

  } else if (token.size() == 1) {
    if (token[0] == '(' || token[0] == ')' || token[0] == '[' ||
        token[0] == ']' || token[0] == '+' || token[0] == '-' ||
        token[0] == '=' || token[0] == ',' || token[0] == ';') {
      return "special";
    }
  }

  return "unknown";
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