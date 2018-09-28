#ifndef _EXTRACT_HPP_
#define _EXTRACT_HPP_

#include <opencv2/core/types.hpp>

int extract1(const cv::Mat *img_ptr, int *cache_pixel_x);
int extract2(const cv::Mat *img_ptr, int *cache_pixel_x);
int extract2_1(const cv::Mat *img_ptr, int *cache_pixel_x);

#endif // _EXTRACT_HPP_
