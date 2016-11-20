#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <iomanip>
#include <list>
#include "Interp4Command.hh"
#include "GnuplotVisualizer.hh"
#include <map>
#include <fstream>
#include <sstream>

#define _MAX 99

using namespace std;


void menu(void)
{
  cout<<"w - wczytanie nazwy pliku sekwencji instrukcji dla drona"<<endl;
  cout<<"p - pokaz sekwencje instrukcji"<<endl;
  cout<<"i - pokaz dostepne instrukcje/wtyczki"<<endl;
  cout<<"s - start wykonywania sekwencji instrukcji"<<endl;
  cout<<"a - dodaj nowa wtyczke"<<endl;
  cout<<"d - usun wtyczke"<<endl;
  cout<<"? - wyswietl ponownie menu"<<endl<<endl;
  cout<<"k - koniec dzialania programu"<<endl;
}

void Del_plugins(void);
int Add_plugin(char const *);
void Del_plugin();


void *LibHandler[_MAX];

Interp4Command * pCmd[_MAX];


class ZarzadcaWtyczek {

public:
 map<string, Interp4Command*>_ZbWtyczek;
~ZarzadcaWtyczek(){}
};





ZarzadcaWtyczek wtyczki;

int plugins = 0;

int main()
{
	  DronPose            DPose;
  	  GnuplotVisualizer   PlotVis;
	  DPose.SetPos_m(0,0,0);
  	  PlotVis.Draw(&DPose);


  fstream file;
  char opcja;
  string plik,wtyczka,komenda,wyraz; 
 
  
    
  menu();
  while(opcja!='k'){
    cout<<"Twoj wybor (? - menu): ";
    cin>>opcja;
    
    switch( opcja )
      {
      case 'w':
	cout<<"Podaj nazwe pliku: ";
	cin>>plik;
	file.open(plik);
	if( file.good() == true)
	{
		cout<< " Uzyskano dostep do pliku!"<< endl;
	}
	else
		cout<< "brak dostepu do pliku" <<endl;
	break;  
      case 'p':
 	if(plugins==0)
	  cout<<"Brak wtyczek"<<endl;
	else
	  for(int i=0;i<plugins;i++){
	    pCmd[i]->PrintSyntax();
	    
	  }
	break;
      case 'i':
	if(plugins==0)
	  cout<<"Brak wtyczek"<<endl;
	else
	  for(int i=0;i<plugins;i++){
	    cout<<pCmd[i]->GetCmdName()<<endl;
	    
	  }
	break;
      case 's':
	{

	do
	{
		getline(file,wyraz);
		if(wyraz.length()!=0){
		istringstream st(wyraz);
		string wartosc;
		st>>wartosc;
			if(wtyczki._ZbWtyczek[wartosc]!=0){
			wtyczki._ZbWtyczek[wartosc]->ReadParams(st);
			wtyczki._ZbWtyczek[wartosc]->ExecCmd(&DPose,&PlotVis);
			wtyczki._ZbWtyczek[wartosc]->PrintCmd();
			}
			else {
			wtyczka="Interp4"+wartosc+".so";
			Add_plugin(wtyczka.c_str());
			wtyczki._ZbWtyczek[wartosc]->ReadParams(st);
			wtyczki._ZbWtyczek[wartosc]->ExecCmd(&DPose,&PlotVis);
			wtyczki._ZbWtyczek[wartosc]->PrintCmd();}
		}
	}while(!file.eof());
	}
	break;   
      case 'a':
	if(plugins>=_MAX){
	  cout<<"Za duzo wtyczek. Usun jakas wtyczke "<<endl;
	  break;
	}
	else{
	  cout<<"Podaj nazwe wtyczki: ";
	  cin>>wtyczka;
		if(wtyczki._ZbWtyczek[wtyczka]!=0)	
	      		cout<<"jest juz taka wtyczka"<<endl;
      		else
		{
		wtyczka="Interp4"+wtyczka+".so";
	 	 Add_plugin(wtyczka.c_str());
		}
	  break;
	}
      case 'd':
	if(plugins==0)
	  cout<<"Brak wtyczek"<<endl;
	else{
	  Del_plugin();
	}
	break; 
      case '?':
	menu();
	break; 
      case 'k':
	cout<<"\nKoniec dzialania programu"<<endl;
	break; 
      default:
	cout<<"Nie ma takiej opcji"<<endl;
	break;
      }
  }  

  Del_plugins();
}
int Add_plugin(char const * wtyczka){
  LibHandler[plugins] = dlopen(wtyczka,RTLD_LAZY);
  Interp4Command *(*pCreateCmd)(void);
  void *pFun;

  if (!LibHandler[plugins]) {
    cerr << "!!! Brak biblioteki: "<<wtyczka << endl;
    return 1;
  }

  pFun = dlsym(LibHandler[plugins],"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }

  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);  
  pCmd[plugins]=pCreateCmd();
  wtyczki._ZbWtyczek[pCmd[plugins]->GetCmdName()]= pCmd[plugins];
  plugins++;


  return 0;
}

void Del_plugin()
{
  delete pCmd[plugins-1];
  dlclose(LibHandler[plugins-1]);
  plugins--;
}

void Del_plugins(void){
  for(int i=0;i<plugins;i++){
    delete pCmd[i];
    dlclose(LibHandler[i]);
  }
 
}


