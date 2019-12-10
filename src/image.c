/*!
\file image.c
\autor Jalbert Sylvain
\version 1
\date 02 decembre 2019
\brief le fichier qui contient les définitions de toutes les méthodes relatives aux manipulations d'image
*/
#include "image.h"

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
FILE *chargerFichier(char *tchar_nomFichier, char *droits){
  FILE *file_image; //l'image qui sera ouverte

  file_image = NULL;

  //ouverture de l'image avec les bon droits
  file_image = fopen(tchar_nomFichier, droits);
  if (file_image == NULL) {
		// Si pb alors on affiche un message
		printf("Problème d'ouverture du fichier (%s) : %s\n", tchar_nomFichier, strerror(errno));
		// et on quitte
		exit(ERREUR_SYS);
	}

  //retourner l'image chargé
  return(file_image);
}

/*!
\fn void enGris(FILE *file_imageEntree, FILE *file_imageSortie)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 09 decembre 2019
\brief la procedure qui convertie une image en couleur en image en gris
\param tchar_imageEntree le nom du de l'image d'entrée
\param tchar_imageSortie le nom du de l'image de sortie, qui condiendra le résultat
*/
void enGris(FILE *file_imageEntree, FILE *file_imageSortie){
  sPixel pixelCourant; //le pixel courant qui sera analyser
  int int_g; //le niveau de gris dans l'image
  char buffer[256];

  //copier les trois premieres lignes du fichier d'entrée dans le fichier de sortie
  fgets(buffer, sizeof(buffer), file_imageEntree);
  fprintf(file_imageSortie, "%s", buffer);
  fgets(buffer, sizeof(buffer), file_imageEntree);
  fprintf(file_imageSortie, "%s", buffer);
  fgets(buffer, sizeof(buffer), file_imageEntree);
  fprintf(file_imageSortie, "%s", buffer);

  //tant que le fichier d'entrée n'est pas arrivé à sa fin
  while(!feof(file_imageEntree)){
    //lecture du niveau de rouge vert et bleu du pixel courant
    fscanf(file_imageEntree, "%d\n%d\n%d\n", &pixelCourant.int_r, &pixelCourant.int_v, &pixelCourant.int_b);
    //calcul du niveau de gris
    int_g = 0.299*pixelCourant.int_r + 0.587*pixelCourant.int_v + 0.114*pixelCourant.int_b;
    //ecrire le résultat dans le fichier de sortie
    fprintf(file_imageSortie, "%d\n%d\n%d\n", int_g, int_g, int_g);
  }
}
