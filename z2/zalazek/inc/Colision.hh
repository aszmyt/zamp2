#ifndef COLISION_HH
#define COLISION_HH

#include "DronPose.hh"
#include <iostream>
#include "Scene.hh"
#include "Cuboid.hh"
#include "Wektor3D.hh"
#include <cmath>


#define DRONE_Z 10
#define DRONE_R 30

/*!
 * \file
 * \brief Definicja klasy Colision
 *
 * Plik zawiera definicję klasy Colision
 */

/*!
 * \brief Sprawdza czy nie nastąpiła kolizja.
 *
 *  Klasa zawiera informacje o przeszkodach na scenie oraz o aktualnym położeniu drona
 *  zapewnia sprawdzenie czy nastąpiła kolizja między tymi elementami.
 */

class Colision{
public:

/*!
   *  \brief Sprawdza czy nastąpiła kolizja
   *
   *  Algorytm testujący kolizje walca wraz z prostopadłościanem.
   *
   * \retval true  - jesli wystąpiła kolizja miedzy elementami
   * \retval false - jeśli nie wystąpiła
   *
   */ 
bool Coli(DronPose *Dpse, Scene *scn);
};


#endif
