#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "execute_cmd.h"

int seperate_cmd(char **commands, int cmd_count, const char *HOSTNAME) {
    int result = 0;
    for (int i = 0; i < cmd_count; i++) {
        char *tokens[64];
        int token_count = 0;
        char *token = strtok(commands[i], " \t");
        while (token && token_count < 63) {
            tokens[token_count++] = token;
            token = strtok(NULL, " \t");
        }
        tokens[token_count] = NULL;

        if (token_count == 0) {
            continue;
        }

        result = cmd(tokens[0], tokens, HOSTNAME);
    }
    return result;
}