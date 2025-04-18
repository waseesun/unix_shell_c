#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler(int sig) {
    printf("\n");
}

int signal_handler(void) {
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        return -1;
    }
    return 0;
}