#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.h"
#include "number.h"
#include "punct.h"
#include "scanner.h"
#include "util.h"

#define isAlpha(c) (c == '_' || isalpha(c))
#define isAlNum(c) (isAlpha(c) || isdigit(c))

void whiteSpace(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  while (isspace(peek(scanner))) advance(scanner);
  ADD_TOKEN_FROM_LEXEME(WHITESPACE);
}

// recognize keywords here
void identifier(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  while (isAlNum(peek(scanner))) advance(scanner);
  char* lexeme = make_lexeme(scanner, start);
  char** keyword = bsearch(&lexeme, keywords, NUMKEYWORDS, sizeof *keyword, compar);
  if (keyword == NULL) {
    Token token = MAKE_TOKEN(IDENTIFIER);
    add_token(tokenList, token);
  } else {
    int offset = keyword - keywords;
    Token token = MAKE_TOKEN(AUTO + offset);
    add_token(tokenList, token);
  }
}

void number(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  if (peek(scanner) == '0') {
    advance(scanner);
    if (tolower(peek(scanner)) == 'x') {
      advance(scanner);
      hexadecimal(scanner, tokenList, start);
    } else {
      scanner -> pos--;
      decimal(scanner, tokenList, start);
    }
  } else {
    decimal(scanner, tokenList, start);
  }
}

void escapeseq(Scanner scanner, TokenList tokenList) {
  switch (advance(scanner)) {
    case '\'':
    case '\"':
    case '\?':
    case '\\':
    case '0':
    case 'a':
    case 'b':
    case 'f':
    case 'v':
    case 'n':
    case 'r':
    case 't': break;
    default: error("Invalid escape sequence");
  }
}

void charliteral(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  advance(scanner); // consume the '
  while (true) {
    char c = advance(scanner);
    if (c == '\0') error("Unterminated character literal");
    if (c == '\'') break;
    if (c == '\\') escapeseq(scanner, tokenList);
    if (c == '\n') error("Newline in character constant");
  }
  ADD_TOKEN_FROM_LEXEME(CHARLITERAL);
}

void string(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  advance(scanner); // consume the "
  while (true) {
    char c = advance(scanner);
    if (c == '\0') error("Unterminated string");
    if (c == '\"') break;
    if (c == '\\') escapeseq(scanner, tokenList);
    if (c == '\n') error("Newline in character constant");
  }
  ADD_TOKEN_FROM_LEXEME(STRING);
}

// recognize preprocessing numbers here
// also, headers in #include directive
void directive(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  while (peek(scanner) != '\n') {
    if (peek(scanner) == '\0') error("Line break required after directive");
    if (peek(scanner) == '\\') {
      advance(scanner);
      if (peek(scanner) == '\n') advance(scanner);
      else error("Non-splicing backslash");
    }
    else advance(scanner);
  }
  ADD_TOKEN_FROM_LEXEME(DIRECTIVE);
}

void comment(Scanner scanner, TokenList tokenList) {
  int start = scanner -> pos;
  advance(scanner); // skip the '/'
  if (peek(scanner) == '/') {
    advance(scanner); // skip the second '/'
    while (peek(scanner) != '\n' && peek(scanner) != '\0') {
      advance(scanner);
    }
  } else {
    advance(scanner); // skip the '*'
    while (true) {
      if (peek(scanner) == '\0') error("Unterminated comment");
      if (advance(scanner) == '*' && peek(scanner) == '/') {
        advance(scanner);
        break;
      }
    }
  }
  ADD_TOKEN_FROM_LEXEME(COMMENT);
}

// scanner.text points to null terminated string
// containing the source code
// scanner.pos, scanner.row, scanner.col are
// initialized to 0
TokenList scanner_scan(Scanner scanner) {
  TokenList tokenList = make_tokenlist();
  while (peek(scanner) != '\0') {
    char c = peek(scanner);
    if (isspace(c)) whiteSpace(scanner, tokenList);
    else if (isAlpha(c)) identifier(scanner, tokenList);
    else if (isdigit(c)) number(scanner, tokenList);
    else if (c == '\"') string(scanner, tokenList);
    else if (c == '\'') charliteral(scanner, tokenList);
    else if (c == '#') directive(scanner, tokenList);
    else punct(scanner, tokenList);
  }
  return tokenList;
}

Scanner scanner_create(const char* source) {
  Scanner scanner = (Scanner) malloc(sizeof *scanner);
  scanner -> text = readFile(source);
  scanner -> pos = 0;
  scanner -> row = 0;
  scanner -> col = 0;
  return scanner;
}

void scanner_destroy(Scanner scanner) {
  free(scanner -> text);
}