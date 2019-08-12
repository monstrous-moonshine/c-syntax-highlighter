#ifndef TOKENLIST_H_
#define TOKENLIST_H_

#include "token.h"

typedef struct Node {
  Token token;
  struct Node* next;
} Node;

typedef struct {
  Node* head;
  Node* tail;
  Node* z;
} * TokenList;

TokenList make_tokenlist();
void add_token(TokenList, Token);
void tokenlist_print(TokenList);
void tokenlist_destroy(TokenList);

#endif