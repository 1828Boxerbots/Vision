/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CameraCMD.h"

CameraCMD::CameraCMD(CameraSubsystem* camera) : m_pcamera{camera}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(camera);
}

// Called when the command is initially scheduled.
void CameraCMD::Initialize()
{
  m_pcamera->InterlizeCamera(0);
}

// Called repeatedly when this Command is scheduled to run
void CameraCMD::Execute()
{
  m_pcamera->IntakeFrame();
  m_pcamera->FilterFrame();
  m_pcamera->CenterMomment();
  m_pcamera->PrintTurn(m_pcamera->WhereToTurn());
}

// Called once the command ends or is interrupted.
void CameraCMD::End(bool interrupted) {}

// Returns true when the command should end.
bool CameraCMD::IsFinished() { return false; }
