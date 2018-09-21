#ifndef _MOTOR_HPP_
#define _MOTOR_HPP_


class ROTATOR{

private:
	char cmd[20];

	int serial_fd;

	/* LOCAL FUNCTIONS */
	int OpenDev(const char *Dev);
	void SetSpeed(int fd, int speed);
	int SetParity(int fd,int databits,int stopbits,int parity);

public:
	ROTATOR(const char *dev);
	~ROTATOR();
	
	int run_rotator(float degree);
	
};

#endif // _MOTOR_HPP_
