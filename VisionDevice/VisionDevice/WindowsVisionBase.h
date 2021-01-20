#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <math.h>

class WindowsVisionBase
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	WindowsVisionBase(int index);

	/// <summary>
	/// Initialize Hardware
	/// </summary>
	/// <returns>
	///		true = initialization successful
	///		false = error occured
	/// </returns>
	bool Init();

	/// <summary>
	/// Which direction should the robot turn and how fast
	/// </summary
	/// 
	/// <returns>
	///		range is -1.0 to +1.0, negative value is turn left
	/// </returns>
	double WhereToTurn();

	/// <summary>
	/// Filters the image and gets the position of its center
	/// </summary>
	cv::Point SetColor(cv::Mat frame);

	virtual void Tick() { }; 

	virtual void Log(std::string title, std::string value);

protected:
	//Red
	const int LOWH_RED  = 0;
	const int HIGHH_RED  = 6;
	const int LOWS_RED  = 134;
	const int HIGHS_RED  = 255;
	const int LOWV_RED  = 0;
	const int HIGHV_RED  = 255;
	//Neon Green
	const int LOWH_GREEN  = 79;
	const int HIGHH_GREEN  = 91;
	const int LOWS_GREEN  = 56;
	const int HIGHS_GREEN  = 255;
	const int LOWV_GREEN = 250;
	const int HIGHV_GREEN = 255;

private:

	//Values that it is filtering by
	int m_iLowH = LOWH_RED ;
	int m_iHighH = HIGHH_RED ;
	int m_iLowS = LOWS_RED ;
	int m_iHighS = HIGHS_RED ;
	int m_iLowV = LOWV_RED ;
	int m_iHighV = HIGHV_RED ;

	//The index/port of the camera - given in the constructor
	int m_index;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//How big is the dead zone where WhereToTurn() = 0.0
	double m_deadZone = 50.0;

	//Holds the camera and raw image
	cv::VideoCapture m_camera;
	cv::Mat m_frame;

	/// <summary>
	/// Create a new window to display an image
	/// </summary>
	/// <param name="title">String of what the window is called</param>
	/// <param name="frame">The image that should be displayed</param>
	virtual void SendImage(std::string title, cv::Mat frame);

	/// <summary>
	/// Find the blob on the image
	/// </summary>
	/// <returns>True - The image is fine  False - The image is empty </returns>
	bool GetBlob();

	void ChangeColor(char color);

	virtual bool GetImage();
};

