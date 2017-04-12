/* server.c
General TCP socket handling, not instrument specific
*/
#include "server.h"

#define DEBUG

int create_tcp_socket(int port)
{
	#ifdef DEBUG
		printf("create_tcp_socket()\n");
	#endif

	struct sockaddr_in addr;
	int sd;

	/*--- create socket ---*/
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if ( sd < 0 )
		perror("socket");

	/*--- bind port/address to socket ---*/
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;                   /* any interface */
	if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
		perror("bind");

	/*--- make into listener with 10 slots ---*/
	if ( listen(sd, 10) != 0 )
		perror("listen");

	return sd;
}

int wait_for_connection(int sd, void *handler)
{
	FILE *fp;
	pthread_t child;
	handler_args *args;

	sd = accept(sd, 0, 0);

	args = malloc(sizeof(*args));
	args->sd = sd;
	args->config = kt15_config;

	pthread_create(&child, 0, handler, (void *)args);
	pthread_detach(child);

	return 0;
}
