#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Utils.h"

// MAIN FUNCTION // --------------------------------------------------------

// FOR NOW: READ JUST ONE FILE
int main(int argsc, char *argsv[]) {

  int statusCode = EXIT_SUCCESS;

  if (argsc < 2) {
    printf("Bad usage -> VMT <byteCode.vm / directory/byteCodes/...>\n");
    return EXIT_FAILURE;
  }

  char *filePath = argsv[1];
  char fileExtension[BYTECODE_EXTENSION_LENGTH];
  size_t filePathLength = strlen(filePath);

  if(stringCopy(fileExtension, filePath, filePathLength - 3, 2) == STATUS_COPY_FAILURE) {
    printf("Internal error -> string copy exception.\n");
    return EXIT_FAILURE;
  }

  if (strncmp(fileExtension, BYTECODE_EXTENSION, BYTECODE_EXTENSION_LENGTH)) {
    printf("File type not supported, use: -> 'xxx.vm'\n");
    return EXIT_FAILURE;
  }

  // TRY TO OPEN THE FILE
  FILE *byteCodeFile = fopen(filePath, "w");

  return 0;
}
