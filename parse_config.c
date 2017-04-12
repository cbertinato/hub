/* parse_config.c
Configuration file parser
*/

#include "parse_config.h"

#define DEBUG

server_config s_config;
device_config ire_config;
device_config kt15_config;

static int s_handler(void* user, const char* section, const char* name, const char* value)
{
    server_config* sconfig = (server_config*)user;

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

    if (MATCH("server", "ip")) {
        sconfig->ip = strdup(value);
    } else if (MATCH("server", "controlport")) {
        sconfig->controlport = atoi(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

static int kt15_handler(void* user, const char* section, const char* name, const char* value)
{
    device_config* dconfig = (device_config*)user;
	char device_id[] = "KT15";

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

	if (MATCH(device_id, "name")) {
		dconfig->name = strdup(value);
	} else if (MATCH(device_id, "outputprotocol")) {
		dconfig->outputprotocol = strdup(value);
	} else if (MATCH(device_id, "inputprotocol")) {
		dconfig->inputprotocol = strdup(value);
	} else if (MATCH(device_id, "commandport")) {
		dconfig->commandport = atoi(value);
	} else if (MATCH(device_id, "outputport")) {
		dconfig->outputport = atoi(value);
	} else if (MATCH(device_id, "outputfreq")) {
		dconfig->outputfreq = atoi(value);
	} else if (MATCH(device_id, "serialdevice")) {
		dconfig->serial_device = strdup(value);
	} else if (MATCH(device_id, "baudrate")) {
		dconfig->baud_rate = atoi(value);
	} else if (MATCH(device_id, "bits")) {
		dconfig->bits = atoi(value);
	} else if (MATCH(device_id, "parity")) {
		dconfig->parity = atoi(value);
	} else if (MATCH(device_id, "stopbits")) {
		dconfig->stop_bit = atoi(value);
	} else {
		return 0;  /* unknown section/name, error */
	}

    return 1;
}

static int ire_handler(void* user, const char* section, const char* name, const char* value)
{
    device_config* dconfig = (device_config*)user;
	char device_id[] = "IRE";

    #define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

	if (MATCH(device_id, "name")) {
		dconfig->name = strdup(value);
	} else if (MATCH(device_id, "outputprotocol")) {
		dconfig->outputprotocol = strdup(value);
	} else if (MATCH(device_id, "inputprotocol")) {
		dconfig->inputprotocol = strdup(value);
	} else if (MATCH(device_id, "commandport")) {
		dconfig->commandport = atoi(value);
	} else if (MATCH(device_id, "outputport")) {
		dconfig->outputport = atoi(value);
	} else if (MATCH(device_id, "outputfreq")) {
		dconfig->outputfreq = atoi(value);
	} else if (MATCH(device_id, "serialdevice")) {
		dconfig->serial_device = strdup(value);
	} else if (MATCH(device_id, "baudrate")) {
		dconfig->baud_rate = atoi(value);
	} else if (MATCH(device_id, "bits")) {
		dconfig->bits = atoi(value);
	} else if (MATCH(device_id, "parity")) {
		dconfig->parity = atoi(value);
	} else if (MATCH(device_id, "stopbits")) {
		dconfig->stop_bit = atoi(value);
	} else {
		return 0;  /* unknown section/name, error */
	}

    return 1;
}

int read_config(void)
{
	#ifdef DEBUG
		printf("read_config()\n");
	#endif

    int error = 0;

    if (ini_parse("config.ini", s_handler, &s_config) < 0) {
        printf("Can't load 'config.ini'\n");
        return 1;
    }

    if ((error=ini_parse("config.ini", kt15_handler, &kt15_config)) < 0) {
        printf("Can't load 'config.ini'\n");
        return 1;
    }

    /*printf("DEBUG: error = %d\n",error);*/

    if (ini_parse("config.ini", ire_handler, &ire_config) < 0) {
        printf("Can't load 'config.ini'\n");
        return 1;
    }

    printf("Config loaded from 'config.ini':\n");
    printf("\t server ip = %s\n", s_config.ip);
    printf("\t server control port = %d\n", s_config.controlport);

    printf("\n\t device name = %s\n", kt15_config.name);
    printf("\t device output protocol = %s\n", kt15_config.outputprotocol);
    printf("\t device input protocol = %s\n", kt15_config.inputprotocol);
    printf("\t device command port = %d\n", kt15_config.commandport);
    printf("\t device output port = %d\n", kt15_config.outputport);
    printf("\t device output freq = %d Hz\n", kt15_config.outputfreq);

    printf("\n\t device name = %s\n", ire_config.name);
    printf("\t device output protocol = %s\n", ire_config.outputprotocol);
    printf("\t device input protocol = %s\n", ire_config.inputprotocol);
    printf("\t device command port = %d\n", ire_config.commandport);
    printf("\t device output port = %d\n", ire_config.outputport);
    printf("\t device output freq = %d Hz\n", ire_config.outputfreq);

    return 0;
}
