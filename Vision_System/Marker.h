/*
	@file	 Marker.h
	@author  Ante Javor
	@date    24.07.2017
	@brief   Marker class members declaration.
*/

#pragma once
#ifndef MARKER_H
#endif MARKER_H

#include <opencv2\core.hpp>
#include <vector>

class Marker
{

public:

	Marker(int markerNum, std::vector<cv::Point2f> markerCorners, cv::Mat &frame);
	cv::Point2f getMarkerCenter();
	int getMarkerID() const;

 private:

	 cv::Mat capFrame;
	 int markerID;
	 cv::Point2f center;
	 std::vector<cv::Point2f> markerPoints;
	 void calculateMarkerCenter();
};


