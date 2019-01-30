#ifndef _CASE_H_INCLUDED
#define _CASE_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include <vector>
#include <cmath>
#include <cassert>
#include <stdlib.h>
#include <stdlib.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h
using namespace std;

/*! \brief La classe Case contient toutes les ressources associees a chaque case du plateau comme la
nourriture ou la science. On definit aussi le type (Ocean/Terre). Elle est reference par ses coordonnees
dans le plateau. Chaque case a un proprietaire(-1 pour personne, 0 pour le joueur humain, 1 et plus pour les IAs.
A chaque tour, les cases produisent des ressources associees a leur type: Ocean -> science et nourriture,
Terre -> production et or. On fixe un prix d'achat de 10 ors pour chaque case.
*/

class Case
{
private:
    int x_Case; //coordonnée en abscisse de la case
    int y_Case;//coordonnée en ordonnée de la case
    int ID_Case;// Identifiant unique de la case
    int type_Case;//Quel type de case : Océan/Terre
    int proprioCase_Case;//Qui possède cette case? Joueur1(humain) ou autre joueur (joueur IA)
    int nourriture_Case;//Quel taux de nourriture produit-elle?
    int or_Case;//Quel taux d'or produit-elle?
    int science_Case;//Quel taux de science produit-elle?
    int production_Case;//Quel taux de "productivité" produit-elle?
    int prix_Case;
    int dejaOccupe_Case;//Est-elle libre d'accès ou déjà occupé par une unité


public:
   Case(); //Constructeur de la Case
/*! \brief Toutes les fonctions get... et set... sont respectivement des accesseurs et des mutateurs pour chaque
parametre de la classe. Ils sont passes en mode const.*/
    //Getters
    int getX()const;
    int getY()const;
    int getCaseID()const;
    int getTypeCase()const;
    int getProprioCase()const;
    int getOrParCase ()const;
    int getNourritureParCase ()const;
    int getScienceParCase ()const;
    int getProductionParCase ()const;
    int getPrixParCase()const;
    int getDejaOccupe ()const;


    //Setters
    void setX(const int k);
    void setY(const int k);
    void setCaseID(const int k);
    void setTypeCase(const int k);
    void setProprioCase(const int k);
    void setOrParCase (const int k);
    void setNourritureParCase(const int k);
    void setScienceParCase (const int k);
    void setProductionParCase (const int k);
    void setDejaOccupe (const int k);

    //Destructeur de la Case
    ~Case();


    //Test de regression de la Case
    /** void TestRegression_Case()
    @brief  Test de regression du module Case, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_Case();

};

#endif //_CASE_H_INCLUDED
