#ifndef HISTORY_H
#define HISTORY_H

#define MAX_HISTORY 100
#define MAX_COMMAND_LENGTH 1024

struct History;

struct History *init_history(void);
void add_history(struct History *history, const char *command);
void print_history(const struct History *history);
void free_history(struct History *history);

#endif 

