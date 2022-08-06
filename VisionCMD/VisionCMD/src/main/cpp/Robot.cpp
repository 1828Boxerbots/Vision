// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

void Robot::VisionThread()
{
  cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
  camera.SetResolution(320, 240);
  cs::CvSink cvSink = frc::CameraServer::GetVideo();
  cs::CvSource outputStream = frc::CameraServer::PutVideo("Vid", 320, 240);
  cv::Mat source;
  cv::Mat output;

  while(true)
  {
    if(cvSink.GrabFrame(source) == 0)
    {
      continue;
    }

    output = ProcessImg(source);
    outputStream.PutFrame(output);
  }
}

cv::Mat Robot::ProcessImg(cv::Mat img)
{
  cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
  cv::Mat kernel = cv::Mat::ones(cv::Size(3, 3), cv::MORPH_DILATE);
  cv::Scalar low(lowH, lowS, lowV);
  cv::Scalar high(highH, highS, highV);
  cv::inRange(img, low, high, img);

  std::vector<std::vector<cv::Point>> contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::dilate(img, img, kernel);
  cv::findContours(img, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
  
  cv::Mat contoursIMG = cv::Mat::zeros(img.rows, img.cols, CV_8UC3);

  for(int i = 0; i < contours.size(); i++)
  {
    cv::Rect boundRect = cv::boundingRect(contours[i]);
    centroidX = boundRect.x + (double)(boundRect.width / 2);
    centroidY = boundRect.y + (double)(boundRect.height / 2);

    //square 
    cv::Scalar color(0, 0, 255);
    cv::Point topLeft(centroidX - (boundRect.width / 2), centroidY + (boundRect.height / 2));
    cv::Point topRight(centroidX + (boundRect.width / 2), centroidY + (boundRect.height / 2));
    cv::Point bottomLeft(centroidX - (boundRect.width / 2), centroidY - (boundRect.height / 2));
    cv::Point bottomRight(centroidX + (boundRect.width / 2), centroidY - (boundRect.height / 2));
    cv::line(contoursIMG, topLeft, topRight, color, 3);
    cv::line(contoursIMG, topLeft, bottomLeft, color, 3);
    cv::line(contoursIMG, bottomLeft, bottomRight, color, 3);
    cv::line(contoursIMG, bottomRight, topRight, color, 3);

    cv::drawContours(contoursIMG, contours, i, cv::Scalar(255, 0, 0), 2);
  }

  return contoursIMG;
}

void Robot::GetFMS()
{
  // std::string data;
  // data = frc::DriverStation::GetGameSpecificMessage();
  // if(data.length() > 0)
  // {
  //   char copy[60];
  //   strcpy(copy, data.c_str());
  //   char *put = strtok(copy, "-");
  //   for()
  // }
}

void Robot::RobotInit() 
{
  std::thread visionThread(VisionThread);
  visionThread.detach();
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  m_autonomousCommand = m_container.GetAutonomousCommand();

  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Cancel();
    m_autonomousCommand = nullptr;
  }
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
