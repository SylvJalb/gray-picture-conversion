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
  FILE *file_imageEntree; //le fichier qui sera traité en entrée
  FILE *file_imageSortie; //le fichier qui sera traité en entrée
  int int_i; //va parcourir tous les indices du tableau des arguments (argv)

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

  if((int_aDonneNomEntree && int_aDonneNomSortie) && (int_veutGris ^ int_veutNoirEtBlanc)){
    //CHARGER LE FICHIER D'ENTREE ET DE SORTIE
    file_imageEntree = chargerFichier(tchar_nomImageEntree, "r");
    file_imageSortie = chargerFichier(tchar_nomImageSortie, "w");
    if(int_veutGris){
      //executer la methode qui convertie l'image en gris
      enGris(file_imageEntree, file_imageSortie);
    }
    else{
      enNoirEtBlanc(file_imageEntree, file_imageSortie, int_seuil);
    }

    //FERMER LE FULX DES FICHIERS
    fclose(file_imageEntree);
    fclose(file_imageSortie);
  }
  //sinon, si aucune entrée ou aucune sortie n'a été donné
  else{
    //afficher un message pour expliquer comment utiliser le programme
    printf("Veuillez donner une entrée et une sortie\n\t-in ./chemain/de/l-image.ppm\n\t-out ./chemain/de/l-image.ppm\nEt un choix :\n\t-gris : si vous voulez transformer l'image en gris\n\t-seuil n : si vous voulez transformer l'image en noir et blanc (le seuil n doit est compris entre 0 et 255 compris)\n");
  }

  //Fin du programme, Il se termine normalement, et donc retourne 0
  return(0);
}
