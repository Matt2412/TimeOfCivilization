#ifndef _UNIT_H_INCLUDED
#define _UNIT_H_INCLUDED

#include "Case.h"


/*! \brief La classe Unite gere toutes les caracteristiques d'une unite, comme par exemple les Points de Vie,
les Points d'Attaque,... Chaque unite possede un nom (exemple:"Hoplite"). Chaque Unite a une position reperee
par des coordonees x,y et a un proprietaire unique. Les fonctions d'attaque au corps a corps, d'attaque a distance,
de creation de ville, et de deplacement, situes dans la classe Jeu appellent les fonctions du meme nom de la classe Unite.
*/
class Unite
{
private:
    int PV_Unite, ATK_Unite, PM_Unite, DST_Unite, type_Unite, prix_Unite, ID_Unite, posX_Unite, posY_Unite, proprioUnite_Unite;
    string nom_Unite;

public:
    /** Unite()
        Constructeur par defaut de la classe Unite
    */
    Unite();

   /** \brief Unite(int type_Unite2, int ID_Unite2, int posX_Unite2, int posY_Unite2)
   Constructeur par defaut de la classe: initialise les PV, les ATK,... aux valeurs definies en fonction
   du type d'unite*/
    Unite(int type_Unite2, int ID_Unite2, int posX_Unite2, int posY_Unite2);//constructeur

 /** \brief ~Unite()
   Destructeur de la classe*/
    ~Unite();

    //Getters

 /*! \brief int getPV()
   Accesseur : recupere le parametre PV*/
    int getPV()const;

 /*! \brief int getATK()
   Accesseur : recupere le parametre ATK*/
    int getATK()const;

 /*! \brief int getPM()
   Accesseur : recupere le parametre PM*/
    int getPM()const;

 /*! \brief int getDST()
   Accesseur : recupere le parametre DST*/
    int getDST()const;

 /*! \brief int gettypeUnite()
   Accesseur : recupere le parametre typeUnite */
    int gettypeUnite()const;

 /*! \brief int getprix()
   Accesseur : recupere le parametre prix*/
    int getprix()const;

 /*! \brief int getuniteID()
   Accesseur : recupere le parametre ID*/
    int getuniteID()const;

 /*! \brief  int getposX()
   Accesseur : recupere le parametre posX*/
    int getposX()const;

 /*! \brief int getposY()
   Accesseur : recupere le parametre posY*/
    int getposY()const;

 /*! \brief int getproprioUnite()
   Accesseur : recupere le parametre proprioUnite*/
    int getproprioUnite()const;

 /*! \brief string getnomUnite()
   Accesseur : recupere le parametre nomUnite*/
    string getnomUnite()const;

    //Setters

 /*! \brief void setPV(const int x)
   Mutateur : modifie le parametre PV
   @param (const int x) */
    void setPV(const int x);

 /*! \brief void setATK(const int x)
   Mutateur : modifie le parametre ATK
   @param (const int x) */
    void setATK(const int x);

 /*! \brief  void setPM(const int x)
   Mutateur : modifie le parametre PM
   @param (const int x) */
    void setPM(const int x);

 /*! \brief setDST(const int x)
   Mutateur : modifie le parametre DST
   @param (const int x) */
    void setDST(const int x);

 /*! \brief settypeUnite(const int x)
   Mutateur : modifie le parametre typeUnite
   @param (const int x) */
    void settypeUnite(const int x);

 /*! \brief void setprix(const int x)
   Mutateur : modifie le parametre prix
   @param (const int x) */
    void setprix(const int x);

 /*! \brief void setuniteID(const int x)
   Mutateur : modifie le parametre ID
   @param (const int x)*/
    void setuniteID(const int x);

 /*! \brief  void setposX(const int x)
   Mutateur : modifie le parametre posX
   @param (const int x) */
    void setposX(const int x);

 /*! \brief  void setposY(const int x)
   Mutateur : modifie le parametre posY
   @param (const int x)*/
    void setposY(const int x);

 /*! \brief void setnomUnite(const string x)
   Mutateur : modifie le parametre nomUnite
   @param (const int x)*/
    void setnomUnite(const string x);

 /*! \brief void setproprioUnite (const int x)
   Mutateur : modifie le parametre proprioUnite
   @param (const int x)*/
    void setproprioUnite (const int x);



/*! \brief void Affronter_Unite(Unite* u_Adverse, Case c)

   @param (Unite* u_Adverse, Case c) */
    void Affronter_Unite(Unite* u_Adverse, Case c);

/*! \brief void Bombarder_Unite(Unite* u_Adverse, Case c)
   @param (Unite* u_Adverse, Case c) */
    void Bombarder_Unite(Unite* u_Adverse, Case c);

/*! \brief  void Fonder_Ville(char action)
   @param (char action) */
    void Fonder_Ville(char action);

    /**  void Atomiser_Unite(Unite * u_Adverse, Case c)
        @brief Atomise la zone auteur de la case c.
        @param (Unite * u_Adverse, Case c)
    */
    void Atomiser_Unite(Unite * u_Adverse, Case c);
    //void Acheter_Unite(char action, int x,int y, int ID_Civ); Fonction déplacée dans Jeu.h et Jeu.cpp

    /**  void Deplacer_Unite(char action,int taille_Horizontale,int taille_Verticale);
         @brief Permet de deplacer une unite en fonction de la direction voulue, apres verification.
         @param (char action,int taille_Horizontale,int taille_Verticale)
    */
    void Deplacer_Unite(char action,int taille_Horizontale,int taille_Verticale);

    /** void TestRegression_Unite();
        @brief Test de regression du module Unite, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_Unite();
};

#endif //_UNIT_H_INCLUDED
