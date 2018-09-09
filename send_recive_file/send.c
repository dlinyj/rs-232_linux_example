#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>        



#define BAUDRATE B115200 
#define MODEMDEVICE "/dev/ttyUSB0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

FILE *file;
int fileLen;
char *tmpbuffer;
int openport(void);
void readport(void);
void sendport(void);
int fd=0;
struct termios oldtp, newtp;
//char sendcmd1[256]="\0";
char buffer[512];

int main() {
	openport();
	//sleep(1);
//	readport();
	sendport();
	return 0;
}

void sendport(void)
{
	printf("enter write\n");
	int n;
	file = fopen("sample.txt", "r");

	//get file size

	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);
	fseek(file, 0, SEEK_SET);

	tmpbuffer = (char *)malloc(fileLen + 1);

	//read file contents
	printf("Start send\n");
	fread(tmpbuffer, fileLen, 1, file);
	fclose(file);

	n = write(fd, tmpbuffer, fileLen + 1);

	if (n < 0) {
			fputs("write() of bytes failed!\n", stderr);
	} else {
		printf("Image sent successfully %d\n",n);
	}
	close(fd);

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



