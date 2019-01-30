#ifndef _TAB_DYN
#define _TAB_DYN
#include "Unite.h"
#include "ElementTD.h"

class TableauDynamique {
public:
    unsigned int capacite;
    unsigned int taille_utilisee;
    ElementTD * ad;

    /** TableauDynamique ()
        @brief Constructeur par defaut de tableau dynamique
    */
    TableauDynamique ();

    /** ~TableauDynamique ()
        @brief Destructeur de tableau dynamique
    */
    ~TableauDynamique ();

    /** void Vider ()
        @brief Vide le tableau et libere la memoire allouee dynamiquement
    */
	void Vider ();

    /** void AjouterElement (ElementTD e)
        @brief Ajoute l'element e dans le premier emplacement inutilise du tableau, double la capacite si necessaire
        @param (ElementTD e)
    */
    void AjouterElement (ElementTD e);

    /** void Afficher()const
        @brief Affiche les elements du tableau
    */
    void Afficher () const;

    /** void SupprimerElement (unsigned int indice)
        @brief Supprime l'element indique par l'indice, et decremente la taille utilisee du tableau de 1
        @param (unsigned int indice)
    */
    void SupprimerElement (unsigned int indice);

    /** ElementTD valeurIemeElement_Unite(unsigned int indice) const
        @brief Getter qui renvoie le i-eme element du tableau dynamique
        @param (unsigned int indice)
    */
    ElementTD valeurIemeElement_Unite(unsigned int indice) const;


    /** void TestRegression_TableauDynamique()
        @brief Test de regression du module TableauDynamique, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_TableauDynamique();

};

#endif
