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

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "scene.hh"
#include "xmlparser4scene.hh"




#define _MAX 99

using namespace std;
using namespace xercesc;

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

/*!
Zarzadca wtyczek odpowiedzialny za magazynowanie informacji oraz wskaznikow do danej wtyczki
*/
class ZarzadcaWtyczek {

public:
  map<string, Interp4Command*>_ZbWtyczek;
  ~ZarzadcaWtyczek(){}
};

/*!
 * Czyta z pliku opis sceny i zapisuje stan sceny do parametru,
 * który ją reprezentuje.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param Scn - (\b we.) reprezentuje scenę, na której ma działać robot.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Scene& Scn)
{
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLParser4Scene(Scn);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
     
     if (!pParser->loadGrammar("grammar/scene.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/scene.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}






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
 

   Scene  Scn;

   if (!ReadFile("scene.xml",Scn)) return 1;

  
  /*! 
    Menu do realizacji pracy calego programu
   */    
  menu();
  while(opcja!='k'){
    cout<<"Twoj wybor (? - menu): ";
    cin>>opcja;
    
    switch( opcja )
      {
      case 'w':
	/*!
	  Funkcja wczytywania pliku do systemu
	  \li Zostaje sprawdzone czy plik zostal otwarty prawidlowo czy nie
	*/
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
	/*! 
	  Funkcja wyswietlajaca sekwencje instrukcji ktore sa obslugiwane przez program 
	*/
 	if(plugins==0)
	  cout<<"Brak wtyczek"<<endl;
	else
	  for(int i=0;i<plugins;i++){
	    pCmd[i]->PrintSyntax();
	    
	  }
	break;
      case 'i':
	/*!
	  Funkcja przedstawia nazwy wtyczek zawartych w programie
	*/
	if(plugins==0)
	  cout<<"Brak wtyczek"<<endl;
	else
	  for(int i=0;i<plugins;i++){
	    cout<<pCmd[i]->GetCmdName()<<endl;
	    
	  }
	break;
	/*!
	  Funkcja realizacji sekwencji:
	  \li program wyciaga linie z pliku ktory zostal otwarty wczesniej i wprowadza go do buffowa
	  \li z buffora zostaje wyciagniety pierwszy wyraz ktory sluzy jako informator dla zarzadcy, ktora wtyczne nalezy wybrac.
	  \li reszta bufforu zostaje przekierowana do odpowiedniej wtyczki aby wykonac sekwencje i zrealizowac ruch.
	  \li w przypadku gdy nie ma takiej wtyczki to autoamtycznie zostaje ona dodana oraz wykonana
	*/
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
	/*!
	  Funkcja odpowiedzialna za dodawanie wtyczke:
	  \li zarzadca sprawdza czy jest juz taka wtyczka wprowadzona do systemu i jesli wykaze ze jest to nie pozwala na ponowne jej wprowadzenie.
	  \li jesli zarzadca uzna ze wtyczki nie ma w systemie to inicjuje sekwencje dodawania.
	*/
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
	/*!
	  Funcja odpowiedzialna za usuwanie ostatniej dodanej wtyczki
	*/
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
/*!
Funkcja odpowiedzialna za dodawanie do systemu wtyczki
\li wtyczka jest wpisywana do zarzadcy, aby umozliwic pozniejsza identyfikacje znajdujacych sie w nim wtyczek
*/
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
/*!
Funkcja usuwa wszystkie wtyczki ktore zostaly wprowadzone do systemu,aby nie pozostawic zagubionych danych.
*/
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


