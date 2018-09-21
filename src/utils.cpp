#include "utils.hpp"

#include <opencv2/core/types.hpp>

using namespace cv;

int distance_from_pixel(int x, int y, int img_height, Point3_<float> *point_ptr)
{
/*
       dist = a/(b-c*x)+d
*/
	// focal length
    const float f = 16.0;
    // CMOS width
    //const float b = 3.6288;
    
    const float pixel_size = 0.0014;
    // distance between laser and camera lens
    const float s = 50.0;

	const float angle_beta = 83.53 / 180 * 3.141592654;
	
	const float rotation_r  = 25.0;

    float edge_PT = f * s / (x * pixel_size);

    float edge_OP = ( (y - img_height/2) * pixel_size ) / f * edge_PT;
    float edge_LT = edge_PT / tan(angle_beta);

    point_ptr->x = edge_LT - rotation_r;
    point_ptr->y= edge_PT;
    point_ptr->z = edge_OP;
    
    return 0;
}

int coordinate_transform(Point3_<float> *dst, Point3_<float> *src, float angle_sita_degree)
{
	float angle_sita_rad = angle_sita_degree * 180.0 / 3.141592654;
	
	dst->x = src->x * cos(angle_sita_rad) - src->y * sin(angle_sita_rad);
	dst->y = src->x * sin(angle_sita_rad) + src->y * cos(angle_sita_rad);
	dst->z = src->z;
	
	return 0;
	
}
