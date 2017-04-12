/* shell.h */
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#define BUFFER_SIZE 1<<16
#define ARR_SIZE 1<<16

void parse_args(char *, char**, size_t, size_t *);
void *initialize_shell(void *);

#endif