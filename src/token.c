#include "token.h"

Token make_token(TokenType tokenType, char* lexeme, int row, int col) {
  return (Token) { .tokenType = tokenType, .lexeme = lexeme, .row = row, .col = col };
}