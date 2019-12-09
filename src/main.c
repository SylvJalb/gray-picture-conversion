/*!
\file main.c
\autor Jalbert Sylvain
\version 1
\date 29 novembre 2019
\brief fichier principal du programme qui permet à l'utilisateur de jouer au black jack
*/

#include "image.h"

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
  int int_estGris; //boolean qui dit si l'image d'entrée est grise (1) ou non (0)
  int int_seuil; //le seuil a partir du quel on considère que c'est noir ou blanc
  int int_aDonneNomEntree; //boolean qui dit si l'utilisateur a donné le nom de l'image d'entrée
  int int_aDonneNomSortie; //boolean qui dit si l'utilisateur a donné le nom de l'image de sortie
  int int_aDonneSeuil; //boolean qui dit si l'utilisateur a donné le nom de l'image de sortie

  //INITIALISATION DES VARIABLES
  //On considère au début que l'image est en couleur
  int_estGris = 0;
  //On considère au début que rien n'a été donné en arguments
  int_aDonneNomEntree = 0;
  int_aDonneNomSortie = 0;
  int_aDonneSeuil = 0;


  for(int_i ; int_i < argc ; int_i++){
    if(strcmp(argv[int_i], "-in")){
      int_i++;
      if(int_i < argc){
        tchar_nomImageEntree = argv[int_i];
        int_aDonneNomEntree = 1;
      }
    }
    else{
      if(strcmp(argv[int_i], "-out")){
        int_i++;
        if(int_i < argc){
          tchar_nomImageSortie = argv[int_i];
          int_aDonneNomSortie = 1;
        }
      }
      else{
        if(strcmp(argv[int_i], "-gris")){
          int_estGris = 1;
        }
        else{
          if(strcmp(argv[int_i], "-seuil")){
            int_i++;
            if(int_i < argc){
              int_seuil = argv[int_i];
              int_aDonneSeuil = 1;
            }
          }
        }
      }
    }
  }

  //INITIALISATION DE L'ECRAN
  system("clear");

  //Fin du programme, Il se termine normalement, et donc retourne 0
  return(0);
}
