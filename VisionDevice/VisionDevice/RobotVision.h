//#pragma once
//#include "CameraVision.h"
////#include <cameraserver/CameraServer/h>
//
//class RobotVision : public CameraVision
//{
//public:
//	//RobotVision();
//	bool Init() override;
//	void Tick();
//private:
//	void SendImage(cv::Mat frame);
//	bool GetBlob() override;
//
//	//The points that hold the center of blob
//	double m_centroidX;
//	double m_centroidY;
//
//	//How big is the dead zone where WhereToTurn() = 0.0
//	double m_deadZone = 50.0;
//
//	//Holds the camera and raw image
//	cs::UsbCamera m_camera;
//	cv::Mat m_frame;
//	cs::CvSink m_cvSink;
//	cs::CvSource m_outputStream;
//
//	const int LOWH_RED = 0;
//	const int HIGHH_RED = 6;
//	const int LOWS_RED = 134;
//	const int HIGHS_RED = 255;
//	const int LOWV_RED = 0;
//	const int HIGHV_RED = 255;
//
//	//Values that it is filtering by
//	int m_iLowH = LOWH_RED;
//	int m_iHighH = HIGHH_RED;
//	int m_iLowS = LOWS_RED;
//	int m_iHighS = HIGHS_RED;
//	int m_iLowV = LOWV_RED;
//	int m_iHighV = HIGHV_RED;
//};
//
