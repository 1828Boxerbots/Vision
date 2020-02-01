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
    inRange(frame, Scalar(0, 0, 200), Scalar(120, 120, 255), colorFiliter);//BGR
    morphologyEx(colorFiliter, closeFilter, MORPH_CLOSE, Morp,Point(-1,-1),4);
    morphologyEx(closeFilter, openFilter, MORPH_OPEN, Morp, Point(-1, -1), 4);
}
void CameraSubsystem::CenterMomment()
{
    moment = cv::moments(openFilter);
    center = cv::Point2f(moment.m10 / moment.m00, moment.m01 / moment.m00);

}
int CameraSubsystem::WhereToTurn()
{
    if (center.x < 270)
    {
        // std::cout << "left" << std::endl;
        return -1;
    }
    if(center.x  > 370)
    {
        //std::cout << "right" << std::endl;
        return 1;
    }
    if(center.x  < 370 && center.x  > 270)
    {
        //std::cout << "center" << std::endl;
        return 0;
    }
    return 0;

}

void CameraSubsystem::PrintTurn(int turn)
{
    double printturn = turn;
    double printX = center.x;
    frc::SmartDashboard::PutNumber("turn",printturn);
    frc::SmartDashboard::PutNumber("center of x",printX);
 
}


// This method will be called once per scheduler run
void CameraSubsystem::Periodic() {}
