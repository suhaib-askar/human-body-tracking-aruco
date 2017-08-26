/*
	@file	 Marker.cpp
	@author  Ante Javor
	@date    24.07.2017
	@brief   Marker class function and constructor definition.
*/

#include "Marker.h"
#include <opencv2\imgproc.hpp>

/*
	@brief Marker constructor.
	@param markerNum integer that holds marker ID
	@param markerCorners vector that holds opencv type point2f with stored all marker corners.
	@param frame is a refrence of opencv Mat type that holds the current frame.
*/

Marker::Marker(int markerNum, std::vector<cv::Point2f> markerCorners, cv::Mat &frame)
{
	markerID = markerNum;
	capFrame = frame;
	for (int i = 0; i < markerCorners.size(); i++)
	{
		markerPoints.push_back(markerCorners[i]);
	}
}

/*
	@brief Returns the marker ID.
	@return The integer that represent marker ID value.
*/

int Marker::getMarkerID() const
{
	return markerID;
}

/*
	@brief Calculates the current marker center.
	@return void
*/

void Marker::calculateMarkerCenter()
{
	cv::LineIterator iter(capFrame, markerPoints[0], markerPoints[2], 8, false);
	for (int i = 0; i < iter.count; i++)
	{
		if (iter.count / 2 == i)
		{
			center = iter.pos();
		}
		++iter;
	}
}

/*
	@brief Return the marker center.
	@return Opencv data type Point2f that represents marker center.

*/

cv::Point2f Marker::getMarkerCenter() 
{
	Marker::calculateMarkerCenter();
	return center;
}



