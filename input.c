#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024
#define MAX_TOKENS 64

int shell_input(char *input) {
    if (fgets(input, MAX_INPUT, stdin) == NULL) {
        perror("Error reading input");
        exit(1);
    }

    input[strcspn(input, "\n")] = '\0';

    if (strlen(input) == 0) {
        printf("Command: none, Option: none, Argument: none\n");
        return 0;
    }

    char *tokens[MAX_TOKENS];
    int count_token = 0;
    char *token = strtok(input, " \t");
    
    while (token != NULL) {
        tokens[count_token] = token;
        count_token++;
        token = strtok(NULL, " \t");
    }

    char *command = NULL;
    char *option = NULL;
    char *argument = NULL;

    if (count_token > 0) {
        command = tokens[0];
    
        int i = 1;
        while (i < count_token) {
            if (tokens[i][0] == '-') {
                option = tokens[i];
            } else {
                argument = malloc(1024);
                if (!argument) {
                    perror("Error allocating memory");
                    exit(1);
                }
                strcpy(argument, tokens[i]);
                for (int j = i + 1; j < count_token; j++) {
                    strcat(argument, " ");
                    strcat(argument, tokens[j]);
                }
                break;
            }
        }
    }

    printf("Command: %s, Option: %s, Argument: %s\n",
        command ? command : "none",
        option ? option : "none",
        argument ? argument : "none");

    if (strcmp(input, "exit") == 0) {
        return 1;
    }

    return 0;
}