#ifndef _ROTATOR_HPP_
#define _ROTATOR_HPP_


class ROTATOR{

private:
	char *cmd;

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

#endif // _ROTATOR_HPP_
