/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "parse_config.h"
#include "server.h"
#include "shell.h"
#include "kt15.h"

int main(int argc, char* argv[])
{
	int sd1, sd2, sd3, sfd;

	/* read configuration file */
	if (read_config())
		perror("read_config");

	/* setup output sockets */
	if (!(sd1 = create_tcp_socket(kt15_config.outputport)))
		perror("create_tcp_socket");

	/*if (!(sd2 = create_tcp_socket(ire_config.outputport)))
		perror("create_tcp_socket");*/


	/*if (!(sd3 = create_tcp_socket(3000)))
		perror("create_tcp_socket");*/

	while (1)
	{
		wait_for_connection(sd1, kt15_servlet);
		/*wait_for_connection(sd2, servlet);*/
		/*wait_for_connection(sd3, initialize_shell);*/
	}

	close(sd1);
	/*close(sd2);
	close(sd3);*/
}
