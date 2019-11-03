/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
 using namespace frc;
 using namespace cv;

 void Robot::Video()
 {
   //create a camera and start the camera
  cs::UsbCamera Camera = CameraServer::GetInstance()->StartAutomaticCapture();

   Camera.SetResolution(640,480);
 
   //Get frames form the camera 
   cs::CvSink sink = CameraServer::GetInstance()->GetVideo();
   //convert fram into gray scale (600 by 400)
   cs::CvSource source = CameraServer::GetInstance()->PutVideo("Gray",640,480);

  // create a mat(a array with more then one dimension) variable
  Mat matSource;
  //Mat matOutput;
  while(true)
  {
    //grabbing a frame
    sink.GrabFrame(matSource);

    //convert the source frame into Gray scale
    //cvtColor(matSource,matOutput,COLOR_BGR2GRAY);

    //Put the frame back
    source.PutFrame(matSource);
  }
  


 }
void Robot::RobotInit() 
{

  //create a thread for only vison processing
  std::thread VideoProcessing(Video);

  VideoProcessing.detach();

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
 
}

void Robot::AutonomousPeriodic() {
  
}

void Robot::TeleopInit() {
  
  
}

void Robot::TeleopPeriodic() 
{
  while(IsEnabled() && IsOperatorControl())
  {
    
  }
}

void Robot::TestPeriodic() {}

Robot::Robot()
{

}
Robot::~Robot()
{

}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
