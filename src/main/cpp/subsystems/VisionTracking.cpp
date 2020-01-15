/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/VisionTracking.h"

VisionTracking::VisionTracking() : Subsystem("ExampleSubsystem") {}

void VisionTracking::InitDefaultCommand() {
  // Set the default command for a subsystem here.
  // SetDefaultCommand(new MySpecialCommand());
}

void VisionTracking::ImageProcessing()
{
  int low1 = 0;
  int low2 = 0;
  int low3 = 0;
  int high1 = 0;
  int high2 = 0;
  int high3 = 0;
  cv::Mat endImage;

  cv::VideoCapture cam;
  cv::Mat image;
  cam.open(0);
  cam >> image;

  cv::inRange(image, cv::Scalar(low1, low2, low3), cv::Scalar(high1, high2, high3), endImage);

  cv::imshow("BRUH", endImage);
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
