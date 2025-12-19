#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/Lexer.h"
#include "../include/Utils.h"

TOKEN instructionsTokens[INSTRUCTIONS] = 
    {

        {"push", C_PUSH}, 
        {"pop", C_POP},

        {"add", C_ARITHMETIC},
        {"sub", C_ARITHMETIC},
        {"neg", C_ARITHMETIC},
        {"eq", C_ARITHMETIC},
        {"gt", C_ARITHMETIC},
        {"lt", C_ARITHMETIC},
        {"and", C_ARITHMETIC},
        {"or", C_ARITHMETIC},
        {"not", C_ARITHMETIC}

    };

TOKEN memorySegments[MEMORY_SEGMENTS] = 
    {

        {"argument", C_PUSH}, 
        {"local", C_POP},
        {"static", C_ARITHMETIC},
        {"constant", C_ARITHMETIC},
        {"this", C_ARITHMETIC},
        {"that", C_ARITHMETIC},
        {"pointer", C_ARITHMETIC},
        {"temp", C_ARITHMETIC},

    };

int tokenizeLine(TOKEN tokens[], size_t tokensSize, char *line) {

    // RESET THE TOKENS LIST
    memset(tokens, 0, tokensSize);

    if (line == NULL || *line == '\0')
        return EMPTY_LINE;

    int lineIndex = 0;
    int tokensIndex = 0;
    int tokenTextIndex = 0;
    int insideToken = FALSE;
    for (; line[lineIndex] != '\0'; lineIndex++) {

        char actualChar = line[lineIndex];

        if (actualChar == '/' && line[lineIndex + 1] == '/')
            break;

        if (isspace(actualChar)) {
            if (insideToken == TRUE) {
                tokens[tokensIndex].tokenText[tokenTextIndex] = '\0';
                tokensIndex++;
                tokenTextIndex = 0;
                insideToken = FALSE;
            }

            continue;
        } else {
            if (tokensIndex >= TOKENS_MAX || tokenTextIndex >= TOKEN_MAX_LENGTH - 1)
                return TOKEN_PROCESSING_ERROR;

            insideToken = TRUE;
            tokens[tokensIndex].tokenText[tokenTextIndex++] = line[lineIndex];
        }
    }

    if (insideToken == TRUE) {
        tokens[tokensIndex].tokenText[tokenTextIndex] = '\0';
        tokensIndex++;
    }

    return (tokensIndex <= 0) ? EMPTY_LINE : PARSING_SUCCESS;
}

int lexingTokens(TOKEN tokens[]) {

    TOKEN opToken = tokens[0];
    TOKEN argToken = tokens[1];
    TOKEN secArgToken = tokens[2];

    opToken.tokenType = tokenMatches(instructionsTokens, INSTRUCTIONS, opToken.tokenText);
    argToken.tokenType = tokenMatches(instructionsTokens, INSTRUCTIONS, opToken.tokenText);
    secArgToken.tokenType = tokenMatches(instructionsTokens, INSTRUCTIONS, opToken.tokenText);

    return LEXING_SUCCESS;
}

int tokenMatches(TOKEN *tokensList, size_t listSize, char *string) {

    if (tokensList == NULL || listSize <= 0 || string == NULL || string[0] == '\0')
        return STRING_MATCHES_FAILURE;

    for (int i = 0; i < listSize; i++) {

        if (!strncmp(tokensList[i].tokenText, string, TOKEN_MAX_LENGTH))
            return tokensList[i].tokenType;

    }

    return NOT_TOKEN;
}