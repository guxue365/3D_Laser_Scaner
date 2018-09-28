/* scaner.cpp
 * 
 * 
 * 
 */

#include "scaner.hpp"
#include "extract.hpp"

#include <opencv2/core/types.hpp>

using namespace cv;

SCANER::SCANER(CONFIG_S *config_ptr)
{
    this->f = config_ptr->f;
	this->s = config_ptr->s;
	this->pixel_size = config_ptr->image_pixel_size;
	this->angle_beta_rad = config_ptr->angle_beta_degree / 180.0 * 3.141592654;
	this->rotation_r = rotation_r;
	
}

SCANER::~SCANER()
{
	;
}

int SCANER::input_image(const cv::Mat *image_ptr)
{
	this->image_ptr = image_ptr;
	
	return 0;
}

// Can change to a different method in extract.cpp
int SCANER::get_pixel_x(int *cache_pixel_x)
{
	extract2_1(image_ptr, cache_pixel_x);
	
	return 0;
}

int SCANER::get_coordinate_pixel(int x, int y, Point3_<float> *point_ptr)
{
    float edge_PT = f * s / ((image_ptr->cols - x) * pixel_size);

    float edge_OP = ( (y - image_ptr->rows/2) * pixel_size ) / f * edge_PT;
    float edge_LT = edge_PT / tan(angle_beta_rad);

    point_ptr->x = edge_LT - rotation_r;
    point_ptr->y= edge_PT;
    point_ptr->z = -edge_OP;
    
    return 0;
}

int SCANER::get_coordinate_line(Point3_<float> *cache_point_coordinate, int *cache_pixel_x)
{
	for (int i = 0; i < image_ptr->rows; i++) {
		get_coordinate_pixel(cache_pixel_x[i], i, cache_point_coordinate + i);
	}
	
	return 0;
}

int SCANER::transform_coordinate(Point3_<float> *destination, Point3_<float> *source, float angle_sita_degree)
{
	float angle_sita_rad = angle_sita_degree / 180.0 * 3.141592654;

	for (int i = 0; i < image_ptr->rows; i++) {
		(destination + i)->x = (source + i)->x * cos(angle_sita_rad) - (source + i)->y * sin(angle_sita_rad);
		(destination + i)->y = (source + i)->x * sin(angle_sita_rad) + (source + i)->y * cos(angle_sita_rad);
		(destination + i)->z = (source + i)->z;
	}
	
	return 0;
}