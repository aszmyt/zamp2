#include <iostream>
#include "Interp4Turn.hh"

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
 Interp4Turn::Interp4Turn(): speed(0), distance(0), radius(0)
{}


/*!
 *
 */
void Interp4Turn::PrintCmd() const
{
 
  cout << GetCmdName() << " " << speed << " " << distance << " "<< radius<<endl;
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
bool Interp4Turn::ExecCmd( DronPose     *pRobPose,  Visualization *pVis,Scene *scn) const
{
  Wektor3D wsp;
  double x,x_1,y_1,y,czas,czas_1,w;
  wsp=pRobPose->GetPos_m();
  
  x=wsp.x();
  y=wsp.y();
  

  czas = abs(distance/speed);
  czas_1 = abs((2*M_PI*radius-distance)/speed);
  w = abs(speed/radius);


   
  if(speed>=0){
    x_1=radius*cos(w*czas);
    y_1=radius*sin(w*czas);
    x+=x_1;
    y+=y_1;
    usleep(czas*100000);
  }
  else{
    x_1=radius*cos(w*czas_1);
    y_1=radius*sin(w*czas_1);
    x+=x_1;
    y+=y_1;
    usleep(czas*100000);
  } 
  pRobPose->SetPos_m(x,y,wsp.z());
  pVis->Draw(pRobPose);
  
  return true;
}


/*!
 *
 */
bool Interp4Turn::ReadParams(std::istream& Strm_CmdsList)
{
  return (Strm_CmdsList>>speed>>distance>>radius);
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
  cout << "   Turn speed[m/s] distance[m] radius[m]" << endl;
}
