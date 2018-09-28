/* pcd_file.cpp
 * 写pcd文件
 * 
 * 
 */

#include "pcd_file.hpp"
#include <string>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

using namespace std;
using namespace cv;

PCD_FILE::PCD_FILE(std::string pcd_filename, const int num_points)
{
	//num_points = num_points;
	fs.open(pcd_filename.c_str(), ios::out);
	
	fs << "# .PCD v.7 - Point Cloud Data file format\n";
    fs << "VERSION .7\n";
    fs << "FIELDS x y z\n";
    fs << "SIZE 4 4 4\n";
    fs << "TYPE F F F\n";
    fs << "COUNT 1 1 1\n";
    fs << "WIDTH " << num_points << "\n";
    fs << "HEIGHT 1\n";
    fs << "VIEWPOINT 0 0 0 1 0 0 0\n";
    fs << "POINTS " << num_points << "\n";
    fs << "DATA ascii\n";
    
}

PCD_FILE::~PCD_FILE()
{
	fs.close();
}

int PCD_FILE::append(Point3_<float> *point, int num)
{
    for (int i = 0; i < num; i++ ) {
        fs << (point + i)->x << " " << (point + i)->y << " " << (point + i)->z << endl;
    }
	
	return 0;
}
