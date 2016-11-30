#ifndef WTYCZKA_HH
#define WTYCZKA_HH

#include "Interp4Command.hh"
/*!
 * \file
 * \brief Definicja klasy Wtyczka.hh
 *
 * Plik zawiera definicję klasy Wtyczka.hh ...
 */

/*!
 * \brief Zawiera informacjie niezbedne do obslugiwania wtyczek.
 *
 *  Klasa zawiera infromacje umożliwiajace wykorzystanie wtyczki.
 */
class Wtyczka{
public:
    /*!
     * \brief Wtyczka
     *
     * Wtyczka. Umożliwia korzystanie z wtyczki.
     */	    
  Interp4Command * _pInterp;
    /*!
     * \brief Uchwyt do wtyczki
     *
     * Uchwyt do wtyczki. Pozwla utowrzyć i zamknąć wtyczkę.
     */	
  void * _pLibHandler;
};

#endif
