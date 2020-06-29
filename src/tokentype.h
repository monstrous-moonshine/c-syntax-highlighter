#ifndef TOKENTYPE_H_
#define TOKENTYPE_H_

#include <stdbool.h>
#define NUMKEYWORDS 32

typedef enum {
  IDENTIFIER, NUMBER, STRING, CHARLITERAL, COMMENT, DIRECTIVE, WHITESPACE,
  // keywords
  AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM,
  EXTERN, FLOAT, FOR, GOTO, IF, INT, LONG, REGISTER, RETURN, SHORT, SIGNED,
  SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE,
  WHILE,
  // punctuations
  LBRACKET, RBRACKET, LPAREN, RPAREN, LBRACE, RBRACE, DOT, ARROW, INCR, DECR,
  AMPERSAND, STAR, PLUS, MINUS, TILDE, BANG, SLASH, PERCENT, LSHIFT, RSHIFT,
  LESS, GREATER, LESS_EQ, GREATER_EQ, EQ_EQ, BANG_EQ, CARET, BAR, AND, OR,
  QUESTION, COLON, SEMICOLON, ELLIPSIS, EQUAL, STAR_EQ, SLASH_EQ, PERCENT_EQ,
  PLUS_EQ, MINUS_EQ, LSHIFT_EQ, RSHIFT_EQ, AMPERSAND_EQ, CARET_EQ, BAR_EQ,
  COMMA
} TokenType;

extern char* keywords[NUMKEYWORDS];
extern bool typewords[NUMKEYWORDS];

#endif