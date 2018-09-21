#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

#include "pcd_file.hpp"

int main(int argc, char *argv[])
{
	std::string filename("./abc.pcd");
	
	PCD_FILE pcd_file(filename, 1000);
	cv::Point3_<float> point(100, 100, 100);
	
	for (int i = 0; i < 1000; i++) {
		point.x = 100.0 * rand();
		point.y = 100.0 * rand();
		point.z = 100.0 * rand();
		
		pcd_file.append(&point);
	}
	
	return 0;
	
}
