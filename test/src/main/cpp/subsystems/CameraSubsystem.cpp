/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystem.h"

CameraSubsystem::CameraSubsystem() {}

void CameraSubsystem::InterlizeCamera(int port)
{
     video.open(port);

}
  void CameraSubsystem::IntakeFrame()
{
    video >> frame;

}
void CameraSubsystem::FilterFrame()
{
    inRange(frame, Scalar(0, 150, 0), Scalar(175, 255, 175), colorFiliter);//BGR
    
    morphologyEx(colorFiliter, openFilter, MORPH_OPEN, Morp, Point(-1, -1), 4);
    dilate(openFilter,dilution,Morp);
    morphologyEx(dilution, Output, MORPH_CLOSE, Morp,Point(-1,-1),4);
}
void CameraSubsystem::CenterMomment()
{
    moment = cv::moments(Output);
    center = cv::Point2f(moment.m10 / moment.m00, moment.m01 / moment.m00);

}
int CameraSubsystem::WhereToTurn()
{
    if ( center.x > 10 && center.x < 250)
    {
        // std::cout << "left" << std::endl;
        return -1;
    }
    if(center.x  > 350 && center.x < 640)
    {
        //std::cout << "right" << std::endl;
        return 1;
    }
    if(center.x  < 350 && center.x  > 250)
    {
        //std::cout << "center" << std::endl;
        return 0;
    }
    if (center.x < 0 || center.x > 640)
    {
        return 0; 
    }
    return 0;

}

void CameraSubsystem::PrintTurn(int turn)
{
    double printturn = turn;
    printX = center.x;
    frc::SmartDashboard::PutNumber("turn",printturn);
    frc::SmartDashboard::PutNumber("center of x",printX);
    //imshow("camera",Output);
 
}


// This method will be called once per scheduler run
void CameraSubsystem::Periodic() {}
