#ifndef MANAGER4PLUGINS_HH
#define MANAGER4PLUGINS_HH

#include <string>
#include "Wtyczka.hh"
#include "Interp4Command.hh"
#include "Colision.hh"
#include "Scene.hh"
#include <map>
#include <string>
#include <iostream>
#include <dlfcn.h>
#include <cassert>
/*!
 * \file
 * \brief Definicja klasy Manager4Plugins
 *
 * Plik zawiera definicję klasy Manager4Plugins
 */

/*!
 * \brief Zarządza wszystkimi wtyczkami wykorzystywanymi w programie.
 *
 *  Klasa zawiera informację o wtyczkach w programie.
 *  Ponadto udostępnia metody, które pozwalają wyszukiwać po kluczu wtyczki, dodawać nowe wtyczki i 
 *  usuwać istniejące, oraz pozwalają obsługiwać  opcje wtyczek.
 */
class Manager4Plugins{
   /*!
     * \brief Kontener asocjacyjny typu mapa przechowujący wtyczki.
     *
     * Przechowuje wtyczki w kontenerze typu mapa.
     */
  std::map<std::string,Wtyczka> _libDict;
public:
   /*!
    *  \brief Dodaje nową wtyczkę do programu
    *  \param[in] plugin - nazwa pliku z wtyczką dodania
    *
    * \retval true  - jesli dodawanie wtyczki zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool AddPlugin(char const * plugin);
   /*!
    *  \brief Usuwa wtyczkę w programu
    *  \param[in] plugin - nazwa komendy wtyczki do usunięcia
    *
    * \retval true  - jesli usuwanie wtyczki zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool DeletePlugin(std::string plugin);
/*!
 * \brief Usuwa wszystkie wtyczki .
 *
 */
  void DeletePlugins(void);
/*!
 * \brief Wyświetla komendy wszystkich wtyczek.
 *
 */
  void PrintPlugins(void);
   /*!
    *  \brief Zapisuje wczytane parametry z bufora wejściowego do odpowiedniej wtyczki.
    *  \param[in] Strm_CmdsList - bufor wejściowy
    *  \param[in] command - klucz opisujący własciwą wtyczkę
    *
    * \retval true  - jesli wczytanie parametrów zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool ReadParameters(std::istream& Strm_CmdsList,std::string command);
  /*!
    *  \brief Wyświetla wczytane parametry z bufora wejściowego .
    *  \param[in] command - klucz opisujący własciwą wtyczkę
    *
    * \retval true  - jesli wczytanie parametrów zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool PrintParameters(std::string command);
   /*!
    *  \brief Wykonuje zadanie dla danej wtyczki i wyświetla pozycję drona.
    *  \param[in] command - klucz opisujący własciwą wtyczkę
    *  \param[in] pRobPose - pozycja drona w układzie współrzędnych
    *  \param[in] pVis - wizualizacja pozycji drona	
    *
    * \retval true  - jesli wykonywanie zadania zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool ExecuteCommand(std::string command,DronPose *pRobPose, Visualization *pVis,Scene *scn);

};





#endif
