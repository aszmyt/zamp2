#include "Scene.hh"


using namespace std;



int Scene::SizeOfScene(void){
  return _obstacles.size();
}

void Scene::RemoveAllObstacles(void){
  
  _obstacles.clear();

}

Scene::~Scene(){
  cout<<"Usuwam scene.."<<endl;
}

bool Scene::AddObstacle(Cuboid obst){
  Wektor3D center,size;

Cuboid tmp;
tmp.SetSize(obst.GetSize());
tmp.SetCenter(obst.GetCenter());
_obstacles.push_back(tmp);

  return true;
  
}

bool Scene::GetParameters(Wektor3D &Center,Wektor3D &Size,int Ind){
  if(Ind<0 || Ind>=SizeOfScene())
    return false;

  Center=(_obstacles[Ind].GetCenter());
  Size=(_obstacles[Ind].GetSize());


  return true;

}

  
