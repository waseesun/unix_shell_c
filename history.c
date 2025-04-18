#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

#define MAX_HISTORY 100

struct History {
    char **commands;
    int count;
    int capacity;
    int oldest_index;
};

struct History *init_history(void) {
    struct History *history = malloc(sizeof(struct History));
    if (!history) {
        perror("Failed to allocate history");
        exit(1);
    }

    history->capacity = MAX_HISTORY;
    history->commands = malloc(history->capacity * sizeof(char *));
    if (!history->commands) {
        perror("Error allocating command list");
        free(history);
        exit(1);
    }

    for (int i = 0; i < history->capacity; i++) {
        history->commands[i] = NULL;
    }

    history->count = 0;
    history->oldest_index = 0;
    return history;
}

void add_history(struct History *history, const char *command) {
    if (!command || strlen(command) == 0) {
        return;
    }
    if (history->count == history->capacity) {
        free(history->commands[history->oldest_index]);
        history->commands[history->oldest_index] = NULL;
    } else {
        history->count++;
    }

    history->commands[history->oldest_index] = strdup(command);
    if (!history->commands[history->oldest_index]) {
        perror("Failed to allocate command");
        exit(1);
    }

    history->oldest_index = (history->oldest_index + 1) % history->capacity;
}

void print_history(const struct History *history) {
    if (history->count == 0) {
        return; 
    }
    for (int i = 0; i < history->count; i++) {
        int index = (history->oldest_index - history->count + i + history->capacity) % history->capacity;
        if (history->commands[index]) {
            printf("%4d  %s\n", i + 1, history->commands[index]);
        }
    }
}

void free_history(struct History *history) {
    for (int i = 0; i < history->capacity; i++) {
        free(history->commands[i]);
    }
    free(history->commands);
    free(history);
}
