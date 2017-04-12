/* kt15.c
Configuration and servlet module for the Heitronics KT-15 infrared thermometer
*/
#include "kt15.h"

int configure_kt15(int fd, char temp_unit, int resp_time, int trig_time)
{
	char command[50];

	printf("Setting temperature unit to %c ... ", temp_unit);

	/* Set temperature unit */
    sprintf(command,"UNI %c\n",temp_unit);

	if (write(fd,command,strlen(command)) < 0)
	{
		perror("configure_kt15: write()");
		return 1;
	} else
		printf("SUCCESS.\n");

	printf("Setting instrument response time to %d s ... ", resp_time);

	sprintf(command,"RES %d\n", resp_time);

	if (write(fd,command,strlen(command)) < 0)
	{
		perror("configure_kt15: write()");
		return 1;
	} else
		printf("SUCCESS.\n");

	printf("Setting measurement interval to %d ms ... ", trig_time);

	sprintf(command,"TRIG ON %d\n", trig_time);

	if (write(fd,command,strlen(command)) < 0)
	{
		perror("configure_kt15: write()");
		return 1;
	} else
		printf("SUCCESS.\n");

	return 0;
} /* func configure_kt15 */

/* handler for data streaming thread */
void *kt15_servlet(void *arg)                    /* servlet thread */
{
	char sbuffer[256];
	char rbuffer[256];
	char obuffer[256];
	char temp_tag[] = "TEMP";
	char amb_ref_comm[] = "AMB ?\n";
	fd_set input;
	int sfd, fd;
	int n;
	handler_args *args;
	device_config config;
	time_t begin, elapsed;

	args = (handler_args *)arg;
	free(arg);

	fd = args->sd;
	config = args->config;

	printf("Client connected. Initializing serial connection.\n");

	/* setup serial connections */
	initialize_serial(config.baud_rate, config.bits, config.parity, config.stop_bit, 1);

	if ((sfd = open_serial(config.serial_device)) < 0)
		perror("kt15_servlet: open_serial()");

	if (configure_kt15(sfd, 'C', 1, 1000))
		perror("kt15_servlet: configure_KT15()");

	/* setup timer for amb ref command */
	begin = time(NULL);

	/* read from serial, output on socket */
	while (1)
	{
		FD_ZERO(&input);
    	FD_SET(sfd, &input);

		if (select(sfd+1, &input, 0, 0, 0) < 0) {
			perror("kt15_servlet: select()");
		} else {
			if (FD_ISSET(sfd, &input)) {
				if((n = read_serial(sfd, obuffer, sizeof sbuffer)) < 0) {
					perror("kt15_servlet: read_serial()");
					pthread_exit(&failed);
				} else {

					obuffer[n] = 0;

					/* check if client socket is still up */
					if (recv(fd, rbuffer, sizeof(rbuffer), MSG_PEEK | MSG_DONTWAIT) == 0)
						pthread_exit(&failed);

					/* write data to the socket */
					if (write(fd, obuffer, n+1) < 0)
						perror("kt15_servlet: write()");

					elapsed = time(NULL) - begin;

					if ( elapsed >= 60 ) {
						if (write(sfd,amb_ref_comm,strlen(amb_ref_comm)) < 0)
							perror("kt15_servlet: write()");

						begin = time(NULL);
					} /* if */
				} /* if */
			} /* if */
		} /* if */
	} /* while */
	return 0;                           /* terminate the thread */
} /* func kt15_servlet */
