/* serial.h
General serial device handling, not instrument specific
*/
#ifndef SERIAL_H
#define SERIAL_H

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

int open_serial (char *);
void initialize_serial(int, int, int, int, int);
int read_serial(int, char *, size_t);

#endif
