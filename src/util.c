#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compar(const void* pstr1, const void* pstr2) {
  return strcmp(*(const char**)pstr1, *(const char**)pstr2);
}

char* get_static(const char* lexeme) {
  char* out = (char*) malloc((strlen(lexeme) + 1) * sizeof *out);
  strcpy(out, lexeme);
  return out;
}

char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);
  
  char* buffer = (char*) malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  buffer[bytesRead] = '\0';
  
  fclose(file);
  return buffer;
}