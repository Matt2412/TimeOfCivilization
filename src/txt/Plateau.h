#ifndef _PLAT_H_INCLUDED
#define _PLAT_H_INCLUDED

#include "Case.h"

/*! \brief La classe Plateau s'occupe de la carte, c'est a dire de l'ensemble des cases du plateau.
La taille horizontale et verticale du plateau est fixe respectivement a 40 et a 20 pour un nombre total
de cases de 800. Cette classe s'occupe de determiner le type de chaque case.*/
class Plateau
{
private:
    int tailleHorizontale_Plateau;
    int tailleVerticale_Plateau;
    int nbCase_Plateau;
    Case * tabCase_Plateau;

public:
    /** Plateau()
        Constructeur par defaut de la classe Plateau.
    */
    Plateau();

   /** Plateau(int tailleHorizontale_Plateau2,int tailleVerticale_Plateau2)
   @brief Constructeur par defaut de la classe: initialise la taille du plateau a 40*20.
   @param (int tailleHorizontale_Plateau2,int tailleVerticale_Plateau2)*/
    Plateau(int tailleHorizontale_Plateau2,int tailleVerticale_Plateau2);

   /*! \brief Case& GetCaseDeTabCase_Plateau(int k)
   Accesseur :recupere une case du plateau en fonction de son indice dans le tableau.
   @param (int k)*/
    Case& GetCaseDeTabCase_Plateau(int k);

   /*! \brief int gettailleHorizontale()
   Accesseur :recupere le parametre tailleHorizontale*/
    int gettailleHorizontale()const;

   /*! \brief int gettailleVerticale()
    Accesseur :recupere le parametre tailleVerticale*/
    int gettailleVerticale()const;

   /*! \brief int getNbCase()
    Accesseur :recupere le parametre NbCase*/
    int getNbCase()const;

   /*! \brief void settailleHorizontale(const int x)
   Mutateur : modifie le parametre tailleHorizontale
   @param (const int x)*/
    void settailleHorizontale(const int x);

   /*! \brief void settailleVerticale(const int x)
   Mutateur : modifie le parametre tailleVerticale
   @param (const int x)*/
    void settailleVerticale(const int x);

   /*! \brief void setNbCase (const int x)
   Mutateur : modifie le parametre NbCase
   @param (const int x)*/
    void setNbCase (const int x);

    //Autres fonctions/procédures utiles
   /** int TypeIemeCase_Plateau(int indice)
   @brief renvoie le type de la case d'indice "indice"
   @param (int indice)*/
    int TypeIemeCase_Plateau(const int indice) ;

  /*! \brief int XiemeCase_Plateau (const int indice)

   @param (const int indice)*/
    int XiemeCase_Plateau (const int indice);

   /*! \brief int YiemeCase_Plateau (const int indice);

   @param (const int indice)*/
    int YiemeCase_Plateau (const int indice);

   /*! \brief Case& GetCaseIDParCoordonnees_Plateau(int x, int y)
    Accesseur :recupere une case du plateau en fonction de ses coordonnees(x,y).
   @param (int x, int y)*/
    Case& GetCaseIDParCoordonnees_Plateau(const int x, const int y);


    /** TestRegression_Plateau()
        @brief Test de regression du module Plateau, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_Plateau();

   /*! \brief ~Plateau()
     Destructeur de la classe: desallocation de la memoire du tableau de cases*/
    ~Plateau();
};

#endif //PLAT_H_INCLUDED
