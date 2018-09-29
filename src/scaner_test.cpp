/* scaner_test.cpp
 * 旋转扫描 主函数
 * 
 * 
 */

#include <iostream>
#include <unistd.h>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "extract.hpp"
#include "pcd_file.hpp"
#include "rotator.hpp"
#include "scaner.hpp"
#include "read_config.hpp"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
	// read config file
	CONFIG_S *config_ptr = new CONFIG_S;
	string config_path("./config");
	if (argc > 1) {
		config_path = argv[1];
	}
	readConfigFile(config_path.c_str(), config_ptr);
	
	// initialize rotator
	std::string rotator_port( config_ptr->rotator_serial_port.c_str() );
	ROTATOR rotator1(rotator_port.c_str());
	
	// capture image
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "\nCouldn't open the camera\n";

        return -1;
    }
		
	int width = config_ptr->image_width;
	int height = config_ptr->image_height;
	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

    cv::Mat image0 = cv::Mat::zeros(height, width, CV_8UC3);
    capture >> image0;
	
	// output pcd file
	std::string pcd_filename( config_ptr->pcd_out_path.c_str() );
	PCD_FILE pcd_file(pcd_filename, image0.rows * ( floor( (config_ptr->rotator_angle_degree - 0.00001) / config_ptr->rotator_angle_resolution) + 1 ));
	
	// initialize scaner
	SCANER scaner1(config_ptr);
	int *cache_pixel_x = new int[image0.rows];
	Point3_<float> *cache_point_coordinate = new Point3_<float>[image0.rows];
	Point3_<float> *cache_point_coordinate_2 = new Point3_<float>[image0.rows];
	
	for( float deg = 0.0; deg < config_ptr->rotator_angle_degree; deg += config_ptr->rotator_angle_resolution) {
		// run rotator
		cout << "run_rotator(), " << deg << " degrees" << endl;
		rotator1.run_rotator(deg);
		// capture
		capture >> image0;
    	if (image0.empty()) {
    	    break;
    	}

		scaner1.input_image(&image0);
		scaner1.get_pixel_x(cache_pixel_x);
		scaner1.get_coordinate_line(cache_point_coordinate, cache_pixel_x);
		scaner1.transform_coordinate(cache_point_coordinate_2, cache_point_coordinate, deg + config_ptr->rotator_coordinate_transform_base_degree);
		
		pcd_file.append(cache_point_coordinate_2, image0.rows);

    }
	
	delete[] cache_pixel_x;
	delete[] cache_point_coordinate;
	delete[] cache_point_coordinate_2;
	
	return 0;
}
