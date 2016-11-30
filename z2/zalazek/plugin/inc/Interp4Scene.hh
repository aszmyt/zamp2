#ifndef  COMMAND4SCENE_HH
#define  COMMAND4SCENE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Fly
 *
 * Plik zawiera definicję klasy Interp4Fly ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch horyzontalnie oraz wertykalnie
 *
 *  Klasa modeluje polecenie dla robota mobilnego, które wymusza jego ruch horyzontalnie oraz wertykalnie
 */
class Interp4Scene: public Interp4Command {
  /*!
   * \brief Nzwa pliku xml do odczytania
   *
   * Zmienna przechowuję nazwę pliku xml do odczytu
   */
  std::string xmlFileName;
 public:
  /*!
   * \brief konstruktor
   */
  Interp4Scene();  
  /*!
   * \brief Wyświetla komendę oraz parametry
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyswietla nazwy paramwetrów oraz jednostki
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Zwraca nazwę komendy
   */
  virtual const char* GetCmdName() const;
 /*!
    *  \brief Wykonuje zadanie dla danej wtyczki i wyświetla pozycję drona.  
    *  \param[in] pRobPose - pozycja drona w układzie współrzędnych
    *  \param[in] pVis - wizualizacja pozycji drona	
    *
    * \retval true  - jesli wykonywanie zadania zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  virtual bool ExecCmd( DronPose  *pRobPose,   Visualization *pVis,Scene *scn) const;
   /*!
    *  \brief Zapisuje wczytane parametry z bufora wejściowego do odpowiedniej wtyczki.
    *  \param[in] Strm_CmdsList - bufor wejściowy
    *
    * \retval true  - jesli wczytanie parametrów zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
