#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.c"

#define MAX_USERNAME 256
#define HOSTNAME "x_shell"

int main() {
    char *user_name = getenv("USER");
    if (user_name == NULL) {
        perror("Error getting username");
        exit(1);
    }

    char *shell_name = malloc(strlen(user_name) + strlen(HOSTNAME) + 3);
    if (shell_name == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    strcpy(shell_name, user_name);
    strcat(shell_name, "@");
    strcat(shell_name, HOSTNAME);
    strcat(shell_name, "> ");

    while (true) {
        char *input = malloc(1024 * sizeof(char));
        if (!input) {
            perror("Error allocating memory");
            exit(1);
        }
        
        printf("%s", shell_name);
        fflush(stdout);
        
        int result = shell_input(input, HOSTNAME);

        free(input);

        if (result == 1) {
            break;
        } else if (result != 0) {
            continue;
        }
    }

    free(shell_name);
    return 0;
}