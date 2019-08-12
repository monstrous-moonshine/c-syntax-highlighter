#include <ctype.h>
#include "common.h"

void exponent(Scanner scanner) {
  switch (peek(scanner)) {
    case '+':
    case '-':
      advance(scanner);
  }
  if (isdigit(peek(scanner))) {
    while (isdigit(peek(scanner))) advance(scanner);
  }
  else error("Exponent absent");
}

#define LONG_SUFFIX(l)\
  switch (peek(scanner)) {\
    case l:\
      advance(scanner);\
      if (tolower(peek(scanner)) == 'u') advance(scanner);\
      break;\
    case 'u':\
    case 'U':\
      advance(scanner);\
  }

void int_suffix(Scanner scanner) {
  switch (peek(scanner)) {
    case 'u':
    case 'U':
      advance(scanner);
      switch (peek(scanner)) {
        case 'l':
          advance(scanner);
          if (peek(scanner) == 'l') advance(scanner);
          break;
        case 'L':
          advance(scanner);
          if (peek(scanner) == 'L') advance(scanner);
      }
      break;
    case 'l':
      advance(scanner);
      LONG_SUFFIX('l')
      break;
    case 'L':
      advance(scanner);
      LONG_SUFFIX('L')
  }
}

void float_suffix(Scanner scanner) {
  switch (tolower(peek(scanner))) {
    case 'f':
    case 'l':
      advance(scanner);
  }
}

#define PREDOT(e)\
case 'u':\
case 'l':\
  if (d > 0) { int_suffix(scanner); goto done; }\
  else error("Invalid number");\
case e:\
  if (d > 0) {\
    advance(scanner);\
    exponent(scanner);\
    float_suffix(scanner);\
    goto done;\
  }\
  else error("Invalid number");\

#define POSTDOT(e)\
if (d < 1) error("Invalid number");\
if (tolower(peek(scanner)) == e) {\
  advance(scanner);\
  exponent(scanner);\
}

void hexadecimal(Scanner scanner, TokenList tokenList, int start) {
  int d = 0;
  while (isxdigit(peek(scanner))) { advance(scanner); d++; }
  switch (tolower(peek(scanner))) {
    PREDOT('p')
    case '.':
      advance(scanner);
      while (isxdigit(peek(scanner))) { advance(scanner); d++; }
      POSTDOT('p')
      else error("Invalid number");
      float_suffix(scanner);
  }
done:
  ADD_TOKEN_FROM_LEXEME(NUMBER);
}

void decimal(Scanner scanner, TokenList tokenList, int start) {
  int d = 0;
  while (isdigit(peek(scanner))) { advance(scanner); d++; }
  switch (tolower(peek(scanner))) {
    PREDOT('e')
    case '.':
      advance(scanner);
      while (isdigit(peek(scanner))) { advance(scanner); d++; }
      POSTDOT('e')
      float_suffix(scanner);
  }
done:
  ADD_TOKEN_FROM_LEXEME(NUMBER);
}