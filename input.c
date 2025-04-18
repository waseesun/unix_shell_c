#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiple_cmd.h"
#include "history.h"

#define MAX_INPUT 1024

int shell_input(char *input, const char *HOSTNAME, struct History *history) {
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        if (feof(stdin)) {
            printf("\n");
            return 1; 
        }
        perror("Error reading input");
        clearerr(stdin); 
        return -1; 
    }

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        return 0;
    }

    add_history(history, input);

    if (strcmp(input, "history") == 0) {
        print_history(history);
        return 0;
    }

    int result = multiple_cmd(input, HOSTNAME);

    return result;
}