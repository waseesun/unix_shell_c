#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

int shell_input(char *input) {
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("Error reading input");
        exit(1);
    }

    input[strcspn(input, "\n")] = '\0';

    printf("Command: %s\n", input);

    if (strcmp(input, "exit") == 0) {
        return 1;
    }

    return 0;
}