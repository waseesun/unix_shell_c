#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int cmd(char *command, char *args[], const char *HOSTNAME) {
    if (strcmp(command, "hostname") == 0) {
        printf("%s\n", HOSTNAME);
        return 0;
    }

    if (strcmp(command, "exit") == 0) {
        printf("Goodbye!\n");
        return 1;
    }

    if (strcmp(command, "cd") == 0) {
        char *dir;
        if (args[1] && strcmp(args[1], "~") == 0) {
            dir = getenv("HOME");
        } else {
            if (args[1]) {
                dir = args[1];
            } else {
                dir = getenv("HOME");
            }
        }
        if (!dir) {
            fprintf(stderr, "cd: HOME not set\n");
            return -1;
        }
        if (chdir(dir) != 0) {
            perror("cd failed");
            return -1;
        }
        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else if (pid == 0) {
        execvp(command, args);
        perror("Command execution failed");
        exit(1);
    } else {
        int status;
        if (wait(&status) == -1) {
            perror("Wait failed");
            return -1;
        }
        return WIFEXITED(status) && WEXITSTATUS(status) == 0 ? 0 : -1;
    }

    return 0;
}