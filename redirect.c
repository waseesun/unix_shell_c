#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int input_redirect(char *args[]) {
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], "<") == 0) {
            if (args[i + 1] == NULL) {
                fprintf(stderr, "Input file is missing after '<'\n");
                return -1;
            }
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("Failed to open input file");
                return -1;
            }
            if (dup2(fd, STDIN_FILENO) < 0) {
                perror("Input redirection failed");
                close(fd);
                return -1;
            }
            close(fd);
            while (args[i] != NULL) {
                args[i] = args[i + 2];
                i++;
            }
            return 1;
        }
        i++;
    }
    return 0;
}

int output_redirect(char *args[], int append) {
    int i = 0;
    const char *redirect_op = append ? ">>" : ">";
    while (args[i] != NULL) {
        if (strcmp(args[i], redirect_op) == 0) {
            if (args[i + 1] == NULL) {
                fprintf(stderr, "Output file is missing after '%s'\n", redirect_op);
                return -1;
            }
            int flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
            int fd = open(args[i + 1], flags, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                return -1;
            }
            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("Output redirection failed");
                close(fd);
                return -1;
            }
            close(fd);
            while (args[i] != NULL) {
                args[i] = args[i + 2];
                i++;
            }
            return 1;
        }
        i++;
    }
    return 0;
}