/* extract.cpp
 * 逐行扫描image，获取激光点所在的列数，存入cache，cache长度为图片行数。
 * extract2_1是当前使用的方法。
 * 
 */

#include "extract.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

int extract1(const cv::Mat *img_ptr, int *cache_pixel_x)
{
	cv::Mat img_gray;
	cv::cvtColor(*img_ptr, img_gray, CV_RGB2GRAY);
	
	int height = img_gray.rows;
 	int	width = img_gray.cols;
	
	static const unsigned char THRESHOLD_MIN_PWR = 25;
    int maxPos = 0;
    unsigned char max = 0;

    int currentPos = 0;
	
	for (int i = 0; i < height; i++) {
		
		maxPos = 0;
		currentPos = 0;
		max = 0;
		while (currentPos < width) {
		    if (max < img_gray.at<uchar>(i, currentPos)) {
		        max = img_gray.at<uchar>(i, currentPos);
		        maxPos = currentPos;
		    }
		    currentPos++;
		}

		if (max < THRESHOLD_MIN_PWR) return -1;

		float logicPwr = 0.0f, totalPwr=0.0f;

		for ( currentPos = maxPos-3; currentPos <= maxPos+3; currentPos++)
		{
		    float currentPwr;
		    if (currentPos >= 0 && currentPos < width){
		       currentPwr = img_gray.at<uchar>(i, currentPos);
		    }else{
		       currentPwr = 0.0f;
		    }
		    logicPwr += currentPwr;
		    totalPwr += currentPwr*currentPos;
		}

		cache_pixel_x[i] = (int)(totalPwr / logicPwr);
	}
	
	return 0;
}


int extract2(const cv::Mat *img_ptr, int *cache_pixel_x)
{

	int height = img_ptr->rows;
 	int	width = img_ptr->cols;
 	
	float brightness = 0.0;
	float max = 0.0;
    int maxPos = -1;

    for (unsigned int i = 0; i < height; i++)
    {
        max  = 0.0;
        maxPos = -1;
        for (int j = 0; j < width; j++)
        {
            brightness = (img_ptr->at<Vec3b>(i,j)[0] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,j)[1] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,j)[2] & 0xFF ) / 255.0 * 100.0;
            if (brightness > max)
            {
                max = brightness;
                maxPos = j;
            }
        }
        
		float logicPwr = 0.0f, totalPwr=0.0f;

		for (int currentPos = maxPos-3; currentPos <= maxPos+3; currentPos++)
		{
		    float currentPwr;
		    if (currentPos>=0 && currentPos < width){
		       currentPwr = (img_ptr->at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    }else{
		       currentPwr = 0.0f;
		    }
		    logicPwr += currentPwr;
		    totalPwr += currentPwr*currentPos;
		}

		cache_pixel_x[i] = (int)totalPwr/logicPwr;
    }
    
    return 0;
}

int extract2_1(const cv::Mat *img_ptr, int *cache_pixel_x)
{
	int height = img_ptr->rows;
 	int	width = img_ptr->cols;
 	
	float brightness = 0.0;
	float max = 0.0;
    int maxPos = -1;

    for (unsigned int i = 0; i < height; i++)
    {
        max  = 0.0;
        maxPos = -1;
        for (int j = 0; j < width; j++)
        {
            brightness = (img_ptr->at<Vec3b>(i,j)[0] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,j)[1] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,j)[2] & 0xFF ) / 255.0 * 100.0;
            if (brightness > max)
            {
                max = brightness;
                maxPos = j;
            }
        }
        
        int currentPos = 0;
		for (currentPos = maxPos; currentPos < width; currentPos++)
		{
		    brightness = (img_ptr->at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    if (brightness < 0.7 * max ) {
		    	break;
		    }
			if (currentPos - maxPos > 50) {
				break;
		    }
		}
		int lb = currentPos;
		
		for (currentPos = maxPos; currentPos > 0; currentPos--)
		{
		    brightness = (img_ptr->at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img_ptr->at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    if (brightness < 0.7 * max ) {
		    	break;
		    }
			if (maxPos - currentPos > 50) {
				break;
		    }
		}
		int rb = currentPos;
		
		cache_pixel_x[i] = (lb + rb) / 2;
    }
    
    return 0;
}
