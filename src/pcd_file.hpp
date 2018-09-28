#ifndef _PCD_FILE_HPP_
#define _PCD_FILE_HPP_

#include <string>
#include <fstream>

#include <opencv2/core/types.hpp>

class PCD_FILE
{
private:
	std::fstream fs;

public:
	PCD_FILE(std::string pcd_filename, const int num_points);
	~PCD_FILE();
	int append(cv::Point3_<float> *point, int num = 1);

};


#endif //_PCD_FILE_HPP_
