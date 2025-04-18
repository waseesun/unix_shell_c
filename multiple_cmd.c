#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "execute_cmd.h"
#include "pipeline_cmd.h"
#include "seperate_cmd.h"
#include "sequence_cmd.h"

#define MAX_COMMANDS 64
#define MAX_TOKENS 64

int multiple_cmd(char *input, const char *HOSTNAME) {
    char *commands[MAX_COMMANDS];
    int cmd_count = 0;
    char *temp_input = strdup(input);
    if (!temp_input) {
        perror("Error allocating memory");
        return -1;
    }

    if (strstr(input, "|")) {
        char *token = strtok(temp_input, "|");
        while (token && cmd_count < MAX_COMMANDS) {
            commands[cmd_count++] = strdup(token);
            token = strtok(NULL, "|");
        }
        int result = pipeline_cmd(commands, cmd_count, HOSTNAME);
        for (int i = 0; i < cmd_count; i++) {
            free(commands[i]);
        }
        free(temp_input);
        return result;
    } else if (strstr(input, "&&")) {
        char *token = strtok(temp_input, "&&");
        while (token && cmd_count < MAX_COMMANDS) {
            commands[cmd_count++] = strdup(token);
            token = strtok(NULL, "&&");
        }
        int result = sequence_cmd(commands, cmd_count, HOSTNAME);
        for (int i = 0; i < cmd_count; i++) {
            free(commands[i]);
        }
        free(temp_input);
        return result;
    } else if (strstr(input, ";")) {
        char *token = strtok(temp_input, ";");
        while (token && cmd_count < MAX_COMMANDS) {
            commands[cmd_count++] = strdup(token);
            token = strtok(NULL, ";");
        }
        int result = seperate_cmd(commands, cmd_count, HOSTNAME);
        for (int i = 0; i < cmd_count; i++) {
            free(commands[i]);
        }
        free(temp_input);
        return result;
    } else {
        char *tokens[MAX_TOKENS];
        int count_token = 0;
        char *token = strtok(temp_input, " \t");
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
        free(temp_input);
        return result;
    }
}