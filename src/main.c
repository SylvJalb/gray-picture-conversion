/*!
\file main.c
\autor Jalbert Sylvain
\version 1
\date 29 novembre 2019
\brief fichier principal du programme qui permet à l'utilisateur de jouer au black jack
*/

#include "image.h"
#include "saisie.h"

/*!
\fn int main ( int argc, char∗∗ argv )
\author Jalbert Sylvain
\version 0.1 Premier jet
\date 29 novembre 2019
\brief la fonction principale qui permet à l'utilisateur de jouer au black jack
\param argc nombre d’arguments en entree
\param argv valeur des arguments en entree
\return 0 si tout c'est bien passé
*/
int main (int argc, char** argv){
  //DECLARATION DES VARIABLES
  char* tchar_nomImageEntree; //le nom de l'image à traiter
  char* tchar_nomImageSortie; //le nom de l'image qui sera enregisté
  int int_veutGris; //boolean qui dit si l'utilisateur veut son image en gris (1) ou non (0)
  int int_seuil; //le seuil a partir du quel on considère que c'est noir ou blanc
  int int_aDonneNomEntree; //boolean qui dit si l'utilisateur a donné le nom de l'image d'entrée
  int int_aDonneNomSortie; //boolean qui dit si l'utilisateur a donné le nom de l'image de sortie
  int int_veutNoirEtBlanc; //boolean qui dit si l'utilisateur veut son image en noir et blanc (1) ou non (0)
  int int_i; //va parcourir tous les indices du tableau des arguments (argv)
  sImagePBM *sImagePBM_imageNB; //une image PBM et donc en Noir et Blanc
  sImagePGM *sImagePGM_imageGris; //une image PGM et donc en Gris
  sImagePPM *sImagePPM_imageCouleur; //une image PPM et donc en couleur

  //INITIALISATION DES VARIABLES
  //On considère au début que l'utilisateur ne veut pas son image en gris
  int_veutGris = 0;
  //On considère au début que l'utilisateur ne veut pas son image en noir et blanc
  int_veutNoirEtBlanc = 0;
  //On considère au début que rien n'a été donné en arguments
  int_aDonneNomEntree = 0;
  int_aDonneNomSortie = 0;

  for(int_i = 1 ; int_i < argc ; int_i++){
    if(!strcmp(argv[int_i], "-in")){
      int_i++;
      if(int_i < argc){
        tchar_nomImageEntree = argv[int_i];
        int_aDonneNomEntree = 1;
      }
    }
    else{
      if(!strcmp(argv[int_i], "-out")){
        int_i++;
        if(int_i < argc){
          tchar_nomImageSortie = argv[int_i];
          int_aDonneNomSortie = 1;
        }
      }
      else{
        if(!strcmp(argv[int_i], "-gris")){
          int_veutGris = 1;
        }
        else{
          if(!strcmp(argv[int_i], "-seuil")){
            int_i++;
            if(int_i < argc){
              int_seuil = atoi(argv[int_i]);
              int_veutNoirEtBlanc = 1;
            }
          }
        }
      }
    }
  }

  //si l'utilisateur veut convertir l'image de couleur en gris et respecte les conditions
  if(int_aDonneNomEntree && int_aDonneNomSortie && int_veutGris &&
     tchar_nomImageEntree[strlen(tchar_nomImageEntree)-4] == '.' &&
     tchar_nomImageEntree[strlen(tchar_nomImageEntree)-3] == 'p' &&
     tchar_nomImageEntree[strlen(tchar_nomImageEntree)-2] == 'p' &&
     tchar_nomImageEntree[strlen(tchar_nomImageEntree)-1] == 'm' &&
     tchar_nomImageSortie[strlen(tchar_nomImageSortie)-4] == '.' &&
     tchar_nomImageSortie[strlen(tchar_nomImageSortie)-3] == 'p' &&
     tchar_nomImageSortie[strlen(tchar_nomImageSortie)-2] == 'g' &&
     tchar_nomImageSortie[strlen(tchar_nomImageSortie)-1] == 'm'){
    //avertir l'utilisateur du traitement qui sera effectué
    printf("\tMise de en gris de l'image en cour...\n");
    //charger l'image en couleur
    sImagePPM_imageCouleur = chargerImagePPM(tchar_nomImageEntree);
    //convertir l'image en gris
    sImagePGM_imageGris = enGris(sImagePPM_imageCouleur);

    //ENREGISTRER L'IMAGE
    enregistrerImagePGM(sImagePGM_imageGris, tchar_nomImageSortie);

    //LIBERER ESPACE MEMOIR ALOUEE
    free(sImagePPM_imageCouleur->tsPixel_pixels);
    free(sImagePPM_imageCouleur);
    free(sImagePGM_imageGris->tint_pixels);
    free(sImagePGM_imageGris);

    //avertir l'utilisateur que le traitement a été effectué
    printf("FAIT\n");
  }
  //sinon
  else{
    //si l'utilisateur veut convertir l'image grise en noir et blanc et a entrer les bons arguments
    if(int_aDonneNomEntree && int_aDonneNomSortie && int_veutNoirEtBlanc &&
       tchar_nomImageEntree[strlen(tchar_nomImageEntree)-4] == '.' &&
       tchar_nomImageEntree[strlen(tchar_nomImageEntree)-3] == 'p' &&
       tchar_nomImageEntree[strlen(tchar_nomImageEntree)-2] == 'g' &&
       tchar_nomImageEntree[strlen(tchar_nomImageEntree)-1] == 'm' &&
       tchar_nomImageSortie[strlen(tchar_nomImageSortie)-4] == '.' &&
       tchar_nomImageSortie[strlen(tchar_nomImageSortie)-3] == 'p' &&
       tchar_nomImageSortie[strlen(tchar_nomImageSortie)-2] == 'b' &&
       tchar_nomImageSortie[strlen(tchar_nomImageSortie)-1] == 'm'){
      //avertir l'utilisateur du traitement qui sera effectué
      printf("\tMise de en noir et blanc de l'image en cour...\n");
      //charger l'image grise
      sImagePGM_imageGris = chargerImagePGM(tchar_nomImageEntree);
      //convertir l'image en noir et blanc
      sImagePBM_imageNB = enNoirEtBlanc(sImagePGM_imageGris, int_seuil);

      //ENREGISTRER L'IMAGE
      enregistrerImagePBM(sImagePBM_imageNB, tchar_nomImageSortie);

      //LIBERER ESPACE MEMOIR ALOUEE
      free(sImagePBM_imageNB->tint_pixels);
      free(sImagePBM_imageNB);
      free(sImagePGM_imageGris->tint_pixels);
      free(sImagePGM_imageGris);

      //avertir l'utilisateur que le traitement a été effectué
      printf("FAIT\n");
    }
    //sinon, si l'utilisateur c'est trompé dans ses saisies
    else{
      //afficher un message pour expliquer comment utiliser le programme
      printf("Veuillez donner une entrée et une sortie\n\t-in X : chemain vers l'image à traiter (exemple : -in ./images/windows.ppm)\n\t-out X : chemain vers l'image résultat (exemple : -out ./images/windows.pgm)\nEt un choix :\n\t-gris : si vous voulez transformer l'image en gris\n\t\tSi cette option est choisie vous devez avoir un .ppm en entrée et un .pgm en sortie\n\t-seuil X : si vous voulez transformer l'image en noir et blanc (le seuil X doit est compris entre 0 et 255 compris)\n\t\tSi cette option est choisie vous devez avoir un .pgm en entrée et un .pbm en sortie\n\n");
    }
  }

  //Fin du programme, Il se termine normalement, et donc retourne 0
  return(0);
}
