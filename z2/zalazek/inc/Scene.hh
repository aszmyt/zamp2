#ifndef SCENE_HH
#define SCENE_HH

#include "Cuboid.hh"
#include <vector>
#include "Wektor3D.hh"
#include <iostream>
#include "DronPose.hh"

/*!
 * \file
 * \brief Definicja klasy Scena
 *
 * Plik zawiera definicję klasy Scena
 */

/*!
 * \brief Przechowuje informację o położeniu przeszkód na scenie
 *
 *  Klasa zawiera informację o przeszkodach na scenie.
 *  Umożliwia dodawanie nowych przeszkód, usuwanie starych oraz udostępnia informacje o przeszkodzie (położenie). 
 */

class Scene{
private:
  /*!
   * \brief Kontener vector - dynamiczna tablica, przechowująca przeszkody
   *
   * Przechowuje i udostępnia przeszkody zapisane w tablicy
   */
  std::vector<Cuboid> _obstacles;
public:
  /*!
   * \brief Destruktor  dla poprawnej destrukcji obiektu
   *
   * Usunie wszystkie elementy dyamicznew tablicy
   */
  ~Scene();
  /*!
   *  \brief Dodaje nową przeszkodę do sceny
   *
   *  Dodaje nowy obiekt do kontenera typu vector
   *  \param[in] obst - przeszkoda, kóra dodana zostanie do sceny
   *
   * \retval true  - jesli dodawanie przeszkody zakończyło się powodzeniem,
   * \retval false - w przypadku przeciwnym.
   *
   */ 
  bool AddObstacle(Cuboid obst);
  /*!
   *  \brief Usuwa wszystkie przeszkody ze sceny
   *
   *  Usunie przeszkody i zwolni zalokowaną pamięć.
   */ 
  void RemoveAllObstacles(void);
  /*!
   *  \brief Zwraca liczę przeszkód na scenie
   *
   *  Zwraca liczbę elementów zapisanych w tablicy 
   * \return liczba przeszkód
   */
  int SizeOfScene(void);
  /*!
   *  \brief Zapisuje do argumentów parametry przeszkody
   *
   *  Zapisuje do podanych parametów danezapisanew przeszkodzie
   *  \param[out] Center - położenie przeszkody w przestrzeni
   *  \param[out] Size - rozmiar przeszkody
   *  \param[in]  Ind - indeks przeszkody w tablicy
   *
   * \retval true  - jesli przepisywanie danych zakończyło się powodzeniem,
   * \retval false - w przypadku przeciwnym.
   *
   */  
  bool GetParameters(Wektor3D &Center,Wektor3D &Size,int Ind);

 


};



#endif
