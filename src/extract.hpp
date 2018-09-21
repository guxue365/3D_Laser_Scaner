#ifndef _EXTRACT_HPP_
#define _EXTRACT_HPP_

#include <opencv2/core/types.hpp>

int extract1(cv::Mat img_gray, int *cache);
int extract2(cv::Mat img, int *cache);
int extract2_1(cv::Mat img, int *cache);

#endif // _EXTRACT_HPP_
