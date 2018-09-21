#include <iostream>
#include <unistd.h>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "extract.hpp"
#include "pcd_file.hpp"
#include "rotator.hpp"
#include "utils.hpp"

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{

	String rotator_port("/dev/ttyUSB0");
	ROTATOR rotator1(rotator_port.c_str());
	
    cv::VideoCapture capture(0);
    if (!capture.isOpened()) {
        cout << "\nCouldn't open the camera\n";

        return -1;
    }

	capture.set(CV_CAP_PROP_FRAME_WIDTH, 2592);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1944);

    cv::Mat image0;
	//cv::Mat image0_laser = cv::Mat::zeros(image0.rows, image0.cols, CV_8U);
	
	namedWindow("Window Original", CV_WINDOW_AUTOSIZE);
	//namedWindow("Window Laser", CV_WINDOW_AUTOSIZE);
	
	int *cache = new int[image0.rows];
	std::string pcd_filename("./point_cloud.pcd");
	PCD_FILE pcd_file(pcd_filename, 180 * 1944);
	
	for( int deg = 0; deg < 180; deg++) {
		// run rotator
		rotator1.run_rotator(deg);
		// capture
		capture >> image0;
    	if (image0.empty()) {
    	    break;
    	}
		
		extract2_1(image0, cache);
		/*
		for (int i = 0; i< image0.rows; i++) {
			image0_laser.at<uchar>(i, cache[i]) = 255;
		}
		*/
		for (int i = 0; i < image0.rows; i++) {
			Point3_<float> result, result_transform;
			distance_from_pixel(cache[i], i, image0.rows, &result);
			coordinate_transform(&result_transform, &result, deg - 90.0);
			// cout << result.x << "\t" << result.y << "\t" << result.z << "\t" << result_transform.x << "\t" << result_transform.y << "\t" << result_transform.z << endl;
			pcd_file.append(&result_transform);
		}
	
		cv::imshow("Window Original", image0);
		//imshow("Window Laser", image0_laser);

	    //if ((cv::waitKey(30) & 255) == 27) {
          //  break;
        //}
        
        //sleep(10);
    }

	destroyWindow("Window Original");
	//destroyWindow("Window Laser");
		
	delete cache;
	
	return 0;
}

