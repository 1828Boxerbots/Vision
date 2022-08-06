// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>

#include "RobotContainer.h"

#include <cameraserver/CameraServer.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>

#include <frc/DriverStation.h>

class Robot : public frc::TimedRobot {
 public:

  static void VisionThread();
  static cv::Mat ProcessImg(cv::Mat img);

  void GetFMS();

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

 private:
  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  frc2::Command* m_autonomousCommand = nullptr;

  int lowH = 0;
  int highH = 7;
  int lowS = 104;
  int highS = 255;
  int lowV = 213;
  int highV = 255;

  double centroidX = -1;
  double centroidY = -1;

  RobotContainer m_container;
};
