#include <iostream>
#include "Interp4Fly.hh"
#include <unistd.h>
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
  return Interp4Fly::CreateCmd();
}


/*!
 *
 */
Interp4Fly::Interp4Fly(): _hor_speed(0), _ver_speed(0), _dist(0)
{}


/*!
 *
 */
void Interp4Fly::PrintCmd() const
{
  cout << GetCmdName() << " " << _hor_speed  << " " << _ver_speed<< " " << _dist << endl;
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
bool Interp4Fly::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
double x,y,z,c,d;
	d=pRobPose->GetAngle_deg(d);
	c=sqrt(pow(_hor_speed,2)+pow(_ver_speed,2));
	c=_dist/c;
	//y=c*_hor_speed;
	z=c*_ver_speed;
	cout<<"d="<<d;
	if((d>0 && d<90) || (d>90 && d<180) || (d>180 && d<270) || (d>270 && d<360) ) 
	{
		y=sin(d)*_hor_speed;
		x=sin(d)*_hor_speed;
		pRobPose->SetPos_m(x,y,z); cout<<x<<" "<<y<<" "<<z<<" "<<endl; }
	else if(d==0 || d==180) { x=c*_hor_speed;
	pRobPose->SetPos_m(0,x,z);}
	else {y=c*_hor_speed; pRobPose->SetPos_m(y,0,z);}
  
  pVis->Draw(pRobPose);
  usleep(800000);  // Pauza 0,8 sek.
/*
  pRobPose->SetPos_m(100,50,50);
  pVis->Draw(pRobPose);
  usleep(800000);  // Pauza 0,3 sek.

  pRobPose->SetPos_m(50,50,50);
  pVis->Draw(pRobPose);
  usleep(800000);  // Pauza 0,8 sek. */
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}


/*!
 *
 */
bool Interp4Fly::ReadParams(std::istream& Strm_CmdsList)
{

Strm_CmdsList>>_hor_speed>>_ver_speed>>_dist;

  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
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
