#pragma once

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Builds a lexical symbolTable from text file
class SourceCodeScanner {
public:
  SourceCodeScanner(string delim) : delimiters(delim), removeWhitespace(true) {}
  void scan(const ifstream& file);
  string summary() const;

  void setRemoveWhitespace(bool b) { removeWhitespace = b; }

private:
  struct TokenInfo {
    int count;
    string tokenClass;
  };
  unordered_map<string, TokenInfo> symbolTable; // <token, TokenInfo>
  vector<string> tokens;
  string delimiters;
  bool removeWhitespace;

  void generateTokens(string str);
  string classify(const string& token);
};

// Scans text file and generates tokens. Tokens are seperated by delimiters.
// Delimiter characters are included as tokens unless they are whitespace.
void SourceCodeScanner::scan(const ifstream& codeFile) {
  ostringstream buffer;
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

// Returns a report of generated tokens and their information.
string SourceCodeScanner::summary() const {
  ostringstream report;

  // Set the width of each column
  int tokenWidth = 20;
  int countWidth = 10;
  int classWidth = 10;

  // Print the header
  report << std::left << std::setw(tokenWidth) << "Token"
         << std::setw(countWidth) << "Count"
         << std::setw(classWidth) << "Class" << "\n";

  // Print a line under the header
  report << std::string(tokenWidth + countWidth + classWidth, '-') << "\n";

  for (const auto& pair : symbolTable) {
    report << std::left << std::setw(tokenWidth) << pair.first
           << std::setw(countWidth) << pair.second.count
           << std::setw(classWidth) << pair.second.tokenClass << "\n";
  }

  return report.str();
}

void SourceCodeScanner::generateTokens(string str) {
  size_t start = 0; // position in string to search from
  size_t delim = 0; // found delimiter position

  // find first delimiter
  delim = str.find_first_of(delimiters);

  while (delim != string::npos) {
    // skip 0 length
    if (start != delim) {
      // token is all characters from start pos to and including delim
      string token = str.substr(start, delim - start);

      if (removeWhitespace) {
        // erase-remove whitespace
        token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
      }
      if (!token.empty()) {
        tokens.push_back(token);
      }
    }

    // Add special character delims as tokens
    if (!isspace(str[delim])) {
      tokens.push_back(str.substr(delim, 1));
    }

    start = delim + 1;
    delim = str.find_first_of(delimiters, start);
  }

  // Add last token if str does not end with delimiter
  if (start != str.length()) {

    string token = str.substr(start);

    if (removeWhitespace) {
      token.erase(remove_if(token.begin(), token.end(), isspace), token.end());
    }
    if (!token.empty()) {
      tokens.push_back(token);
    }
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
    // remove capital letters
    string lower;
    for (const char& c : token) {
      lower += tolower(c);
    }
    if (lower == "if" || lower == "then" || lower == "else" ||
        lower == "begin" || lower == "end") {
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
token grammar:

keyword ::= if | then | else | begin | end

    identifier -> character | character identifier

    integer -> digit | digit integer

    real -> integer.integer

    special -> ( | ) | [ | ] | + | - | = | , | ;

    digit -> 0|1|2|3|4|5|6|7|8|9

    character -> a|b|c ... |z|A|B|C ... |Z
*/