#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>        
#include <stdlib.h> 
#include <unistd.h>

#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyUSB1"/*UART NAME IN PROCESSOR*/
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
int openport(void);
void sendport(void);
void readport(void);
int fd=0, n;
static int cnt, size, s_cnt;
unsigned char *var;
struct termios oldtp, newtp;
char sendcmd1[10]="\0";
FILE *file;

void  readport(void) {
	unsigned char buff;
	file = fopen( "zname.txt", "w+" );
	while (1) { 
		n = read(fd, &buff, 1);
		//	fcntl(fd,F_SETFL,0);
		if (n == -1) switch(errno) {
				case EAGAIN: /* sleep() */ 
					continue;
				 default: goto quit;
			}
		if (n ==0) break;
		fputc(buff, file);
		printf("%d %c\n", n,buff);
		fflush(file);
	}
quit:
	fclose (file);
}
int openport(){
	fd = 0;										/* File descriptor */
	struct termios options;
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY | O_NDELAY);



	if (fd < 0){														/* Could not open the port */
		fprintf(stderr, "open_port: Unable to open %s - %s\n", MODEMDEVICE,
		strerror(errno));
		//~ exit (-1);
		return fd;
	}

	/* Configure port reading */
	fcntl(fd, F_SETFL, 0); 	//read com-port is the bloking
	//fcntl(fd, F_SETFL, FNDELAY);  //read com-port not bloking
	//fcntl(fd, F_SETFL, O_NDELAY);  //read com-port not bloking
	
	//ioctl(fd, FIOASYNC, 1);
	
/* Get the current options for the port */
	tcgetattr(fd, &options);
	cfsetispeed(&options, B115200);
	//cfsetispeed(&options, B9600);	
	 
/* Enable the receiver and set local mode */
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB; 						/* Mask the character size to 8 bits, no parity */
//	options.c_cflag &= ~CSTOPB; 						//one stop bit
	options.c_cflag |= CSTOPB;							//two stop bit
	options.c_cflag &= ~CSIZE;
	options.c_cflag |=  CS8;							/* Select 8 data bits */
	options.c_cflag &= ~CRTSCTS;						/* Disable hardware flow control */  
	options.c_oflag &= ~OPOST;							/* Disable postprocessing */  
	

	/* Software flow control is disabled */
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
 
/* Enable data to be processed as raw input */
	options.c_lflag &= ~(ICANON | ECHO | ISIG);
/* Set the new options for the port */


// Добавлено для проверки
	options.c_cc[VMIN]  = 50;
	options.c_cc[VTIME] = 10; 
	
	options.c_iflag |= IGNBRK;
//До этого момента всё завелось
	options.c_iflag &= ~ICRNL;
	options.c_oflag &= ~ONLCR;
	options.c_lflag &= ~IEXTEN;
	options.c_lflag &= ~ECHOE;
	options.c_lflag &= ~ECHOK;
#ifndef OPENWRT_ARM
	options.c_lflag &= ~ECHOCTL;
	options.c_lflag &= ~ECHOKE;
#endif
	tcsetattr(fd, TCSANOW, &options);
	return fd;
}


int  main()
{

	openport();
	readport();
	return 0;
}
