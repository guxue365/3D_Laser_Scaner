#include "extract.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

using namespace cv;

int extract1(Mat img_gray, int *cache)
{
	int height = img_gray.rows;
 	int	width = img_gray.cols;
	
	static const unsigned char THRESHOLD_MIN_PWR = 25;
    static const unsigned char THRESHOLD_BLOB_DIFF = 10;
    static const int           THRESHOLD_ALLOWED_BLOB_SZ = 20;
    int centerPos = 0;
    unsigned char maxPwr = 0;

    int currentPos = 0;
	
	for (int i = 0; i < height; i++) {
		
		centerPos = 0;
		currentPos = 0;
		maxPwr = 0;
		while (currentPos < width) {
		    if (maxPwr < img_gray.at<uchar>(i, currentPos)) {
		        maxPwr = img_gray.at<uchar>(i, currentPos);
		        centerPos = currentPos;
		    }
		    currentPos++;
		}

		if (maxPwr < THRESHOLD_MIN_PWR) return -1;

		float logicPwr = 0.0f, totalPwr=0.0f;

		for ( currentPos = centerPos-3; currentPos <= centerPos+3; currentPos++)
		{
		    float currentPwr;
		    if (currentPos>=0 && currentPos < width){
		       currentPwr = img_gray.at<uchar>(i, currentPos);
		    }else{
		       currentPwr = 0.0f;
		    }
		    logicPwr+=currentPwr;
		    totalPwr+=currentPwr*currentPos;
		}

		cache[i] = (int)totalPwr/logicPwr;
	
		//cache[i] = centerPos;	
	}
	
	return 0;
}


int extract2(Mat img, int *cache)
{

	int height = img.rows;
 	int	width = img.cols;
 	
	float x(0.0), y(0.0), z(0.0), brightness(0.0), max(0.0), radius(0.0), cameraAngle(0.0);
    unsigned int px(0);
    int maxpos(-1);

    for (unsigned int i = 0; i < height; i++)
    {
        // Find the brightest pixel
        /** @todo do we have to specify minimal pixel brightness in order not to use dark points for object values ??!!! */
        max  = 0.0;
        maxpos = -1;
        for (int j = 0; j < width; j++)
        {
            brightness = (img.at<Vec3b>(i,j)[0] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,j)[1] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,j)[2] & 0xFF ) / 255.0 * 100.0;
            /**
            * @todo use swap here ?
            */
            if (brightness > max)
            {
                max = brightness;
                maxpos = j;
            }
        }
        
		float logicPwr = 0.0f, totalPwr=0.0f;

		for (int currentPos = maxpos-3; currentPos <= maxpos+3; currentPos++)
		{
		    float currentPwr;
		    if (currentPos>=0 && currentPos < width){
		       currentPwr = (img.at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    }else{
		       currentPwr = 0.0f;
		    }
		    logicPwr+=currentPwr;
		    totalPwr+=currentPwr*currentPos;
		}

		cache[i] = (int)totalPwr/logicPwr;
        
        //cache[i] = maxpos;
    }
    
    return 0;
}

int extract2_1(Mat img, int *cache)
{

	int height = img.rows;
 	int	width = img.cols;
 	
	float x(0.0), y(0.0), z(0.0), brightness(0.0), max(0.0), radius(0.0), cameraAngle(0.0);
    unsigned int px(0);
    int maxpos(-1);

    for (unsigned int i = 0; i < height; i++)
    {
        // Find the brightest pixel
        /** @todo do we have to specify minimal pixel brightness in order not to use dark points for object values ??!!! */
        max  = 0.0;
        maxpos = -1;
        for (int j = 0; j < width; j++)
        {
            brightness = (img.at<Vec3b>(i,j)[0] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,j)[1] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,j)[2] & 0xFF ) / 255.0 * 100.0;
            /**
            * @todo use swap here ?
            */
            if (brightness > max)
            {
                max = brightness;
                maxpos = j;
            }
        }
        
        int currentPos = 0;
		for (currentPos = maxpos; currentPos < width; currentPos++)
		{
		    float currentPwr;
	       	currentPwr = (img.at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    if (currentPwr < 0.7 * max ) {
		    	break;
		    }
			if (currentPos - maxpos > 50) {
				break;
		    }
		}
		int lb = currentPos;
		
		for (currentPos = maxpos; currentPos > 0; currentPos--)
		{
		    float currentPwr;
	       	currentPwr = (img.at<Vec3b>(i,currentPos)[0] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[1] & 0xFF ) / 255.0 +
                         (img.at<Vec3b>(i,currentPos)[2] & 0xFF ) / 255.0 * 100.0;
		    if (currentPwr < 0.7 * max ) {
		    	break;
		    }
			if (maxpos - currentPos > 50) {
				break;
		    }
		}
		int rb = currentPos;

		
		cache[i] = (lb + rb) / 2;
    }
    
    return 0;
}
