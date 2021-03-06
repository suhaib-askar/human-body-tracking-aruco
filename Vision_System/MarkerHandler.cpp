/*
	@file	 MarkerHandler.cpp
	@author  Ante Javor
	@date    24.07.2017
	@brief   Marker class functions definition.
*/

#include "Marker.h"
#include "MarkerHandler.h"
#include "Constants.h"
#include <opencv2\imgproc.hpp>
#include <string>

/*
	@brief Detect markers from the frame and store them sorted by markerID in vector of marker objects.
	@param frame is a refrence of opencv Mat type that holds the current frame.
	@param dictionary is a pointer to aruco dictionary that holds information about markers that should be detected, like size and data.
	@param detectedMarkers is refrence to vector that hold markers objects, all detected markers from current frame will be sorted and stored in here.
	@return void
*/

void MarkerHandler::detectMarkers(cv::Mat& frame, cv::Ptr<cv::aruco::Dictionary> dictionary, std::vector<Marker>& detectedMarkers)
{
	std::vector<std::vector<cv::Point2f>> markerCorners;
	std::vector<int> markersID;

	cv::aruco::detectMarkers(frame, dictionary, markerCorners, markersID);
	cv::aruco::drawDetectedMarkers(frame, markerCorners, markersID);

	/* Stroing markers an sorting them by ID. */
	if (markersID.size() > 0)
	{
		for (int i = 0; i < markersID.size(); i++)
		{
			detectedMarkers.push_back(Marker{ markersID[i], markerCorners[i], frame });
		}
		auto ReOrder = [](Marker one, Marker two) { return(one.getMarkerID() < two.getMarkerID()); };
		sort(detectedMarkers.begin(), detectedMarkers.end(), ReOrder);
	}
}

/*
	@brief Connects the markers by drawing the line on passed frame from marker to marker.
	@param frame is a refrence of opencv Mat type that holds the current frame.
	@param detectedMarkers is refrence to vector that hold markers, all passed markers will be connected.
	@return void
*/

void MarkerHandler::connectDetectedMarkers(cv::Mat& frame, std::vector<Marker> detectedMarkers)
{
		std::vector<cv::Point2i> centerPointsLowerBody;
		std::vector<cv::Point2i> centerPointsUpperBody;
		std::vector<cv::Point2i> middlePoints;

		/* Storing and sorting center points of detected markers. */
		for (auto object : detectedMarkers)
		{
			
			if (object.getMarkerID() < constants::UPPER_BODY_LIMIT)
			{
				centerPointsUpperBody.push_back(object.getMarkerCenter());
				if (object.getMarkerID() == constants::MIDDLE_MARKER_CHEST)
					middlePoints.push_back(object.getMarkerCenter());
			}
			else
			{
				if (object.getMarkerID() < constants::LOWER_BODY_LIMIT)
				{
					centerPointsLowerBody.push_back(object.getMarkerCenter());
					if (object.getMarkerID() == constants::MIDDLE_MARKER_BELLY)
						middlePoints.push_back(object.getMarkerCenter());
				}
				else
					continue;
			}

		}

		/* Drawing functions that connect center points. */
		cv::polylines(frame, centerPointsUpperBody, false, cv::Scalar{ 0,0,0 }, 3, 8);
		cv::polylines(frame, centerPointsLowerBody, false, cv::Scalar{ 0,0,0 }, 3, 8);

		if (middlePoints.size() == 2)
			cv::line(frame, middlePoints[0], middlePoints[1],cv::Scalar{ 0,0,0 }, 3, 8);
	}

/*
	@brief Function measure distance between markers defined in Constants.h and print distance on frame.
	@return void
*/

void MarkerHandler::showMarkerDistance()
{
	cv::Point2f markerCenterOne;
	cv::Point2f markerCenterTwo;

	cv::Point2f markerChest;
	cv::Point2f markerBelly;

	for (auto object : detectedMarkers)
	{
	
		if (object.getMarkerID() == constants::DISTANCE_REF_MARKER_ONE)
			markerCenterOne = object.getMarkerCenter();
		else if (object.getMarkerID() == constants::DISTANCE_REF_MARKER_TWO)
			markerCenterTwo = object.getMarkerCenter();
		else if (object.getMarkerID() == constants::MARKER_MEASURE_START)
			markerChest = object.getMarkerCenter();
		else if (object.getMarkerID() == constants::MARKER_MEASURE_END)
			markerBelly = object.getMarkerCenter();
		else
			continue;
	}

	/* Measuring distance between, and put it on frame */
	if (markerChest.x > 0 && markerBelly.x > 0 && markerCenterOne. x > 0 && markerCenterTwo.x > 0 )
	{
		cv::LineIterator iterator(refrenceFrame, markerCenterOne, markerCenterTwo, 8, true);
		double numberOfPixels = iterator.count;
		cv::LineIterator iteratorTwo(refrenceFrame, markerChest, markerBelly, 8, true);
		double numberOfPixelsChest = iteratorTwo.count;
		double distance = (constants::REFRENCE_DISTANCE / numberOfPixels) * numberOfPixelsChest;

		std::string distanceInCm{ "Lenght chest: " };
		std::string temp = std::to_string(distance);
		distanceInCm.append(temp);
		distanceInCm.append(" cm");
		cv::putText(refrenceFrame, distanceInCm, cv::Point(400, 400), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar{ 0,0,0 }, 2, 8);
	}

}

/*
	@brief Packs two functions in one, detectMarkers and connectDetectedMarkers.
	@return void
*/

void MarkerHandler::markerTracking()
{
	MarkerHandler::detectMarkers(refrenceFrame, markerDictionary, detectedMarkers);
	MarkerHandler::connectDetectedMarkers(refrenceFrame, detectedMarkers);

}
