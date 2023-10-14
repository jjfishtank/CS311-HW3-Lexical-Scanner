# CS311-HW3-Lexical-Scanner
Builds a lexical symbolTable from text file and prints a summary.

File must follow the following BNF formating for tokens:
```
keyword ::= if | then | else | begin | end

    identifier -> character | character identifier

    integer -> digit | digit integer

    real -> integer.integer

    special -> ( | ) | [ | ] | + | - | = | , | ;

    digit -> 0|1|2|3|4|5|6|7|8|9

    character -> a|b|c ... |z|A|B|C ... |Z
```
* Keywords and identifiers are not case sensitive.
* Token delimiters are space, tab, newline, and the special characters.
* Keywords, Identifiers, integers, reals, and specials are recognized as tokens.
## Usage
Build src and include files. Run LexicalScan executable with path to code file as argument.
