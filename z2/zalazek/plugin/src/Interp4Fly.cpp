#include <iostream>
#include "Interp4Fly.hh"

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
  return Interp4Fly::CreateCmd();
}


/*!
 *
 */
Interp4Fly::Interp4Fly(): _Speed_mpS(0),_verSpeed_mpS(0),_distance_m(0)
{}


/*!
 *
 */
void Interp4Fly::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed_mpS  << " " << _verSpeed_mpS << " " <<_distance_m<< endl;
}


/*!
 *
 */
const char* Interp4Fly::GetCmdName() const
{
  return "Fly";
}


/*!
 *
 */
bool Interp4Fly::ExecCmd( DronPose     *pRobPose,  Visualization *pVis,Scene *scn) const
{
  //nie wykonujemy zadnego ruchu
  if(_Speed_mpS==0 && _verSpeed_mpS==0)
    return true;
  
  double kat,x,x_1,y_1,y,z,czas,predkosc;
  kat=pRobPose->GetAngle_deg();
  


  //predkosc jest wypadkowa v_ver. i v_hor.
  predkosc=sqrt(pow(_Speed_mpS,2)+pow(_verSpeed_mpS,2));
  czas = _distance_m/predkosc;
  y_1=cos(kat*(M_PI/180))*(_Speed_mpS*czas);
  x_1=sin(kat*(M_PI/180))*(_Speed_mpS*czas);
  //obliczamy nowe wspolzedne
  z=_verSpeed_mpS*czas;
  x=x_1;
  y=y_1;

  for(int i=0;i<20;i++){
  pRobPose->SetPos_m(x/20,y/20,z/20);
  pVis->Draw(pRobPose);
  usleep(czas*100000/10);
}
  usleep(czas*100000);
  

  return true;
}


/*!
 *
 */
bool Interp4Fly::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
 
  return (Strm_CmdsList>>_Speed_mpS>>_verSpeed_mpS>>_distance_m);
}


/*!
 *
 */
Interp4Command* Interp4Fly::CreateCmd()
{
  return new Interp4Fly();
}


/*!
 *
 */
void Interp4Fly::PrintSyntax() const
{
  cout << "   Fly  hor_speed[m/s]  ver_speed[m/s]  dist[m]" << endl;
}
