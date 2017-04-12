/* parse_config.h */
#ifndef PARSE_CONFIG_H
#define PARSE_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ini.h"

typedef struct
{
    const char* ip;
  	int controlport;
} server_config;

typedef struct
{
    const char* name;
    const char* outputprotocol;		/* TCP or UDP */
    const char* inputprotocol;		/* USB or RS232 */
    int commandport;			/* for direct control */
    int outputport;
    int outputfreq;
    char *serial_device;
    int baud_rate;
    int bits;
    int parity;
    int stop_bit;
} device_config;

extern server_config s_config;
extern device_config ire_config;
extern device_config kt15_config;

static int s_handler(void*, const char*, const char*, const char*);
static int kt15_handler(void*, const char*, const char*, const char*);
static int ire_handler(void*, const char*, const char*, const char*);
int read_config(void);

#endif