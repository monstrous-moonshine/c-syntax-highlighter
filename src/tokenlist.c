#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tokenlist.h"

bool isempty(TokenList lst) {
  return lst -> head == lst -> z;
}

TokenList make_tokenlist() {
  TokenList lst = (TokenList) malloc(sizeof *lst);
  lst -> z = (Node*) malloc(sizeof(Node));
  lst -> z -> next = lst -> z;
  lst -> head = lst -> z;
  lst -> tail = lst -> z;
  return lst;
}

void add_token(TokenList lst, Token token) {
  Node* node = (Node*) malloc(sizeof *node);
  memcpy(&node->token, &token, sizeof token);
  if (isempty(lst)) {
    lst -> head = node;
    lst -> tail = node;
  } else {
    lst -> tail -> next = node;
    lst -> tail = node;
  }
  node -> next = lst -> z;
}

void printescaped(const char* lexeme) {
  for (int i = 0; lexeme[i] != '\0'; i++) {
    switch (lexeme[i]) {
      case '<':
        fprintf(stdout, "&lt;");
        break;
      case '>':
        fprintf(stdout, "&gt;");
        break;
      case '&':
        fprintf(stdout, "&amp;");
        break;
      case '\'':
        fprintf(stdout, "&apos;");
        break;
      case '"':
        fprintf(stdout, "&quot;");
        break;
      default:
        fprintf(stdout, "%c", lexeme[i]);
    }
  }
}

#define PRINTCLASS(class)\
  fprintf(stdout, "<span class=\""class"\">%s</span>", t -> token . lexeme)

#define PRINTESCAPED(class)\
  fprintf(stdout, "<span class=\""class"\">");\
  printescaped(t -> token . lexeme);\
  fprintf(stdout, "</span>")

void tokenlist_print(TokenList lst) {
  fprintf(stdout, "<!DOCTYPE html>\n<html>\n<head>\n");
  fprintf(stdout, "<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n");
  fprintf(stdout, "</head>\n<body>\n");
  fprintf(stdout, "<pre>\n");
  for (Node* t = lst -> head; t != lst -> z; t = t -> next) {
    TokenType tokenType = t -> token . tokenType;
    if (tokenType >= AUTO && tokenType <= WHILE) {
      if (typewords[tokenType - AUTO]) PRINTCLASS("typeword");
      else                             PRINTCLASS("instword");     
    } else switch (tokenType) {
      case IDENTIFIER:
        PRINTCLASS("identifier");
        break;
      case NUMBER:
        PRINTCLASS("number");
        break;
      case STRING:
      case CHARLITERAL:
        PRINTESCAPED("string");
        break;
      case COMMENT:
        PRINTESCAPED("comment");
        break;
      case DIRECTIVE:
        PRINTESCAPED("directive");
        break;
      case WHITESPACE:
        fprintf(stdout, "%s", t -> token . lexeme);
        break;
      default:
        PRINTCLASS("punct");
    }
  }
  fprintf(stdout, "</pre>\n</body>\n</html>\n");
}

void tokenlist_destroy(TokenList lst) {
  Node* t = lst -> head;
  while (t != lst -> z) {
    Node* u = t -> next;
    free(t -> token . lexeme);
    free(t);
    t = u;
  }
  free(lst -> z);
}