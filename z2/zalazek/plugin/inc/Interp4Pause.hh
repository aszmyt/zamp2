#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause ...
 */

/*!
 * \brief Wstrzymuje działanie programu na okreslony czas
 *
 *  Klasa modeluje polecenie, które wstrzymuje działanie programu na okreslony czas
 */
class Interp4Pause: public Interp4Command {
   /*!
     * \brief czas oczekiwania w ms
     */	
  double  time;

 public:
  /*!
   * \brief konstruktor
   */
  Interp4Pause();  
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
