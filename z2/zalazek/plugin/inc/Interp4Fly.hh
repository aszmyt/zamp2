#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

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
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Fly: public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  double  _hor_speed;
  double  _ver_speed;
  double  _dist;
 public:
  /*!
   * \brief
   */
  Interp4Fly();  
  /*!
   * \brief
   */
  virtual void PrintCmd() const;
  /*!
   * \brief
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief
   */
  virtual bool ExecCmd( DronPose  *pRobPose,   Visualization *pVis) const;
  /*!
   * \brief
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
