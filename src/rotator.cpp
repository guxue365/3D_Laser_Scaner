/* rotator.cpp
 * 控制舵机
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "rotator.hpp"

ROTATOR::ROTATOR(const char *dev)
{
	cmd = new char[20];
	
	serial_fd = OpenDev(dev);
    SetSpeed(serial_fd, 115200);
    if ( (SetParity(serial_fd,8 ,1 ,'N')) == -1 )  {
        printf("Set Parity Error\n");
        exit (-1);
    }

	// mod3
	sprintf(cmd, "#000PMOD3!");
	write(serial_fd, cmd, 10);
	//printf("initialize_rotator(): %s -> MOD3\n", cmd);
	usleep(1000000);
	
	// 0 degree
	sprintf(cmd, "#000P%04dT0010!", 500);
	write(serial_fd, cmd, 15);
	//printf("initialize_rotator(): %s -> %d degree\n", cmd, 0);

	usleep(2000000);
}

ROTATOR::~ROTATOR()
{
	delete cmd;
	
	close(serial_fd);
}

int ROTATOR::run_rotator(float degree)
{
	sprintf(cmd, "#000P%04dT0010!", (int)( 500.0 + 2000.0 / 180.0 * degree));
	write(serial_fd, cmd, 15);
	//printf("run_rotator(): %s -> %d degree\n", cmd, (int)degree);

	usleep(20000);
	
	return 0;
}




/***********************************************************************
*                         LOCAL FUNCTION CODE                          *
************************************************************************/
int ROTATOR::OpenDev(const char *dev)
{
    int fd = open( dev, O_RDWR | O_NOCTTY | O_NDELAY );
    if (-1 == fd) {
        perror("Can't Open Serial Port");
        return -1;      
    } else {
        return fd;
    }
}


int speed_arr[] = {
    B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
    B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300 };
int name_arr[] = {
    115200, 38400, 19200, 9600, 4800, 2400, 1200, 300, 
	115200, 38400, 19200, 9600, 4800, 2400, 1200, 300 };
void ROTATOR::SetSpeed(int fd, int speed)
{
    int i; 
    int status; 
    struct termios Opt;
    tcgetattr(fd, &Opt); 
    for ( i = 0; i < sizeof(speed_arr) / sizeof(int); i++) { 
        if (speed == name_arr[i]) {     
            tcflush(fd, TCIOFLUSH);     
            cfsetispeed(&Opt, speed_arr[i]);  
            cfsetospeed(&Opt, speed_arr[i]);   
            status = tcsetattr(fd, TCSANOW, &Opt);  
            if  (status != 0) {        
            perror("tcsetattr fd");  
            return;     
        }
        tcflush(fd,TCIOFLUSH);   
    }
  }
}

int ROTATOR::SetParity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;
    if ( tcgetattr( fd,&options) != 0 ) { 
        perror("SetupSerial 1");     
        return -1;  
    }

    options.c_cflag &= ~CSIZE; 
    switch (databits) {   
    case 7:     
        options.c_cflag |= CS7; 
        break;
    case 8:     
        options.c_cflag |= CS8;
        break;   
    default:    
        fprintf(stderr,"Unsupported data size\n");
        return -1;  
    }

    switch (parity) {   
    case 'n':
    case 'N':    
        options.c_cflag &= ~PARENB;   /* Clear parity enable */
        options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
        break;  
    case 'o':   
    case 'O':     
        options.c_cflag |= (PARODD | PARENB); /* Odd*/  
        options.c_iflag |= INPCK;             /* Disable parity checking */ 
        break;  
    case 'e':  
    case 'E':   
        options.c_cflag |= PARENB;     /* Enable parity */    
        options.c_cflag &= ~PARODD;   /* */     
        options.c_iflag |= INPCK;       /* Disable parity checking */
        break;
    case 'S': 
    case 's':  /*as no parity*/   
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;break;  
    default:   
        fprintf(stderr,"Unsupported parity\n");    
        return -1;  
    }
    
    switch (stopbits) {   
    case 1:    
        options.c_cflag &= ~CSTOPB;  
        break;  
    case 2:    
        options.c_cflag |= CSTOPB;  
    break;
    default:    
        fprintf(stderr,"Unsupported stop bits\n");  
        return -1; 
    }

    options.c_cc[VTIME] = 0; // x0.1, time to wait 
    options.c_cc[VMIN] = 0; // minimal data count to wait
	
    options.c_cflag &= ~HUPCL;

    options.c_iflag |= IGNBRK;
    options.c_iflag &= ~(ICRNL | INLCR | IGNCR);
	options.c_iflag &= ~(IXON | IXOFF | IXANY);
    
	options.c_lflag &= ~IEXTEN;
    options.c_lflag &= ~ECHOK;
    options.c_lflag &= ~ECHOCTL;
    options.c_lflag &= ~ECHOKE;
    options.c_lflag &= ~(ICANON | ISIG);

	options.c_oflag &= ~(ONLCR | OCRNL);

    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("SetupSerial 3");
        return -1;
    }
    tcflush(fd,TCIFLUSH);

    return 0;
}
