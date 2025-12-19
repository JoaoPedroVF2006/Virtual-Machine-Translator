#ifndef UTILS_H
#define UTILS_H

// UTILS_H // -----------------------------------------------------------

    // CONSTANTS // --------------------------------------------------------
    #define MAX_PATH 255
    #define BYTECODE_EXTENSION ".vm"
    #define BYTECODE_EXTENSION_LENGTH 3

    #define FALSE 0
    #define TRUE 1

    #define STATUS_COPY_SUCCESS 0
    #define STATUS_COPY_FAILURE -1

    #define STRING_MATCHES_FAILURE -1

    // FUNCTION PROTOTYPES // ---------------------------------------------
    int stringCopy(char *destination, const char *source, size_t initialIndex, size_t length);

#endif // UTILS_H