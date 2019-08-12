#include <stdlib.h>
#include <string.h>
#include "common.h"

void error(const char* msg) {
  // do something here
}

char advance(Scanner scanner) {
  return scanner -> text [ scanner -> pos++ ];
}

char peek(Scanner scanner) {
  return scanner -> text [ scanner -> pos ];
}

char* make_lexeme(Scanner scanner, int start) {
  int len = scanner -> pos - start + 1;
  char* lexeme = (char*) malloc(len * sizeof(char));
  memcpy(lexeme, scanner -> text + start, len - 1);
  lexeme [ len - 1 ] = '\0';
  return lexeme;
}

void add_token_from_lexeme(Scanner scanner, int start, TokenType tokenType , TokenList tokenList) {
  char* lexeme = make_lexeme(scanner, start);
  Token token = MAKE_TOKEN(tokenType);
  add_token(tokenList, token);
}