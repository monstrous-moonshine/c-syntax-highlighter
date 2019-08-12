#ifndef TOKEN_H_
#define TOKEN_H_

#include "tokentype.h"

typedef struct {
  TokenType tokenType;
  char* lexeme;
  int row;
  int col;
} Token;

Token make_token(TokenType, char*, int, int);

#endif