/* kt15.h
Configuration and servlet module for the Heitronics KT-15 infrared thermometer
*/
#ifndef KT15_H
#define KT15_H

#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <pthread.h>
#include <sys/socket.h>
#include <time.h>
#include "serial.h"
#include "server.h"

static int failed = -1;

int configure_kt15(int, char, int, int);
void *kt15_servlet(void *);
char *stripWhitespace (char *);

#endif
