#include <iostream>
#include "Interp4Pause.hh"

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
  return Interp4Pause::CreateCmd();
}


/*!
 *
 */
Interp4Pause::Interp4Pause(): time(0)
{}


/*!
 *
 */
void Interp4Pause::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " <<time<<endl;
}


/*!
 *
 */
const char* Interp4Pause::GetCmdName() const
{
  return "Pause";
}


/*!
 *
 */
bool Interp4Pause::ExecCmd( DronPose     *pRobPose,  Visualization *pVis,Scene *scn) const
{
  
  usleep(time*100);
 

  return true;
}
  

/*!
 *
 */
bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
 
  return (Strm_CmdsList>>time);
}


/*!
 *
 */
Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


/*!
 *
 */
void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause  time[ms]" << endl;
}
