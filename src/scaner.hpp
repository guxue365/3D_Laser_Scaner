#ifndef _SCANER_HPP_
#define _SCANER_HPP_

#include <opencv2/opencv.hpp>

#include "read_config.hpp"

class SCANER
{
private:
	// focal length
    float f;
    
    float pixel_size;

    // distance between laser and camera lens
    float s;

	float angle_beta_rad; // = 83.53 / 180 * 3.141592654;
	
	float rotation_r;
	
	const cv::Mat *image_ptr;

public:
	SCANER(CONFIG_S *config_ptr);
	~SCANER();
	// 输入预处理的图像到scaner
	int input_image(const cv::Mat *image_ptr);

	// 从图像每行中提取激光点所在列数
	int get_pixel_x(int *cache_pixel_x);

	// 获取单个激光点坐标
	int get_coordinate_pixel(int x, int y, cv::Point3_<float> *point_ptr);

	// 获取一条线上的激光点坐标（未旋转的局部坐标）
	int get_coordinate_line(cv::Point3_<float> *cache_point_coordinate, int *cache_pixel_x);

	// 变换局部坐标到全局坐标。转子0度，对应全局坐标系angle_sita_degree，比如-90度。
	int transform_coordinate(cv::Point3_<float> *destination, cv::Point3_<float> *source, float angle_sita_degree);

};

#endif // _SCANER_HPP_
