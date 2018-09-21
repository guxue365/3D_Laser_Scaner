#include "rotator.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	ROTATOR rotator1("/dev/ttyUSB0");
	
	// 0 -> 179
	cout << "start 0 -> 179 degree \n";
	for (int deg = 0; deg < 181; deg++) {
		rotator1.run_rotator(deg);
		
	}
    
	// 179 -> 0
	cout << "start 179 -> 0 degree \n";
	for (int deg = 179; deg >= 0; deg--) {
		rotator1.run_rotator(deg);
		
	}

	return 0;
}


