#define LINE_LEN 100
#include<sstream>
#include<cstdlib>
#include<readline/readline.h>
#include<readline/history.h>

#include <iomanip>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <list>
#include "Interp4Command.hh"
#include "Manager4Plugins.hh"
#include "GnuplotVisualizer.hh"
#include "xmlparser4scene.hh"
#include "Wtyczka.hh"
#include "Scene.hh"
#include <sstream>
#include "Colision.hh"

using namespace std;


/*!
 * Wyświetla proste menu.
 *
 */
void menu(void)
{
  cout<<"w - wczytanie nazwy pliku sekwencji instrukcji dla drona"<<endl;
  cout<<"p - pokaz sekwencje instrukcji"<<endl;
  cout<<"i - pokaz dostepne instrukcje/wtyczki"<<endl;
  cout<<"s - start wykonywania sekwencji instrukcji"<<endl;
  cout<<"a - dodaj nowa wtyczke"<<endl;
  cout<<"d - usun wtyczke"<<endl;
  cout<<"? - wyswietl ponownie menu"<<endl;
  cout<<"\nk - koniec dzialania programu"<<endl;
}


/******************************************/
  /*!
    * 	Sczytuje z pliku zadania dla drona i wyswietla je
    *  \param[in] FileName - Nazwa pliku z zadaniami
    *  \param[in] slownik  - manger wtyczek
    *
    * \retval true  - jesli wczytanie parametrów zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
bool PrintCommands(string FileName,Manager4Plugins &slownik);
  /*!
    * 	Sczytuje z pliku zadania dla drona i wykonuje je
    *  \param[in] FileName - Nazwa pliku z zadaniami
    *  \param[in] slownik  - manger wtyczek
    *  \param[in] pRobPose - pozycja drona w przestrzeni 3D
    *  \param[in] pVis - wizualizacja drona
    *
    * \retval true  - jesli wczytanie parametrów zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
bool ExecCommands(string FileName,Manager4Plugins &slownik,DronPose *pRobPose		  ,Visualization *pVis,Scene *scn);



/*!
  * Główna funkcja programu. Obsługuje prosty interfejst i steruje programem.
  *
  */ 
int main()
{
  char opcja='?', *sLiniaPolecenia;
  const char *sZacheta ="Twoj wybor (? - menu): ";
  string plik,wtyczka,komenda; 
  Manager4Plugins slownik;
  DronPose            DPose;
  GnuplotVisualizer   PlotVis;
  istringstream StrmWe;
  Scene* scn;


 
  rl_bind_key('\t',rl_complete);
  DPose.SetPos_m(0,0,0);
 
  slownik.AddPlugin("Interp4Fly.so");
  slownik.AddPlugin("Interp4Rotate.so");
  slownik.AddPlugin("Interp4Turn.so");
  slownik.AddPlugin("Interp4Scene.so");
  slownik.AddPlugin("Interp4Pause.so");  
    
 
    do{
  
    
    switch( opcja )
      {
      case 'w':
	cout<<"Podaj nazwe pliku: ";
	cin>>plik;
scn=PlotVis.Wskaznik();

	break;  
      case 'p':
	if(!PrintCommands(plik,slownik))
	  cout<<"Blad przy probie odczytu pliku: "<<plik<<endl;
	break;
      case 'i':
	cout<<endl;
	slownik.PrintPlugins();
	cout<<endl;
  	
	break;
      case 's':
	if(!ExecCommands(plik,slownik,&DPose,&PlotVis,scn))
	  cout<<"Blad przy probie wykonania pliku: "<<plik<<endl;
	for (int i=1; i < 20; ++i) {
	  PlotVis.Draw(&DPose);
	  usleep(100000);  // Pauza 0,1 sek.
	}
	
	break;
      case 'a':
	  cout<<"Podaj nazwe wtyczki: ";
	  cin>>wtyczka;
	  slownik.AddPlugin(wtyczka.c_str());
	  break;
      case 'd':
	  cout<<"Podaj nazwe komendy do usuniecia: ";
	  cin>>komenda;
	  if(slownik.DeletePlugin(komenda))
	    cout<<"Pomyslnie usunieto wtyczke"<<endl;
	  else
	    cout<<"Nie ma takiej komendy"<<endl;
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
    sLiniaPolecenia = readline(sZacheta);
    if(!sLiniaPolecenia)return 0;
    add_history(sLiniaPolecenia);
    StrmWe.str(sLiniaPolecenia);
    free(sLiniaPolecenia);
    
    }  while(StrmWe>>opcja,opcja!='k');

  slownik.DeletePlugins();
  

}




bool PrintCommands(string FileName,Manager4Plugins & slownik){
  string f_comm_part = "cpp -P ";
  std::ostringstream ostr;
  std::istringstream istr;
  char line [LINE_LEN];
  string word;

  FILE *pFile = popen((f_comm_part+FileName).c_str(),"r");//otwieramy plik i uruchamiamy preprocesor
  
  
  
  while(fscanf(pFile,"%100s",line)==1){//zapisujemy dane do strumienia
    ostr<<line<<endl;
  }
  pclose(pFile);
  
  istr.str(ostr.str());  //przepisujemy strumienie
 

  istr>>word; 
        //sczytujemy rodzaj komendy i sprawdzamy czy wszystko OK
  while(!istr.eof()&&istr.good()){
 

 
    //sczytujemy rodzaj komendy
    if(!slownik.ReadParameters(istr,word)){
      return false;     
    }
    if(!slownik.PrintParameters(word)){//wyświetlamy zadania
      return false;
    }

    istr>>word;
  }
  
  return true;
}

bool ExecCommands(string FileName,Manager4Plugins &slownik,DronPose *pRobPose, Visualization *pVis,Scene *scn){
  string f_comm_part = "cpp -P ";
  std::ostringstream ostr;
  std::istringstream istr;
  char line [LINE_LEN];
  string word;
  Colision coli;
 
  FILE *pFile = popen((f_comm_part+FileName).c_str(),"r");//otwieramy plik i uruchamiamy preprocesor
  
  
  while(fscanf(pFile,"%100s",line)==1){ //zapisujemy dane do strumienia
    ostr<<line<<endl;
  }
  pclose(pFile);
  
  istr.str(ostr.str());  //przepisujemy strumienie
 

  istr>>word; 
        
  while(!istr.eof()&&istr.good()){ 

    //sczytujemy rodzaj komendy i sprawdzamy czy wszystko OK
    if(!slownik.ReadParameters(istr,word)){
      return false;     
    }
    if(!slownik.ExecuteCommand(word,pRobPose,pVis,scn)){  //wykonujemy zadanie
        return false;
    }
    if(coli.Coli(pRobPose,scn)==true) {cout<<endl<<"trafiono w przeszkode!!"<<endl; break;}//sprawdzamy czy trafiono w przeszkode
    istr>>word;
  }
  

  return true;
}


