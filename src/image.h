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
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "tableau.h"

/*! \def ERREUR_SYS
 *  Constante pour définir une terminaison par erreur
 *  système
 */
#define ERREUR_SYS -1


/*! \struct sImagePPM
 * Structure qui déclare une image .ppm
 */
typedef struct{
  int int_largeur; /*!< largeur de l'image en pixel */
  int int_longueur; /*!< longueur de l'image en pixel */
  int int_max; /*!< le maximum qu'une couleur peut prendre comme valeur */
  sPixel *tsPixel_pixels; /*!< Matrice de pixel de couleurs */
} sImagePPM;

/*! \struct sImagePGM
 * Structure qui déclare une image .pgm
 */
typedef struct{
  int int_largeur; /*!< largeur de l'image en pixel */
  int int_longueur; /*!< longueur de l'image en pixel */
  int int_max; /*!< le maximum qu'une couleur peut prendre comme valeur */
  int *tint_pixels; /*!< Matrice de pixel gris */
} sImagePGM;

/*! \struct sImagePBM
 * Structure qui déclare une image .pbm
 */
typedef struct{
  int int_largeur; /*!< largeur de l'image en pixel */
  int int_longueur; /*!< longueur de l'image en pixel */
  int int_max; /*!< le maximum qu'une couleur peut prendre comme valeur */
  int *tint_pixels; /*!< Matrice de pixel noir et blanc (boolean) */
} sImagePBM;

/*!
\fn FILE *chargerFichier(char *tchar_nomFichier, char *droits)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge un fichier avec les droits donné en parametre
\param tchar_nomFichier le nom du fichier à ouvrir
\param droits le ou les droits que l'on veut donner au programme sur le fichier
\return le pointeur vers le fichier ouvert
*/
FILE *chargerFichier(char *tchar_nomFichier, char *droits);

/*!
\fn sImagePPM *chargerImagePPM(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image PPM
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers la structure créé
*/
sImagePPM *chargerImagePPM(char *tchar_nomFichier);

/*!
\fn sImagePGM *chargerImagePGM(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image PGM
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers la structure créé
*/
sImagePGM *chargerImagePGM(char *tchar_nomFichier);

/*!
\fn sImagePGM *enGris(sImagePPM *sImagePPM_imageCouleur)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 09 decembre 2019
\brief la fonction qui convertie une image en couleur en image en gris
\param sImagePPM_imageCouleur l'image en couleur
\return l'image PGM (en gris)
*/
sImagePGM *enGris(sImagePPM *sImagePPM_imageCouleur);

/*!
\fn sImagePBM *enNoirEtBlanc(sImagePGM *sImagePGM_imageGrise, int int_seuil)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 09 decembre 2019
\brief la fonction qui convertie une image grise en noir et blanc grâce à un seuil donné
\param sImagePGM_imageGrise une image grise a convertir en noir et blanc
\param int_seuil le suil à partir du quel on dit que c'est un pixel blanc. En dessous c'est un pixel noir.
\return une image PBM
*/
sImagePBM *enNoirEtBlanc(sImagePGM *sImagePGM_imageGrise, int int_seuil);

/*!
\fn void enregistrerImagePGM(sImagePGM *sImagePGM_image, char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 13 decembre 2019
\brief la procedure qui enregistre une image grise PGM
\param sImagePGM_image l'image à enregistrer
\param tchar_nomFichier le nom du fichier à ouvrir
*/
void enregistrerImagePGM(sImagePGM *sImagePGM_image, char *tchar_nomFichier);

/*!
\fn void enregistrerImagePBM(sImagePBM *sImagePBM_image, char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 13 decembre 2019
\brief la procedure qui enregistre une image noire et blanche PBM (binaire)
\param sImagePBM_image l'image à enregistrer
\param tchar_nomFichier le nom du fichier à ouvrir
*/
void enregistrerImagePBM(sImagePBM *sImagePBM_image, char *tchar_nomFichier);

#endif
