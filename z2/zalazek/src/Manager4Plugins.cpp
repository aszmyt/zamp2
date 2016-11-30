#include "Manager4Plugins.hh"
using std::cout;
using std::cerr;
using std::endl;
using std::cin;
using std::string;

bool Manager4Plugins::AddPlugin(char const * wtyczka){
  Wtyczka _wtyczka;
  //_wtyczka._pLibHandler = dlopen(wtyczka,RTLD_LAZY);
  _wtyczka._pLibHandler = dlopen(wtyczka,RTLD_LAZY);
  Interp4Command *(*pCreateCmd)(void);
  void *pFun;
  
  if (!_wtyczka._pLibHandler) {
    cerr << "!!! Brak biblioteki: "<<wtyczka << endl;
    return false;
  }

  pFun = dlsym(_wtyczka._pLibHandler,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return false;
  }
  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);  
  _wtyczka._pInterp=pCreateCmd();

  _libDict.insert (std::pair<string,Wtyczka>(_wtyczka._pInterp->GetCmdName(),_wtyczka) );
 
  return true;
}

bool Manager4Plugins::DeletePlugin(string wtyczka){
  std::map<string,Wtyczka>::iterator it;
  it=_libDict.find(wtyczka);
  if(it!=_libDict.end()){
    delete it->second._pInterp;
    dlclose(it->second._pLibHandler);
    _libDict.erase (it);
    return true;
  }
  return false;
}

void Manager4Plugins::DeletePlugins(void){
  std::map<string,Wtyczka>::iterator it;
  if(_libDict.empty())
    return;

  for (it=_libDict.begin(); it!=_libDict.end(); ++it){
    cout<<"Usunieto "<<it->first<<endl;
    delete it->second._pInterp;
    dlclose(it->second._pLibHandler);
    _libDict.erase (it);
  }
}
void Manager4Plugins::PrintPlugins(void){
  if(_libDict.empty()){
    cout<<"Brak wtyczek"<<endl;
    return;
  }  
  std::map<string,Wtyczka>::iterator it;
  for (it=_libDict.begin(); it!=_libDict.end(); ++it)
    it->second._pInterp->PrintSyntax();
}

bool Manager4Plugins::ReadParameters(std::istream& Strm_CmdsList,std::string command){
  std::map<string,Wtyczka>::iterator it;
  it=_libDict.find(command);
  if(it!=_libDict.end()){
 
    if(!(it->second._pInterp->ReadParams(Strm_CmdsList)))
      {         
	return false;
      }
  }
  else
    return false;
  return true;
}

bool Manager4Plugins::PrintParameters(std::string command){
  std::map<string,Wtyczka>::iterator it;
  it=_libDict.find(command);
  if(it!=_libDict.end()){ 
    it->second._pInterp->PrintCmd();
  }
  else
    return false;
  return true;
}


bool Manager4Plugins::ExecuteCommand(std::string command,DronPose *pRobPose, Visualization *pVis,Scene *scn){
  

  std::map<string,Wtyczka>::iterator it;
  it=_libDict.find(command);
  if(it!=_libDict.end()){ 
    if(!(it->second._pInterp->ExecCmd(pRobPose,pVis,scn)))
      return false;
  }
  else
    return false;
  

  return true;
}
