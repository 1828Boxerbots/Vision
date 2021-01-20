#include "Drivers/CameraDrivers/WindowsVisionBase.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <String>

WindowsVisionBase::WindowsVisionBase(int index)
{
	m_index = index;
}

bool WindowsVisionBase::Init()
{
	//Check to see if the camera is working
	if (m_camera.open(m_index) == false)
	{
		std::cout << "The Camera could not be accessed";
		return false;
	}

	//Create the sliders window
	std::string sliderWindowName = "Sliders";
	cv::namedWindow(sliderWindowName, cv::WINDOW_AUTOSIZE);

	cv::createTrackbar("LowH", sliderWindowName, &m_iLowH, 179); //Hue (0-179)
	cv::createTrackbar("HighH", sliderWindowName, &m_iHighH, 179);
	cv::createTrackbar("LowS", sliderWindowName, &m_iLowS, 255); //Saturation (0-255)
	cv::createTrackbar("HighS", sliderWindowName, &m_iHighS, 255);
	cv::createTrackbar("LowV", sliderWindowName, &m_iLowV, 255); //Value (0-255)
	cv::createTrackbar("HighV", sliderWindowName, &m_iHighV, 255);
	return true;
}

double WindowsVisionBase::WhereToTurn()
{
	//Check if there is a blob
	if (GetBlob() == false /*|| m_centroidX == nan( && m_centroidY == nan(ind)*/)
	{
		return -2.0;
	}

	//std::cout << m_centroidX << std::endl;
	//std::cout << m_centroidY << std::endl;

	//Get the Center of the screen
	double screenCenter = m_frame.size().width / 2;
	//Get Dead zone values
	double highDedZone = screenCenter + m_deadZone;
	double lowDedZone = screenCenter - m_deadZone;
	//Check if we are in the dead zone
	if (m_centroidX > lowDedZone && m_centroidX < highDedZone)
	{
		return 0.0;
	}

	//Use some MATH to turn our position into a percentage and return
	double powerPercentage = (m_centroidX - screenCenter) / screenCenter;
	cv::Mat textImg = m_frame;
	cv::QtFont font;
	std::string powerPercentageStr = std::to_string(powerPercentage);

	cv::putText(textImg, powerPercentageStr, cv::Point(m_centroidX, m_centroidY), cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 0, 0), 2);

	//cv::addText(textImg, "Ben", cv::Point(320, 240), font);
	//SendImage("TextImage", textImg);
	return (m_centroidX - screenCenter) / screenCenter;
}


void WindowsVisionBase::SendImage(std::string title, cv::Mat frame)
{
	cv::imshow(title.c_str(), frame); 
}

bool WindowsVisionBase::GetImage()
{
	m_camera >> m_frame;
	
	if(m_frame.empty() == true)
	{
		return false;
	}

	return true;
}

void WindowsVisionBase::Log(std::string title, std::string value)
{
	std::cout << title << ": " << value << "\n" << std::endl;
}

bool WindowsVisionBase::GetBlob()
{
	//std::cout << "Press now!" << std::endl;
	if (cv::waitKey(120) == 'r')
	{
		ChangeColor('r');
	}
	if (cv::waitKey(120) == 27)
	{
		ChangeColor('g');
	}

	//Gets one frame from camera
	if(GetImage() == false)
	{
		return false; //Exit if empty
	}

	//Filter the image
	cv::Point momentPoint = SetColor(m_frame);
	m_centroidX = momentPoint.x;
	m_centroidY = momentPoint.y;

	//Place a 2 line where the blob is
	cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0,0,255), 3);
	cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);

	//Show where the center of the screen is on the camera
	double screenCenter = m_frame.size().width / 2;
	cv::line(m_frame, cv::Point(screenCenter, 0), cv::Point(screenCenter, m_frame.size().height), cv::Scalar(255, 0, 0), 3);

	//Display the new image
	SendImage("raw image", m_frame);

	cv::waitKey(1);

	//Checks is there is no blob
	if (isnan(m_centroidX) && isnan(m_centroidY))
	{
		return false;
	}

	return true;
}

cv::Point WindowsVisionBase::SetColor(cv::Mat frame)
{
	//Change the camera image from BGR to HSV - Blue Green Red to Hue Saturation Value
	cv::Mat imgHSV;
	cv::cvtColor(frame, imgHSV, cv::COLOR_BGR2HSV);
	SendImage("grey image", imgHSV);

	//Looks for specifc colors in the image
	cv::Mat imgThresholded;
	cv::inRange(imgHSV, cv::Scalar(m_iLowH, m_iLowS, m_iLowV), cv::Scalar(m_iHighH, m_iHighS, m_iHighV), imgThresholded);
	//Display Filtered Image
	SendImage("Threshold", imgThresholded);
	// Find moments of the image
	cv::Moments m = cv::moments(imgThresholded, true);
	m_centroidX = m.m10 / m.m00;
	m_centroidY = m.m01 / m.m00;
	return cv::Point (m_centroidX, m_centroidY);

}

void WindowsVisionBase::ChangeColor(char color)
{
	switch (color)
	{
	case 'r':
		m_iLowH = LOWH_RED;
		m_iLowS = LOWS_RED;
		m_iLowV = LOWV_RED;
		m_iHighH = HIGHH_RED;
		m_iHighS = HIGHS_RED;
		m_iHighV = HIGHV_RED;
		std::cout << "Changed to red" << std::endl;
		break;
	case 'g':
		m_iLowH = LOWH_GREEN;
		m_iLowS = LOWS_GREEN;
		m_iLowV = LOWV_GREEN;
		m_iHighH = HIGHH_GREEN;
		m_iHighS = HIGHS_GREEN;
		m_iHighV = HIGHV_GREEN;
		std::cout << "Changed to green" << std::endl;
		break;
	default:
		std::cout << "Default" << std::endl;
		break;
	}
}
