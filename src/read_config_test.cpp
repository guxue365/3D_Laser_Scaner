#include <iostream>
#include <string>

#include "read_config.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	CONFIG_S *config_ptr = new CONFIG_S;
	
	string config_path("./config");
	
	readConfigFile(config_path.c_str(), config_ptr);
	
	cout << config_ptr->f << endl << config_ptr->s << endl << config_ptr->angle_beta_degree << endl \
	<< config_ptr->rotation_r << endl << config_ptr->image_width << endl << config_ptr->image_height << endl \
	<< config_ptr->image_pixel_size << endl << config_ptr->rotator_serial_port << endl \
	<< config_ptr->rotator_angle_degree << endl << config_ptr->rotator_angle_resolution << endl \
	<< config_ptr->rotator_coordinate_transform_base_degree << endl << config_ptr->pcd_out_path << endl;
	
	return 0;
}
