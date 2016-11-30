#ifndef  INTERP4COMMAND_HH
#define  INTERP4COMMAND_HH

#include <iostream>
#include "DronPose.hh"
#include "Visualization.hh"
#include "Colision.hh"
#include "Scene.hh"
#include <cmath>
#include <unistd.h>



/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command ...
 */

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 *  Klasa modeluje abstrakcyjne polecenie dla robota mobilnego
 */
class Interp4Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    *  
    */
   virtual ~Interp4Command() {}
   /*!
    * \brief Wyświetla komendę oraz parametry
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief Wyswietla nazwy paramwetrów oraz jednostki
    */
   virtual void PrintSyntax() const = 0;
   /*!
    * \brief Zwraca nazwę komendy
    * \return zwraca nazwę komenty
    */
   virtual const char* GetCmdName() const = 0;
   /*!
    * \brief Wykonuje zadanie
    *  \param[in] pRobPose - pozycja drona w przestrzeni 3D
    *  \param[in] pVis - wizualizacja drona
    *
    * \retval true  - jesli wykonanie zadania zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
   virtual bool ExecCmd(  DronPose  *pRobPose,  Visualization *pVis ,Scene *scn ) const = 0;
   /*!
    * \brief Wczytuje parametry
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif
