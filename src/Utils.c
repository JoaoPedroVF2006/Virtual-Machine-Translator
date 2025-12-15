#include <stdio.h>
#include <string.h>
#include "../include/Utils.h"

int stringCopy(char *destination, const char *source, int initialIndex, int length) {
    
    int statusCode = STATUS_COPY_SUCCESS;

    printf("%s %s\n%d %d", destination , source, initialIndex, length);

    if (destination == NULL || source == NULL || length < 0 
        || initialIndex < 0 || initialIndex + length >= strlen(source)
        || sizeof(destination) < length) {
        return STATUS_COPY_FAILURE;
    }

    int j = 0;
    for (int i = initialIndex; i <= initialIndex + length; i++) {

        destination[j] = source[i];

        j++;

    }

    return statusCode;

}