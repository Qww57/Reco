/**
 * \file parametrage.h
 * \brief paramètrage de la détection des couleurs
 * \author Quentin.T
 * \version 0.1
 * \date 11 janvier 2015
 *
 * Partie ayant pour but de paramètrer la détection des couleurs par la webcam.
 * Un paramètrage par défaut est prévu.
 *
 */

#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include "structures.h"

extern jeuCouleurs pardefaut;
extern jeuCouleurs _calibrage;

jeuCouleurs defaut();
jeuCouleurs parametrage();

#endif // PARAMETRAGE_H
