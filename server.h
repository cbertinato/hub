/* server.h
General TCP socket handling, not instrument specific
*/
#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <pthread.h>
#include <netdb.h>
#include "parse_config.h"

typedef struct {
    int sd;
  	device_config config;
} handler_args;

int create_tcp_socket(int port);
int wait_for_connection(int, void *);

#endif
