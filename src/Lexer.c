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

        {"argument", M_SEGMENT}, 
        {"local", M_SEGMENT},
        {"static", M_SEGMENT},
        {"constant", M_SEGMENT},
        {"this", M_SEGMENT},
        {"that", M_SEGMENT},
        {"pointer", M_SEGMENT},
        {"temp", M_SEGMENT},

    };

int tokenizeLine(TOKEN *tokens, size_t tokensSize, char *line) {

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

int lexingTokens(TOKEN *tokens) {

    TOKEN *opToken = &tokens[0];
    TOKEN *argToken = &tokens[1];
    TOKEN *secArgToken = &tokens[2];

    opToken->tokenType = tokenMatches(instructionsTokens, INSTRUCTIONS, opToken->tokenText);
    
    if (opToken->tokenType == NOT_TOKEN) return TOKEN_PROCESSING_ERROR;
    
    if (opToken->tokenType == C_ARITHMETIC) return LEXING_SUCCESS;
    else if (opToken->tokenType == C_PUSH || opToken->tokenType == C_POP) {
        argToken->tokenType = tokenMatches(memorySegments, MEMORY_SEGMENTS, argToken->tokenText);
        
        if (secArgToken->tokenText[0] == '\0')
            return BAD_USAGE;

        if (isdigit(secArgToken->tokenText[0])) 
            secArgToken->tokenType = C_LITERAL;
        else 
            return BAD_USAGE;
        
    }

    return LEXING_SUCCESS;
}

TOKEN_TYPE tokenMatches(TOKEN *tokensList, size_t listSize, char *string) {

    if (tokensList == NULL || listSize <= 0 || string == NULL || string[0] == '\0')
        return STRING_MATCHES_FAILURE;

    for (int i = 0; i < listSize; i++) {

        if (!strcmp(tokensList[i].tokenText, string))
            return tokensList[i].tokenType;

    }

    return NOT_TOKEN;
}