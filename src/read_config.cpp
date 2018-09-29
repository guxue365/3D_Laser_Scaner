/* read_config.cpp
 * 读取config文件
 * 
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include "read_config.hpp"

using namespace std;

int readConfigFile(const char * cfgfilepath, CONFIG_S *config_ptr)
{
    fstream cfgFile;
    cfgFile.open(cfgfilepath);
    if( ! cfgFile.is_open())
    {
        cout<<"can not open cfg file!"<<endl;
        return false;
    }

    char tmp[128];
    while(!cfgFile.eof())
    {
        cfgFile.getline(tmp,128);
		if ( tmp[0] == '#' ) continue;
		
        string line(tmp);
		
        size_t pos = line.find('=');
        if(pos==string::npos) return false;
        string tmpKey = line.substr(0,pos);
 		
 		if ( strcmp( tmpKey.c_str(), "f" ) == 0 ) {
 			config_ptr->f = atof( line.substr(pos+1).c_str() );
 		} else if ( strcmp( tmpKey.c_str(), "s") == 0 ) {
 			config_ptr->s = atof( line.substr(pos+1).c_str() );
 		} else if ( strcmp( tmpKey.c_str(), "angle_beta_degree") == 0 ) {
 			config_ptr->angle_beta_degree = atof( line.substr(pos+1).c_str() );
 		} else if ( strcmp( tmpKey.c_str(), "rotation_r") == 0 ) {
 			config_ptr->rotation_r = atof( line.substr(pos+1).c_str() );
 			
 		} else if ( strcmp( tmpKey.c_str(), "image_width") == 0 ) {
 			config_ptr->image_width = atoi( line.substr(pos+1).c_str() );
	 	} else if ( strcmp( tmpKey.c_str(), "image_height") == 0 ) {
 			config_ptr->image_height = atoi( line.substr(pos+1).c_str() );
		} else if ( strcmp( tmpKey.c_str(), "image_pixel_size") == 0 ) {
			config_ptr->image_pixel_size = atof( line.substr(pos+1).c_str() );

		} else if ( strcmp( tmpKey.c_str(), "rotator_serial_port") == 0 ) {
 			config_ptr->rotator_serial_port = line.substr(pos+1);
		} else if ( strcmp( tmpKey.c_str(), "rotator_angle_degree") == 0 ) {
 			config_ptr->rotator_angle_degree = atof( line.substr(pos+1).c_str() );
		} else if ( strcmp( tmpKey.c_str(), "rotator_angle_resolution") == 0 ) {
 			config_ptr->rotator_angle_resolution = atof( line.substr(pos+1).c_str() );
		} else if ( strcmp( tmpKey.c_str(), "rotator_coordinate_transform_base_degree") == 0 ) {
 			config_ptr->rotator_coordinate_transform_base_degree = atof( line.substr(pos+1).c_str() );
 			
		} else if ( strcmp( tmpKey.c_str(), "pcd_out_path") == 0 ) {
 			config_ptr->pcd_out_path = line.substr(pos+1);
 		}
 			
    }

    return 0;
}

