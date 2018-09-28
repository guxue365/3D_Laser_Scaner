#ifndef _READ_CONFIG_HPP_
#define _READ_CONFIG_HPP_

#include <string>

typedef struct CONFIG_S{
	float f;
	float s;
	float angle_beta_degree;
	float rotation_r;
	
	int image_width;
	int image_height;
	float image_pixel_size;
	
	std::string rotator_serial_port; //("/dev/ttyUSB0");
	float rotator_angle_degree = 90.0;
	float rotator_angle_resolution = 1.0;
	float rotator_coordinate_transform_base_degree = -90.0;
	
	std::string pcd_out_path; // ("./point_cloud.pcd");
	
} CONFIG_S;

int readConfigFile(const char * cfgfilepath, CONFIG_S *config_ptr);

#endif // _READ_CONFIG_HPP_
