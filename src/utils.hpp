#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <opencv2/core/types.hpp>

int distance_from_pixel(int x, int y, int img_height, cv::Point3_<float> *point_ptr);
int coordinate_transform(cv::Point3_<float> *dst, cv::Point3_<float> *src, float angle_sita_degree);

#endif // _UTILS_HPP_
