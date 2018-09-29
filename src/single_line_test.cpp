/* single_line_test.cpp
 * 单条激光线测距 主函数
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

	
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "\nCouldn't open the camera\n";

        return -1;
    }

	int width = config_ptr->image_width;
	int height = config_ptr->image_height;
	capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);

    cv::Mat image0 = cv::Mat::zeros(width, height, CV_8UC3);
    capture >> image0;
	cv::Mat image0_laser = cv::Mat::zeros(image0.rows, image0.cols, CV_8U);
	
	//namedWindow("Window Original", CV_WINDOW_AUTOSIZE);
	namedWindow("Window Original", CV_WINDOW_NORMAL);
	namedWindow("Window Laser", CV_WINDOW_NORMAL | CV_WINDOW_FREERATIO | CV_GUI_EXPANDED);
	

	std::string pcd_filename("./point_cloud_2.pcd");
	PCD_FILE pcd_file(pcd_filename, image0.rows);
	
	SCANER scaner1(config_ptr);
	int *cache_pixel_x = new int[image0.rows];
	Point3_<float> *cache_point_coordinate = new Point3_<float>[image0.rows];
	
	while (1) {
		// capture
		capture >> image0;
    	if (image0.empty()) {
    	    return -1;
    	}
		scaner1.input_image(&image0);
		scaner1.get_pixel_x(cache_pixel_x);
		scaner1.get_coordinate_line(cache_point_coordinate, cache_pixel_x);
		

		for (int i = 0; i < image0.rows; i++) {
			cout << cache_pixel_x[i] << "\t" << (cache_point_coordinate + i)->y << endl;
			pcd_file.append(cache_point_coordinate + i);
		}


		for (int i = 0; i< image0.rows; i++) {
			image0_laser.at<uchar>(i, cache_pixel_x[i]) = 255;
		}

	
		cv::imshow("Window Original", image0);
		imshow("Window Laser", image0_laser);

		if ((cv::waitKey(5000) & 255) != 'q') {
        	continue;
		} else {
			break;
		}
	}
    	
	destroyWindow("Window Original");
	destroyWindow("Window Laser");
	
	delete[] cache_pixel_x;
	delete[] cache_point_coordinate;
	
	return 0;
}

