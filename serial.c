/* serial.c
General serial device handling, not instrument specific
*/

#include "serial.h"

struct termios old_tio;
struct termios tio;

/* Setup RS232 connection parameters and return file descriptor */
void initialize_serial(int baudrate, int data, int parity, int stopbit, int hardware_fc)
{
        memset(&tio,0,sizeof(tio));

        /* Ignore bytes with parity errors and map CR to NL */
        /*tio.c_iflag = IGNPAR | ICRNL; */
        tio.c_iflag = IGNBRK | IGNPAR | ICRNL;

        /* Raw output */
        tio.c_oflag = 0;

        /* CS8 = 8N1 (8 bit, no parity, 1 stop bit)
           CLOCAL = local connection, no modem control
           CREAD = enable receiving characters
           CRTSCTS = enable hardware flow control */
        tio.c_cflag = CS8 | CREAD | CLOCAL | CRTSCTS;

    	tio.c_lflag = 0;

    	/* Blocking read until 1 character arrives */
        tio.c_cc[VMIN] = 0;

        /* Inter-character timer unused */
        tio.c_cc[VTIME] = 0;

        cfsetospeed(&tio,baudrate);
        cfsetispeed(&tio,baudrate);

}

int open_serial (char *device)
{
	int fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);

  	if (fd == -1)
  	{
    	printf("open_port(): Unable to open %s\n", device);
    	return -1;
  	} else {
    	fcntl(fd, F_SETFL, 0);
		printf("Connection to %s open.\n", device);

	 	/* Save current serial port settings */
    	tcgetattr(fd,&old_tio);

		tcflush(fd, TCIFLUSH);
    	tcsetattr(fd,TCSANOW,&tio);

  		return fd;
  	}

}

/* read bytes from serial connection with file descriptor fd. */
/* return output as pointer to buffer */
int read_serial(int fd, char *buffer, size_t size)
{
	int n;

	if ((n = read(fd, buffer, size)) < 0)
		return -1;
	else {
		buffer[n] = 0;
		return n;
	}
}
