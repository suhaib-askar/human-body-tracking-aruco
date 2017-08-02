/*
	@file	 Constants.h
	@author  Ante Javor
	@date    24.07.2017
	@version 1.0
	@brief   Constants namespace and variables definition.
*/


#pragma once
#ifdef CONSTANTS_H
#endif CONSTANTS_H

#include <string>


namespace constants
{
	const int END_KEY = 30;
	const int VIDEO_SOURCE = 0;
	const int MIDDLE_MARKER_CHEST = 3;
	const int MIDDLE_MARKER_BELLY = 10;
	const int UPPER_BODY_LIMIT = 7;
	const int LOWER_BODY_LIMIT = 25;
	const int DISTANCE_REF_MARKER_ONE = 29;
	const int DISTANCE_REF_MARKER_TWO = 30;
	const int REFRENCE_DISTANCE = 46;
	const int MARKER_MEASURE_START = 3;
	const int MARKER_MEASURE_END = 10;
	const std::string WINDOW_NAME{ "Vision system" };
}
