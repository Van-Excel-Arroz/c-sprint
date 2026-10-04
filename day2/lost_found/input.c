#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

void read_line(
    char *buffer,
    size_t capacity
)
{
    if (fgets(buffer, capacity, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    size_t length = strlen(buffer);

    if (length > 0 &&
        buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        int character;

        while (
            (character = getchar()) != '\n' &&
            character != EOF
        ) {
        }
    }
}

int read_int(void)
{
    char buffer[64];

    read_line(
        buffer,
        sizeof(buffer)
    );

    return atoi(buffer);
}
