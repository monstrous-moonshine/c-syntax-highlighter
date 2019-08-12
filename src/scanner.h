#ifndef SCANNER_H_
#define SCANNER_H_

#include "tokenlist.h"

typedef struct {
  char* text;
  int pos;
  int row;
  int col;
} * Scanner;

Scanner scanner_create(const char*);
TokenList scanner_scan(Scanner);
void scanner_destroy(Scanner);

#endif