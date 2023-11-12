#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void) {
    char *s = NULL;
    size_t n = 0;
    char *token;
    int status, i = 0;
    pid_t child_pid;

    while (1) {
        write(1, "#cisfun$ ", 9);
        getline(&s, &n, stdin);

        // Tokenize the input
        token = strtok(s, " \t\n");
        tokenArray = malloc(sizeof(char *) * 1024);

        while (token) {
            tokenArray[i] = token;
            token = strtok(NULL, " \t\n");
            i++;
        }
        tokenArray[i] = NULL;

        if (access(tokenArray[0], X_OK) == 0) {
            child_pid = fork();
            if (child_pid == -1) {
                perror("Error");
            } else if (child_pid == 0) {
                // Child process
                execvp(tokenArray[0], tokenArray);
                // If execvp fails, print an error and exit
                perror("Error");
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                wait(&status);
                i = 0;
            }
        } else {
            // Try searching in PATH
            int found = 0;
            char *path = getenv("PATH");
            char *path_copy = strdup(path);  // Make a copy for strtok

            // Tokenize PATH and search for the executable
            token = strtok(path_copy, ":");
            while (token) {
                char full_path[1024];
                snprintf(full_path, sizeof(full_path), "%s/%s", token, tokenArray[0]);
                if (access(full_path, X_OK) == 0) {
                    found = 1;
                    break;
                }
                token = strtok(NULL, ":");
            }

            free(path_copy);

            if (found) {
                child_pid = fork();
                if (child_pid == -1) {
                    perror("Error");
                } else if (child_pid == 0) {
                    // Child process
                    execvp(tokenArray[0], tokenArray);
                    // If execvp fails, print an error and exit
                    perror("Error");
                    exit(EXIT_FAILURE);
                } else {
                    // Parent process
                    wait(&status);
                    i = 0;
                }
            } else {
                fprintf(stderr, "Command not found: %s\n", tokenArray[0]);
            }
        }
    }

    free(s);
    return 0;
}
