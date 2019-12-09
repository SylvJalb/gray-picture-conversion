/*!
\file image.h
\autor Jalbert Sylvain
\version 1
\date 02 decembre 2019
\brief le fichier qui contient les déclarations de toutes les méthodes relatives aux manipulations d'image
*/

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <stdio.h>

/*! \def ERREUR_SYS
 *  Constante pour définir une terminaison par erreur
 *  système
 */
#define ERREUR_SYS -1

/*!
\fn FILE *chargerImage(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers le fichier ouvert
*/
FILE *chargerImage(char *tchar_nomFichier)

#endif
