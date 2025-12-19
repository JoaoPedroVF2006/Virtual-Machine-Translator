#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Utils.h"
#include "../include/Lexer.h"

// MAIN FUNCTION // --------------------------------------------------------

TOKEN tokens[TOKENS_MAX];

int main(int argsc, char *argsv[]) {

  int statusCode = EXIT_SUCCESS;

  // if (argsc < 2) {
  //   fprintf(stderr, "Bad usage -> VMT <byteCode.vm / directory/byteCodes/...>\n");
  //   return EXIT_FAILURE;
  // }

  // char *filePath = argsv[1];
  char *filePath = "./teste.vm";
  char fileExtension[BYTECODE_EXTENSION_LENGTH];
  size_t filePathLength = strlen(filePath);

  if(stringCopy(fileExtension, filePath, filePathLength - 3, 2) == STATUS_COPY_FAILURE) {
    fprintf(stderr, "Internal error -> string copy exception.\n");
    return EXIT_FAILURE;
  }

  if (strncmp(fileExtension, BYTECODE_EXTENSION, BYTECODE_EXTENSION_LENGTH)) {
    fprintf(stderr, "File type not supported, use: -> 'xxx.vm'\n");
    return EXIT_FAILURE;
  }

  // TRY TO OPEN THE FILE
  FILE *byteCodeFile = fopen(filePath, "r");

  if (byteCodeFile == NULL) {
    perror("Error opening file\n");
    return EXIT_FAILURE;
  }
  
  { // READING THE LINES
    char actualLine[LINE_MAX_LENGTH];
    actualLine[0] = '\0';

    int lineCount = 0;
    while (fgets(actualLine, LINE_MAX_LENGTH, byteCodeFile) != NULL) {
    
      if (tokenizeLine(tokens, sizeof(tokens), actualLine) == EMPTY_LINE)
        continue;

      lexingTokens(tokens);

      lineCount++;
    }

    if (lineCount == 0) {
      fprintf(stderr, "\nThe file is empty.\n");
      statusCode = EXIT_FAILURE;
    }
  }

  // CLOSE THE FILE
  fclose(byteCodeFile);

  return statusCode;
}
