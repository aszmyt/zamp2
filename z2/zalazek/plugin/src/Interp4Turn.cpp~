#include <iostream>
#include "Interp4Turn.hh"
#include <cmath>

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
  return Interp4Turn::CreateCmd();
}


/*!
 *
 */
 Interp4Turn::Interp4Turn(): _ang_speed(0), ang(0), radius(0)
{}


/*!
 *
 */
void Interp4Turn::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _ang_speed << " " << ang << " "<< radius<<endl;
}


/*!
 *
 */
const char* Interp4Turn::GetCmdName() const
{
  return "Turn";
}


/*!
 *
 */
bool Interp4Turn::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  double d,pom,angle;
	angle=ang*360/(2*M_PI*radius);
	pRobPose->SetAngle_deg(angle);
	pom=ang/_ang_speed;
	usleep(pom*100000);
	d=pRobPose->GetAngle_deg(d);
	cout<<endl<<d<<"  <-- d  "<<endl;

  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Turn::ReadParams(std::istream& Strm_CmdsList)
{
Strm_CmdsList>>_ang_speed>>ang>>radius;
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Turn::CreateCmd()
{
  return new Interp4Turn();
}


/*!
 *
 */
void Interp4Turn::PrintSyntax() const
{
  cout << "   Turn ang_speed[deg/s] ang[deg] radius[m" << endl;
}
