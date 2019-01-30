#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "src/txt/Jeu.h"
#include "src/graphique/Jeu_graphique.h"
#include "src/txt/Plateau.h"
#include "src/txt/Civilization.h"
#include "src/txt/Unite.h"
#include "src/txt/TableauDynamique.h"
#include "src/txt/ElementTD.h"
#include "src/txt/Case.h"
using namespace std;

void initialisationAleatoire ()
{
    srand(time(NULL)); // initialisation de rand

}

int main()
{
    initialisationAleatoire();//Ne se lance qu'une fois pour tout le programme
    cout<<"Bonjour, bienvenue sur Time Of Civilization."<<endl;
    cout<<"Entrez le nombre de joueurs (2 minimum): ";
    int nbCiv_Jeu=0;
    while (nbCiv_Jeu<2){cin>>nbCiv_Jeu;}
    cout<<"Entrez maintenant le nom de votre civilisation : ";
    string nomCiv_Jeu;
    cin>>nomCiv_Jeu;

    Jeu jeu(nbCiv_Jeu,nomCiv_Jeu);
    jeu.GestionTourTxt_Jeu();

    return 0;
}
