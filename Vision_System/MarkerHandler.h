/*
	@file	 MarkerHandler.h
	@author  Ante Javor
	@date    24.07.2017
	@version 1.0
	@brief   Frame class members declaration and definition.
*/

#pragma once
#ifdef MARKERHANDLER_h
#endif MARKERHANDLER_h

#include "Marker.h"
#include <opencv2\aruco.hpp>
#include <vector>

class MarkerHandler
{

public:

	MarkerHandler(cv::Mat &frame) : refrenceFrame(frame) {};
	void markerTracking();
	void showMarkerDistance();
	
private:

	void detectMarkers(cv::Mat& frame, cv::Ptr<cv::aruco::Dictionary> dictionary, std::vector<Marker>& detectedMarkers);
	void connectDetectedMarkers(cv::Mat& frame, std::vector<Marker> detectedMarkers);
	
	cv::Mat& refrenceFrame;
	cv::Ptr <cv::aruco::Dictionary> markerDictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	std::vector<Marker> detectedMarkers;

};

