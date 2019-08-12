#include <ctype.h>
#include "common.h"
#include "util.h"

#define ADD_TOKEN(tokenType, lexeme)\
  add_token(tokenList, make_token(tokenType, get_static(lexeme),\
                                  scanner -> row, scanner -> col))

void comment(Scanner, TokenList);
void number(Scanner, TokenList);

void punct(Scanner scanner, TokenList tokenList) {
  switch (advance(scanner)) {
    case ',': ADD_TOKEN(COMMA,    ","); break;
    case ';': ADD_TOKEN(SEMICOLON, ";"); break;
    case '?': ADD_TOKEN(QUESTION, "?"); break;
    case ':': ADD_TOKEN(COLON,    ":"); break;
    case '~': ADD_TOKEN(TILDE,    "~"); break;
    case '(': ADD_TOKEN(LPAREN,   "("); break;
    case ')': ADD_TOKEN(RPAREN,   ")"); break;
    case '{': ADD_TOKEN(LBRACE,   "{"); break;
    case '}': ADD_TOKEN(RBRACE,   "}"); break;
    case '[': ADD_TOKEN(LBRACKET, "["); break;
    case ']': ADD_TOKEN(RBRACKET, "]"); break;
    case '\\':
      if (peek(scanner) != '\n') error("Non-splicing backslash");
      else advance(scanner); // skip over the following new line
      break;
    case '^':
      if (peek(scanner) == '=') {
        advance(scanner);
        ADD_TOKEN(CARET_EQ, "^=");
      } else {
        ADD_TOKEN(CARET, "^");
      }
      break;
    case '!':
      if (peek(scanner) == '=') {
        advance(scanner);
        ADD_TOKEN(BANG_EQ, "!=");
      } else {
        ADD_TOKEN(BANG, "!");
      }
      break;
    case '=':
      if (peek(scanner) == '=') {
        advance(scanner);
        ADD_TOKEN(EQ_EQ, "==");
      } else {
        ADD_TOKEN(EQUAL, "=");
      }
      break;
    case '&':
      switch (peek(scanner)) {
        case '=':
          advance(scanner);
          ADD_TOKEN(AMPERSAND_EQ, "&amp;=");
          break;
        case '&':
          advance(scanner);
          ADD_TOKEN(AND, "&amp;&amp;");
          break;
        default:
          ADD_TOKEN(AMPERSAND, "&amp;");
      }
      break;
    case '|': 
      switch (peek(scanner)) {
        case '=':
          advance(scanner);
          ADD_TOKEN(BAR_EQ, "|=");
          break;
        case '|':
          advance(scanner);
          ADD_TOKEN(OR, "||");
          break;
        default :
          ADD_TOKEN(BAR, "|");
      }
      break;
    case '.':
      if (peek(scanner) == '.') {
        advance(scanner);
        if (peek(scanner) == '.') {
          advance(scanner);
          ADD_TOKEN(ELLIPSIS, "...");
        } else {
          error("Unexpected character");
        }
      } else if (isdigit(peek(scanner))) {
        scanner -> pos--;
        number(scanner, tokenList);
      } else {
        ADD_TOKEN(DOT , ".");
      }
      break;
    case '+':
      switch (peek(scanner)) {
        case '+':
          advance(scanner);
          ADD_TOKEN(INCR, "++");
          break;
        case '=':
          advance(scanner);
          ADD_TOKEN(PLUS_EQ, "+=");
          break;
        default :
          ADD_TOKEN(PLUS, "+");
      }
      break;
    case '-':
      switch (peek(scanner)) {
        case '>':
          advance(scanner);
          ADD_TOKEN(ARROW, "-&gt;");
          break;
        case '-':
          advance(scanner);
          ADD_TOKEN(DECR, "--");
          break;
        case '=':
          advance(scanner);
          ADD_TOKEN(MINUS_EQ, "-=");
          break;
        default : ADD_TOKEN(MINUS, "-"); break;
      }
      break;
    case '*':
      if (peek(scanner) == '=') {
        advance(scanner);
        ADD_TOKEN(STAR_EQ, "*=");
      } else {
        ADD_TOKEN(STAR, "*");
      }
      break;
    case '/':
      switch (peek(scanner)) {
        case '/':
        case '*':
          scanner -> pos--;
          comment(scanner, tokenList);
          break;
        case '=':
          advance(scanner);
          ADD_TOKEN(SLASH_EQ, "/=");
          break;
        default :
          ADD_TOKEN(SLASH, "/");
      }
      break;
    case '%':
      if (peek(scanner) == '=') {
        advance(scanner);
        ADD_TOKEN(PERCENT_EQ, "%=");
      } else {
        ADD_TOKEN(PERCENT, "%");
      }
    case '<':
      switch (peek(scanner)) {
        case '<':
          advance(scanner);
          if (peek(scanner) == '=') {
            advance(scanner);
            ADD_TOKEN(LSHIFT_EQ, "&lt;&lt;=");
          } else {
            ADD_TOKEN(LSHIFT, "&lt;&lt;");
          }
          break;
        case '=':
          advance(scanner);
          ADD_TOKEN(LESS_EQ, "&lt;=");
          break;
        default :
          ADD_TOKEN(LESS, "&lt;");
      }
      break;
    case '>':
      switch (peek(scanner)) {
        case '>':
          advance(scanner);
          if (peek(scanner) == '=') {
            advance(scanner);
            ADD_TOKEN(RSHIFT_EQ, "&gt;&gt;=");
          } else {
            ADD_TOKEN(RSHIFT, "&gt;&gt;");
          }
          break;
        case '=':
          advance(scanner);
          ADD_TOKEN(GREATER_EQ, "&gt;=");
          break;
        default :
          ADD_TOKEN(GREATER, "&gt;");
      }
      break;
    default :
      error("Unrecognized character");
  }
}