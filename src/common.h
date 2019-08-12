#ifndef COMMON_H_
#define COMMON_H_

#include "scanner.h"

#define MAKE_TOKEN(tokenType)\
  make_token(tokenType, lexeme, scanner -> row, scanner -> col)
#define ADD_TOKEN_FROM_LEXEME(tokenType)\
  add_token_from_lexeme(scanner, start, tokenType, tokenList)

void error(const char*);
char advance(Scanner);
char peek(Scanner);
char* make_lexeme(Scanner, int);
void add_token_from_lexeme(Scanner, int, TokenType, TokenList);

#endif