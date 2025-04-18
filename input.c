#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.c"

#define MAX_INPUT 1024
#define MAX_TOKENS 64

int shell_input(char *input, const char *HOSTNAME) {
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

    char *tokens[MAX_TOKENS];
    int count_token = 0;
    char *token = strtok(input, " \t");
    
    while (token != NULL && count_token < MAX_TOKENS - 1) {
        tokens[count_token] = token;
        count_token++;
        token = strtok(NULL, " \t");
    }

    tokens[count_token] = NULL;
    if (count_token == 0) {
        return 0;
    }

    int result = cmd(tokens[0], tokens, HOSTNAME);

    return result;
}