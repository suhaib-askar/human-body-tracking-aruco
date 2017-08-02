/*
	@file	 Main.cpp
	@author  Ante Javor
	@date    24.07.2017
	@version 1.0 
	@brief   Main program loop for loading frame and window.
*/

#include "Marker.h"
#include "Frame.h"
#include "Constants.h"

#include <opencv2\highgui.hpp>
#include <iostream>

/*
	@brief	 Opens the frame and window and pass frame data to frame object for aruco marker tracking.

	@return  a integer value that indicates status of function progress.

*/

int visionSystem();

/* Main program loop. */
int main()
{
	
	visionSystem();

	return 0;
}


int  visionSystem()
{
	cv::Mat frame;
	cv::VideoCapture vid(constants::VIDEO_SOURCE);

	if (!vid.isOpened())
	{
		std::cout << "Problem with video source, check camera ID!" << std::endl;
		return -1;
	}

	cv::namedWindow(constants::WINDOW_NAME, cv::WINDOW_FREERATIO);

	/* Loop for reading, loadnig and processing frames. */
	while (true)
	{
		if (!vid.read(frame))
		{
			std::cout << "Problem with loading frame!" << std::endl;
			break;
		}

		Frame frameObject{ frame };
		frameObject.markerTracking();
		frameObject.showMarkerDistance();

		cv::imshow("Vision system", frame);
		if (cv::waitKey(constants::END_KEY) >= 0)
			break;
	}
	return 0;
}
