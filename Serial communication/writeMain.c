#include <stdio.h>   /* Standard input/output definitions */
    #include <string.h>  /* String function definitions */
    #include <unistd.h>  /* UNIX standard function definitions */
    #include <fcntl.h>   /* File control definitions */
    #include <errno.h>   /* Error number definitions */
    #include <termios.h> /* POSIX terminal control definitions */
    #include <fcntl.h>
    #include <stdlib.h> 
    /*
     * 'open_port()' - Open serial port 1.
     *
     * Returns the file descriptor on success or -1 on error.
     */

int open_port(void)
{
	int fd; /* File descriptor for the port */
	int i; 
	char port[255], out[255], in[255];
	int n ;
	unsigned char * output = malloc(sizeof(unsigned char));
	int status;	
	
	sprintf(port, "/dev/ttyUSB"); // puts string into buffer
	fd = open("/dev/ttyUSB0" , O_RDWR | O_NOCTTY | O_NDELAY);


	if (fd == -1)
	{
		/*
		* Could not open the port.
		*/
		sprintf(port, "open_port: Unable to open /dev/ttyS - %i", i); // puts string into buffer
		perror(port);
	}
	else
	{
		/*int flags = fcntl(fd, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fd, F_SETFL, flags);*/
		fcntl(fd, F_SETFL, 0);
	}
	
	struct termios options;
	tcgetattr(fd, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	//options.c_cflag |= CRTSCTS; 
	printf("%i\n", options.c_ispeed);
	tcsetattr(fd, TCSANOW, &options);
	
	printf("next\n");
				
	/*n = write(fd, "+++", 3);
	if (n < 0)
	{
		fputs("write() of 4 bytes failed!\n", stderr);
	}
	sleep(1);
	read(fd, out, 3);
	printf("%s\n",out);
	sleep(1);
	*/


	/*ioctl(fd, TIOCMGET, &status);
	status |= TIOCM_CTS_DTR;
	ioctl(fd, TIOCMSET, &status);*/
	while(1)
	{
		scanf("%s", in);
		write(fd, in, strlen(in));
		printf("test");
		//out[1] = '\0'; 
		//printf("%x",  * output);
		//fflush(stdout);
	}
		
		
	
	return (fd);
}

	int main()
	{
		printf("Hello\n");
		open_port();
/*
		    n = write(fd, "ATZ\r", 4);
		    if (n < 0)
		      fputs("write() of 4 bytes failed!\n", stderr);
*/
		printf("Hello2\n");
		return 0;
	}
