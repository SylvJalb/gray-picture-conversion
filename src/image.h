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

/*! \def ERREUR_SYS
 *  Constante pour définir une terminaison par erreur
 *  système
 */
#define ERREUR_SYS -1

/*! \struct sPixel
 * Structure qui défini les nuances de couleurs primaires d'un pixel
 * \remark le taux de rouge vert et bleu varie entre 0 et 255 inclus
 */
typedef struct{
  int int_r; /*!< Taux de rouge */
  int int_v; /*!< Taux de vers */
  int int_b; /*!< Taux de bleu */
} sPixel;

/*
typedef struct{
  FILE* image;
} sImagePPM;

typedef struct{
  FILE* image;
} sImagePGM;

typedef struct{
  FILE* image;
} sImagePBM;
*/

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
\fn void enGris(FILE *file_imageEntree, FILE *file_imageSortie)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 09 decembre 2019
\brief la procedure qui convertie une image en couleur en image en gris
\param tchar_imageEntree le nom du de l'image d'entrée
\param tchar_imageSortie le nom du de l'image de sortie, qui condiendra le résultat
*/
void enGris(FILE *file_imageEntree, FILE *file_imageSortie);

#endif
