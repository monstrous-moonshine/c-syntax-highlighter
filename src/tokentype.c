#include <stdbool.h>

char* keywords[] = {
  "auto",     "break",    "case",     "char",
  "const",    "continue", "default",  "do",
  "double",   "else",     "enum",     "extern",
  "float",    "for",      "goto",     "if",
  "int",      "long",     "register", "return",
  "short",    "signed",   "sizeof",   "static",
  "struct",   "switch",   "typedef",  "union",
  "unsigned", "void",     "volatile", "while"
};

bool typewords[] = {
  true, false, false, true,
  true, false, false, false,
  true, false, true,  true,
  true, false, false, false,
  true, true,  true,  false,
  true, true,  false, true,
  true, false, false, true,
  true, true,  true,  false
};