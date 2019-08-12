#include <stdio.h>
#include "scanner.h"
//#include "parser.h"
//#include "stmtlist.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stdout, "Usage: %s source\n", argv[0]);
    return 0;
  }
  Scanner scanner = scanner_create(argv[1]);
  TokenList tokens = scanner_scan(scanner);
  //Parser parser = parser_create(tokens);
  //StmtList stmts = parser_parse(parser);
  //print_stmtlist(stmts);
  //stmtlist_destroy(stmts);
  //parser_destroy(parser);
  tokenlist_print(tokens);
  tokenlist_destroy(tokens);
  scanner_destroy(scanner);
}