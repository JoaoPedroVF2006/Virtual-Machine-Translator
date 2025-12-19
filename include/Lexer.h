#ifndef LEXER_H
#define LEXER_H

// PARSER_H // -----------------------------------------------------------

    // CONSTANTS // --------------------------------------------------------
    #define LINE_MAX_LENGTH 255
    #define TOKEN_MAX_LENGTH 16
    #define TOKENS_MAX 3

    #define INSTRUCTIONS 20
    #define MEMORY_SEGMENTS 8

    #define EMPTY_LINE 1
    #define PARSING_SUCCESS 0

    #define LEXING_SUCCESS 0

    #define NOT_TOKEN -1

    #define TOKEN_PROCESSING_ERROR -1

    typedef enum {
        C_ARITHMETIC,
        C_LITERAL,
        C_PUSH, C_POP,
        C_LABEL,
        C_GOTO, C_IF,
        C_FUNCTION,
        C_RETURN,
        C_CALL
    } TOKEN_TYPE;

    typedef struct {

        char tokenText[TOKEN_MAX_LENGTH];
        TOKEN_TYPE tokenType;

    } TOKEN; 

    extern TOKEN instructionsTokens[INSTRUCTIONS];
    extern TOKEN memorySegments[MEMORY_SEGMENTS];
    
    extern TOKEN tokens[TOKENS_MAX];

    // FUNCTION PROTOTYPES // ---------------------------------------------
    int tokenizeLine(TOKEN tokens[], size_t tokensSize, char *line);
    int tokenMatches(TOKEN *tokensList, size_t listSize, char *string);
    int lexingTokens(TOKEN tokens[]);

#endif