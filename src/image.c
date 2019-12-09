/*!
\file image.c
\autor Jalbert Sylvain
\version 1
\date 02 decembre 2019
\brief le fichier qui contient les définitions de toutes les méthodes relatives aux manipulations d'image
*/
#include "image.h"

/*!
\fn FILE *chargerImage(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers le fichier ouvert
*/
FILE *chargerImage(char *tchar_nomFichier){
  int int_retour; //ce que retourne la fonction d'ouverture de fichier
  FILE *file_image; //l'image qui sera ouverte

  //ouverture de l'image en ecriture / lecture
  file_image = fopen(tchar_nomFichier, "w+");
  if (pfil_fic == NULL) {
		// Si pb alors on affiche un message
		fprintf(file_image, "Problème d'ouverture du fichier : %s\n", strerror (errno));
		// et on quitte
		exit(ERREUR_SYS);
	}

  //retourner l'image chargé
  return(file_image);
}
