#include <iostream>
#include "Interp4Rotate.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Angle_rotation(0), _Angular_velocity(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Angular_velocity  << " " << _Angle_rotation << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return "Rotate";
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
double d,pom;
d=pRobPose->GetAngle_deg(d);
	pRobPose->SetAngle_deg(_Angle_rotation);
	pom=_Angle_rotation/_Angular_velocity;
	usleep(pom*100000);


  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{

Strm_CmdsList>>_Angular_velocity>>_Angle_rotation;
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate   ang_speed[deg/s] ang[deg]" << endl;
}
