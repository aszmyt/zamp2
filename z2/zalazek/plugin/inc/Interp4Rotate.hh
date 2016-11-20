#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do obor wokol wlasnej osi
 *
 *  Klasa modeluje ...
 */
class Interp4Rotate: public Interp4Command {
  double  _Angle_rotation;    //(stopnie) kat obrotu
  double  _Angular_velocity;  //(stopnie na sekunde)predkosc katowa stopnie/sekunda
 public:
  /*!
   * \brief
   */
  Interp4Rotate();  
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
