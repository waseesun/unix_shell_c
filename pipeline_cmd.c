#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "execute_cmd.h"

#define MAX_PIPES 10

int pipeline_cmd(char **commands, int cmd_count, const char *HOSTNAME) {
    int pipes[MAX_PIPES][2];
    pid_t pids[MAX_PIPES + 1];
    int i;

    if (cmd_count > MAX_PIPES + 1) {
        fprintf(stderr, "Too many piped commands\n");
        return -1;
    }

    for (i = 0; i < cmd_count - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe creation failed");
            return -1;
        }
    }

    for (i = 0; i < cmd_count; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("Fork failed");
            return -1;
        } else if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
                close(pipes[i-1][0]);
                close(pipes[i-1][1]);
            }
            if (i < cmd_count - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            for (int j = 0; j < cmd_count - 1; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            char *tokens[64];
            int token_count = 0;
            char *token = strtok(commands[i], " \t");
            while (token && token_count < 63) {
                tokens[token_count++] = token;
                token = strtok(NULL, " \t");
            }
            tokens[token_count] = NULL;

            if (token_count == 0) {
                exit(1);
            }

            int result = cmd(tokens[0], tokens, HOSTNAME);
            exit(result == 0 ? 0 : 1);
        }
    }

    for (i = 0; i < cmd_count - 1; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    int status;
    for (i = 0; i < cmd_count; i++) {
        if (waitpid(pids[i], &status, 0) == -1) {
            perror("Wait failed");
            return -1;
        }
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            return -1;
        }
    }

    return 0;
}