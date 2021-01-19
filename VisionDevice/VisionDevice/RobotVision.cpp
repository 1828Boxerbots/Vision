//#include "RobotVision.h"
//#include <opencv2/imgproc/imgproc.hpp>
//
//
//bool RobotVision::Init()
//{
//	m_camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
//	m_camera.SetResolution(640, 480);
//	m_cvSink = frc::CameraServer::GetInstance()->GetVideo();
//	m_outputStream = frc::CameraServer::GetInstance()->PutVideo("Normal", 640, 480);
//
//	return true;
//}
//
//void RobotVision::Tick()
//{
//	if (m_cvSink.GrabFrame(m_frame) == 0)
//	{
//		return;
//	}
//
//	cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
//
//	//m_outputStream.PutFrame(m_frame);
//	SendImage(m_frame);
//}
//
//void RobotVision::SendImage(cv::Mat frame)
//{
//	m_outputStream.PutFrame(frame);
//}
//
//bool RobotVision::GetBlob()
//{
//	if (m_cvSink.GrabFrame(m_frame) == 0)
//	{
//		return false;
//	}
//
//	cv::Point centroidPoints = CameraVision::SetColor(m_frame);
//
//	m_centroidX = centroidPoints.x;
//	m_centroidY = centroidPoints.y;
//
//	//Place a 2 line where the blob
//	cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0, 0, 255), 3);
//	cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
//
//	//Show where the center of the screen is on the camera
//	double screenCenter = m_frame.size().width / 2;
//	cv::line(m_frame, cv::Point(screenCenter, 0), cv::Point(screenCenter, m_frame.size().height), cv::Scalar(255, 0, 0), 3);
//
//	//Requires something like mathf to use isnan()
//	if (isnan(m_centroidX) && isnan(m_centroidY))
//	{
//		return false;
//	}
//
//	return true;
//}
