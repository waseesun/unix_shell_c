#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.c"

#define MAX_USERNAME 256
#define HOSTNAME "x_shell>"

int main() {
    char user_name[MAX_USERNAME];

    printf("Enter your username: ");
    if (fgets(user_name, MAX_USERNAME, stdin) == NULL) {
        perror("Error reading username");
        exit(1);
    }

    user_name[strcspn(user_name, "\n")] = '\0';

    char *shell_name = malloc(strlen(user_name) + strlen(HOSTNAME) + 2);
    if (shell_name == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    strcpy(shell_name, user_name);
    strcat(shell_name, "@");
    strcat(shell_name, HOSTNAME);
    strcat(shell_name, " ");

    while (true) {
        char *input = malloc(1024 * sizeof(char));
        if (!input) {
            perror("Error allocating memory");
            exit(1);
        }
        
        printf("%s", shell_name);
        fflush(stdout);
        
        int result = shell_input(input);

        if (result == 0) {
            free(input);
            continue;
        }
        
        if (result != 0) {
            free(input);
            exit(1);
        }

        printf("Command: %s\n", input);
    }

    return 0;
}