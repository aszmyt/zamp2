#include <iostream>
#include "Interp4Scene.hh"

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
  return Interp4Scene::CreateCmd();
}


/*!
 *
 */
Interp4Scene::Interp4Scene()
{}


/*!
 *
 */
void Interp4Scene::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " <<xmlFileName<<endl;
}


/*!
 *
 */
const char* Interp4Scene::GetCmdName() const
{
  return "ReadScene";
}


/*!
 *
 */
bool Interp4Scene::ExecCmd( DronPose     *pRobPose,  Visualization *pVis,Scene *scn) const
{
  pVis->ReadScene(xmlFileName.c_str());
  
  for (int i=1; i < 20; ++i) {
    pVis->Draw(pRobPose);
    usleep(100000);  // Pauza 0,1 sek.
  }
 
  return true;
}
  

/*!
 *
 */
bool Interp4Scene::ReadParams(std::istream& Strm_CmdsList)
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
 
  return (Strm_CmdsList>>xmlFileName);
}


/*!
 *
 */
Interp4Command* Interp4Scene::CreateCmd()
{
  return new Interp4Scene();
}


/*!
 *
 */
void Interp4Scene::PrintSyntax() const
{
  cout << "   ReadScene  nazwa_pliku.xml" << endl;
}
