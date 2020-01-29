/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <opencv2/core.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
using namespace cv;

class CameraSubsystem : public frc2::SubsystemBase {
 public:
  CameraSubsystem();

  void InterlizeCamera(int port);
  void IntakeFrame();
  void FilterFrame();
  void CenterMomment();
  int WhereToTurn();
  void PrintTurn(int turn);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  Mat frame;
  Mat Morp = cv::getStructuringElement(MORPH_CROSS, Size(3, 3), Point(-1, 1));
  VideoCapture video;
  Mat output;
  Mat colorFiliter;
  Mat closeFilter;
  Mat openFilter;
  cv::Moments moment;
  cv::Point center;
};
