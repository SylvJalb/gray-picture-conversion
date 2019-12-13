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
\fn sImagePPM *chargerImagePPM(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image PPM
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers la structure créé
*/
sImagePPM *chargerImagePPM(char *tchar_nomFichier){
  sImagePPM *sImagePPM_image; //l'image PPM a charger
  FILE *file_image; //le fichier qui sera ouvert
  int int_i; //parcours le tableau de pixel
  int int_resultat; //valeur retourner par le fscanf

  //INITIALISATION DES VARIABLES
  //alocation de la mémoir pour l'image
  sImagePPM_image = malloc(sizeof(sImagePPM));
  //on défini la largeur à -1 pour ensuite tester la lecture de la taille de l'image
  sImagePPM_image->int_largeur = -1;
  //on défini le max à -1 pour ensuite tester la lecture de la valeur max d'un pixel
  sImagePPM_image->int_max = -1;
  //le parcour du tableau de pixel commence à l'indice 0
  int_i = 0;
  //le resultat du fscanf est null au début
  int_resultat = 0;

  //OUVRIR LE FICHIER
  //ouverture de l'image avec les bon droits
  file_image = chargerFichier(tchar_nomFichier, "r");

  //INITIALISER sImagePPM_image
  //Lire le fichier jusqu'a trouver et définir la taille de l'image
  while(sImagePPM_image->int_largeur == -1 && int_resultat != EOF){
    int_resultat = fscanf(file_image, "%d %d", &(sImagePPM_image->int_largeur), &(sImagePPM_image->int_longueur));
    //passage à la ligne suivante
    while (fgetc(file_image) != '\n');
  }
  //si le la taille n'a pas été trouvé, le fichier est incorect
  if (sImagePPM_image->int_largeur == -1) {
		// Si pb alors on affiche un message
		printf("La taille de l'image n'est pas défini dans l'entête !\n");
    //FERMER LE FICHIER
    fclose(file_image);
		// et on quitte
		exit(ERREUR_SYS);
	}
  //creer le Tableau de pixel de taille longueur * largeur
  sImagePPM_image->tsPixel_pixels = creerTableauPixel(sImagePPM_image->int_longueur * sImagePPM_image->int_largeur);

  //Lire le fichier jusqu'a trouver et définir le maximum de valeur pouvant etre pris par un pixel
  while(sImagePPM_image->int_max == -1 && !feof(file_image)){
    fscanf(file_image, "%d", &(sImagePPM_image->int_max));
    //passage à la ligne suivante
    while (fgetc(file_image) != '\n');
  }
  //si la valeur max n'a pas été trouvé, le fichier est incorect
  if (sImagePPM_image->int_max == -1) {
		// Si pb alors on affiche un message
		printf("La valeur max n'est pas défini dans le fichier !\n");
    //FERMER LE FICHIER
    fclose(file_image);
		// et on quitte
		exit(ERREUR_SYS);
	}

  //COPIE DES PIXELS
  //tant que le fichier d'entrée n'est pas arrivé à sa fin
  while(!feof(file_image)){
    //si le numero de pixel dépase ou égale la taille
    if (int_i >= sImagePPM_image->int_longueur * sImagePPM_image->int_largeur) {
  		// affiche un message d'erreur
  		printf("La taille ne correspond pas au nombre de pixel défini dans le fichier !\n");
      //FERMER LE FICHIER
      fclose(file_image);
  		// et on quitte
  		exit(ERREUR_SYS);
  	}
    //lecture du niveau de rouge vert et bleu du pixel courant
    fscanf(file_image, "%d\n%d\n%d\n", &sImagePPM_image->tsPixel_pixels[int_i].int_r, &sImagePPM_image->tsPixel_pixels[int_i].int_v, &sImagePPM_image->tsPixel_pixels[int_i].int_b);
    //incrémenter le compteur pour le parcours du tableau de pixel.
    int_i++;
  }

  //FERMER LE FICHIER
  fclose(file_image);

  //retourner l'image chargé
  return(sImagePPM_image);
}

/*!
\fn sImagePGM *chargerImagePGM(char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 02 decembre 2019
\brief la fonction qui charge une image PGM
\param tchar_nomFichier le nom du fichier à ouvrir
\return le pointeur vers la structure créé
*/
sImagePGM *chargerImagePGM(char *tchar_nomFichier){
  sImagePGM *sImagePGM_image; //l'image PGM a charger
  FILE *file_image; //le fichier qui sera ouvert
  int int_i; //parcours le tableau de pixel

  //INITIALISATION DES VARIABLES
  //alocation de la mémoir pour l'image
  sImagePGM_image = malloc(sizeof(sImagePGM));
  //on défini la largeur à -1 pour ensuite tester la lecture de la taille de l'image
  sImagePGM_image->int_largeur = -1;
  //on défini le max à -1 pour ensuite tester la lecture de la valeur max d'un pixel
  sImagePGM_image->int_max = -1;
  //le parcour du tableau de pixel commence à l'indice 0
  int_i = 0;

  //OUVRIR LE FICHIER
  //ouverture de l'image avec les bon droits
  file_image = chargerFichier(tchar_nomFichier, "r");

  //INITIALISER sImagePPM_image
  //Lire le fichier jusqu'a trouver et définir la taille de l'image
  while(sImagePGM_image->int_largeur == -1 && !feof(file_image)){
    fscanf(file_image, "%d %d", &(sImagePGM_image->int_largeur), &(sImagePGM_image->int_longueur));
    //passage à la ligne suivante
    while (fgetc(file_image) != '\n');
  }
  //si le la taille n'a pas été trouvé, le fichier est incorect
  if (sImagePGM_image->int_largeur == -1) {
		// Si pb alors on affiche un message
		printf("La taille de l'image n'est pas défini dans l'entête !\n");
    //FERMER LE FICHIER
    fclose(file_image);
		// et on quitte
		exit(ERREUR_SYS);
	}
  //creer le Tableau de pixel de taille longueur * largeur
  sImagePGM_image->tint_pixels = creerTableauEntier(sImagePGM_image->int_longueur * sImagePGM_image->int_largeur);

  //Lire le fichier jusqu'a trouver et définir le maximum de valeur pouvant etre pris par un pixel
  while(sImagePGM_image->int_max == -1 && !feof(file_image)){
    fscanf(file_image, "%d\n", &(sImagePGM_image->int_max));
    //passage à la ligne suivante
    while (fgetc(file_image) != '\n');
  }
  //si la valeur max n'a pas été trouvé, le fichier est incorect
  if (sImagePGM_image->int_max == -1) {
		// Si pb alors on affiche un message
		printf("La valeur max n'est pas défini dans le fichier !\n");
    //FERMER LE FICHIER
    fclose(file_image);
		// et on quitte
		exit(ERREUR_SYS);
	}

  //COPIE DES PIXELS
  //tant que le fichier d'entrée n'est pas arrivé à sa fin
  while(!feof(file_image)){
    //si le numero de pixel dépase ou égale la taille
    if (int_i >= sImagePGM_image->int_longueur * sImagePGM_image->int_largeur) {
  		// affiche un message d'erreur
  		printf("La taille ne correspond pas au nombre de pixel défini dans le fichier !\n");
      //FERMER LE FICHIER
      fclose(file_image);
  		// et on quitte
  		exit(ERREUR_SYS);
  	}
    //lecture du niveau de rouge vert et bleu du pixel courant
    fscanf(file_image, "%d\n", &sImagePGM_image->tint_pixels[int_i]);
    //incrémenter le compteur pour le parcours du tableau de pixel.
    int_i++;
  }

  //FERMER LE FICHIER
  fclose(file_image);

  //retourner l'image chargé
  return(sImagePGM_image);
}

/*!
\fn sImagePGM *enGris(sImagePPM *sImagePPM_imageCouleur)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 09 decembre 2019
\brief la fonction qui convertie une image en couleur en image en gris
\param sImagePPM_imageCouleur l'image en couleur
\return l'image PGM (en gris)
*/
sImagePGM *enGris(sImagePPM *sImagePPM_imageCouleur){
  //DECLARATION DES VARIABLES
  sImagePGM *sImagePGM_imageGrise; //l'image grise créer (le résultat)
  int int_g; //le niveau de gris dans l'image
  int int_i; //va parcourirs le tableau de pixel

  //INITIALISATION DES VARIABLES
  //allocation en mémoire de l'image
  sImagePGM_imageGrise = malloc(sizeof(sImagePGM));
  //copier la taille et la valeur max de l'image couleur dans celle en gris
  sImagePGM_imageGrise->int_longueur = sImagePPM_imageCouleur->int_longueur;
  sImagePGM_imageGrise->int_largeur = sImagePPM_imageCouleur->int_largeur;
  sImagePGM_imageGrise->int_max = sImagePPM_imageCouleur->int_max;

  //creer le Tableau de pixel de taille longueur * largeur
  sImagePGM_imageGrise->tint_pixels = creerTableauEntier(sImagePGM_imageGrise->int_longueur * sImagePGM_imageGrise->int_largeur);

  /*parcours de tous le pixels de l'image en couleur,
    pour les traiter et définir les pixels de l'image grise*/
  for(int_i = 0 ; int_i < sImagePPM_imageCouleur->int_longueur * sImagePPM_imageCouleur->int_largeur ; int_i++){
    //calcul du niveau de gris
    int_g = 0.299*sImagePPM_imageCouleur->tsPixel_pixels[int_i].int_r
          + 0.587*sImagePPM_imageCouleur->tsPixel_pixels[int_i].int_v
          + 0.114*sImagePPM_imageCouleur->tsPixel_pixels[int_i].int_b;
    //ecrire le résultat dans le l'image grise
    sImagePGM_imageGrise->tint_pixels[int_i] = int_g;
  }

  //retourner l'image grise
  return(sImagePGM_imageGrise);
}

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
sImagePBM *enNoirEtBlanc(sImagePGM *sImagePGM_imageGrise, int int_seuil){
  //DECLARATION DES VARIABLES
  sImagePBM *sImagePBM_imageNB; //l'image Noire et Blanche a créer (le résultat)
  int int_i; //va parcourirs le tableau de pixel

  //INITIALISATION DES VARIABLES
  //allocation en mémoire de l'image
  sImagePBM_imageNB = malloc(sizeof(sImagePBM));
  //copier la taille et la valeur max de l'image couleur dans celle en gris
  sImagePBM_imageNB->int_longueur = sImagePGM_imageGrise->int_longueur;
  sImagePBM_imageNB->int_largeur = sImagePGM_imageGrise->int_largeur;
  sImagePBM_imageNB->int_max = sImagePGM_imageGrise->int_max;

  //creer le Tableau de pixel de taille longueur * largeur
  sImagePBM_imageNB->tint_pixels = creerTableauEntier(sImagePBM_imageNB->int_longueur * sImagePBM_imageNB->int_largeur);

  /*parcours de tous le pixels de l'image grise,
    pour les traiter et définir les pixels de l'image noire et blanche*/
  for(int_i = 0 ; int_i < sImagePGM_imageGrise->int_longueur * sImagePGM_imageGrise->int_largeur ; int_i++){
    //si le pixel courant de l'image grise est superieur au seuil
    if(sImagePGM_imageGrise->tint_pixels[int_i]>int_seuil){
      //le pixel courant de l'image en noir et blanc prend la valeur blanche soit 0
      sImagePBM_imageNB->tint_pixels[int_i] = 0;
    }
    //sinon, si le pixel courant de l'image grise est inferieur ou égal au seuil
    else{
      //le pixel courant de l'image en noir et blanc prend la valeur noir soit 1
      sImagePBM_imageNB->tint_pixels[int_i] = 1;
    }
  }

  //retourner l'image noire et blanche
  return(sImagePBM_imageNB);
}

/*!
\fn void enregistrerImagePGM(sImagePGM *sImagePGM_image, char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 13 decembre 2019
\brief la procedure qui enregistre une image grise PGM
\param sImagePGM_image l'image à enregistrer
\param tchar_nomFichier le nom du fichier à ouvrir
*/
void enregistrerImagePGM(sImagePGM *sImagePGM_image, char *tchar_nomFichier){
  FILE *file_image; //le fichier qui sera ouvert
  int int_i; //parcours le tableau de pixel

  //OUVRIR LE FICHIER
  //ouverture de l'image avec les droits d'ecriture
  file_image = chargerFichier(tchar_nomFichier, "w");

  //INITIALISER sImagePPM_image
  //Ecrire l'entête de l'image
  fprintf(file_image, "P2\n%d %d\n%d\n",sImagePGM_image->int_largeur, sImagePGM_image->int_longueur, sImagePGM_image->int_max);

  //ECRITURE DES PIXELS
  //parcours du tableau de pixel
  for(int_i = 0 ; int_i < sImagePGM_image->int_longueur * sImagePGM_image->int_largeur ; int_i++){
    //ecriture du pexel courant
    fprintf(file_image, "%d\n", sImagePGM_image->tint_pixels[int_i]);
  }

  //FERMER LE FICHIER
  fclose(file_image);
}

/*!
\fn void enregistrerImagePBM(sImagePBM *sImagePBM_image, char *tchar_nomFichier)
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 13 decembre 2019
\brief la procedure qui enregistre une image noire et blanche PBM (binaire)
\param sImagePBM_image l'image à enregistrer
\param tchar_nomFichier le nom du fichier à ouvrir
*/
void enregistrerImagePBM(sImagePBM *sImagePBM_image, char *tchar_nomFichier){
  FILE *file_image; //le fichier qui sera ouvert
  int int_i; //parcours le tableau de pixel

  //OUVRIR LE FICHIER
  //ouverture de l'image avec les droits d'ecriture
  file_image = chargerFichier(tchar_nomFichier, "w");

  //INITIALISER sImagePPM_image
  //Ecrire l'entête de l'image
  fprintf(file_image, "P1\n%d %d\n%d\n",sImagePBM_image->int_largeur, sImagePBM_image->int_longueur, sImagePBM_image->int_max);

  //ECRITURE DES PIXELS
  //parcours du tableau de pixel
  for(int_i = 0 ; int_i < sImagePBM_image->int_longueur * sImagePBM_image->int_largeur ; int_i++){
    //ecriture du pexel courant
    fprintf(file_image, "%d\n", sImagePBM_image->tint_pixels[int_i]);
  }

  //FERMER LE FICHIER
  fclose(file_image);
}
