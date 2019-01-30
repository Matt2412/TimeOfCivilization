#ifndef _CIV_H_INCLUDED
#define _CIV_H_INCLUDED

#include "Unite.h"
#include "TableauDynamique.h"

/*! \brief La classe Civilisation gere les donnees des joueurs comme par exemple leurs ressources totales,
c'est a dire la somme des ressources de toutes leurs cases possedees. Chaque civilisation evolue
dans un age, c'est a dire une epoque(Antiquite, Renaissance, epoque moderne). La liste des unites(soldats
ou ville) est stocke dans un tableau dynamique pour pouvoir supprimer ou ajouter autant d'unites que necessaire
*/
class Civilization
{
private:

    bool enVie_Civilization;
    string nom_Civilization;
    int ID_Civilization;
    int or_Civilization,science_Civilization,nourriture_Civilization, production_Civilization;
    int age_Civilization;
    TableauDynamique tabUnite;

public:

    /*! Civilization()
        @brief Constructeur par defaut de Civilization
    */
    Civilization();

    /*! Unite* getUniteDeTabUnite(int k)const
        @brief  Renvoie une unite du tableau dynamique de la civilisation.
    */
    Unite* getUniteDeTabUnite(int k)const;

    //Getters
    /*! \brief bool getEnVie()
    Accesseur :recupere le parametre EnVie*/
    bool getEnVie()const;

/*! \brief string getNomCivilization()
    Accesseur :recupere le nom de la Civilisation*/
    string getNomCivilization()const;

    /*! \brief int getCivilizationID()
   Accesseur :recupere l'ID de la Civilisation*/
    int getCivilizationID()const;

    /*! \brief int getNourritureCivilization()
   Accesseur :recupere la ressource Nourriture de la Civilisation*/
    int getNourritureCivilization()const;

    /*! \brief  getscience_Civilization()
  Accesseur :recupere la ressource Science de la Civilisation*/
    int getscience_Civilization()const;

    /*! \brief int getOrCivilization()
   Accesseur :recupere la ressource Or de la Civilisation*/
    int getOrCivilization()const;

    /*! \brief int getProductionCivilization()
   Accesseur :recupere la ressource Production de la Civilisation*/
    int getProductionCivilization()const;

    /*! \brief int getage_Civilization()
   Accesseur :recupere l'age de la Civilisation*/
    int getage_Civilization()const;

    /*! \brief TableauDynamique & getTabUnite()
   Accesseur :recupere l'adresse du tableau dynamique d'unites*/
    TableauDynamique & getTabUnite();

    //Setters

    /*! \brief void setEnVie(const bool x)
   Mutateur : modifie le parametre EnVie
   @param (bool x)*/
    void setEnVie(const bool x);

    /*! \brief void setNomCivilization(const string x)
   Mutateur : modifie le nom de la Civilisation
   @param (const string x)*/
    void setNomCivilization(const string x);

    /*! \brief void setCivilizationID (const int x)
   Mutateur : modifie l'ID de la Civilisation
   @param (const int x)*/
    void setCivilizationID (const int x);

    /*! \brief  void setNourritureCivilization (const int x)
   Mutateur : modifie la ressource Nourriture de la Civilisation
   @param (const int x)*/
    void setNourritureCivilization (const int x);

    /*! \brief  void setOrCivilization (const int x)
   Mutateur : modifie la ressource Or de la Civilisation
   @param (const int x)*/
    void setOrCivilization (const int x);

    /*! \brief  void setProductionCivilization (const int x)
   Mutateur : modifie la ressource Production de la Civilisation
   @param (const int x)*/
    void setProductionCivilization (const int x);

   /*! \brief void setscienceCivilization(const int x)
   Mutateur : modifie la ressource Science de la Civilisation
   @param (const int x)*/
    void setscienceCivilization(const int x);

    /*! \brief void setage_Civilization (const int x)
   Mutateur : modifie l'age de la Civilisation
   @param (const int x)*/
    void setage_Civilization (const int x);

     /*! \brief void setTableauUnite (const int x)
   Mutateur : Permet de modifier les éléments du Tableau
   d'unites.
   @param (const TableauDynamique x)*/
    void setTableauUnite(const TableauDynamique x);

    //Autres fonctions/procédures utiles

   /*! \brief int DefinirVilleDepartX_Civilization()
   Renvoie une position aleatoire en x pour la ville de depart*/
    int DefinirVilleDepartX_Civilization();//Appelée par le constructeur de la civilisation pour définir la ville de départ en X!

    /*! \brief int DefinirVilleDepartX_Civilization()
   Renvoie une position aleatoire en x pour la ville de depart*/
    int DefinirVilleDepartY_Civilization();//Appelée par le constructeur de la civilisation pour définir la ville de départ en Y!

   /** \brief ~Civilization()
   Destructeur de la classe: desallocation de la memoire du tableau dynamique d'unite*/
    ~Civilization();

    /** void TestRegression_Civilization()
        @brief  Test de regression du module Civilization, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_Civilization();

};

#endif //_CIV_H_INCLUDED
