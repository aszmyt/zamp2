#include "Colision.hh"

using namespace std;

bool Colision::Coli(DronPose *Dpose,Scene *scn)
{
Wektor3D center, size,pose,test;

scn->GetParameters(center,size,0);
pose=Dpose->GetPos_m();

test.x()=abs(pose.x()-center.x());
test.y()=abs(pose.y()-center.y());
test.z()=abs(pose.z()-center.z());

if(test.x() > (size.x()/2+DRONE_R)){return false;}
if(test.y() > (size.y()/2+DRONE_R)){return false;}

if(test.x() <= (size.x()/2)) {if(test.z() <= (size.z()/2)) {return true;}}
if(test.y() <= (size.y()/2)){if(test.z() <= (size.z()/2)){return true;}}


 return true;
}
