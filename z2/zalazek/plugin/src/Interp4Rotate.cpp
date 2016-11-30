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
bool Interp4Rotate::ExecCmd( DronPose     *pRobPose,  Visualization *pVis,Scene *scn) const
{
  if(_Angular_velocity == 0)
    return true;
  
  Wektor3D wsp;
  double kat,czas;
  kat=pRobPose->GetAngle_deg();
  czas=abs(_Angle_rotation/_Angular_velocity);


 
  if(_Angular_velocity<0&&_Angle_rotation<0)
    kat=kat-_Angle_rotation;
  else if(_Angular_velocity<0&&_Angle_rotation>=0)
    kat=kat-_Angle_rotation;
  else
    kat=kat+_Angle_rotation;

  

  pRobPose->SetAngle_deg(kat);



  usleep(czas*100000);
  pVis->Draw(pRobPose);  

  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return (Strm_CmdsList>>_Angular_velocity>>_Angle_rotation);
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
