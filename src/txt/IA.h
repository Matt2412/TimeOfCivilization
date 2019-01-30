#ifndef _IA_H_INCLUDED
#define _IA_H_INCLUDED

#include <vector>
#include "Plateau.h"
#include "Civilization.h"
#include "TableauDynamique.h"

using namespace std;

/** @brief  La classe IA simule la reaction d'un joueur humain, en incarnant une civilisation a part entiere. Le joueur humain incarnant la civilisation 0,
            toutes les autres civilisations verront leurs actions dictees par une implacable Intelligence Artificielle, dont le cerveau se situe dans cette
            classe. Cette classe fonctionne en trois temps : Analyse, Decision et Action. Le programme analyse la situation dans laquelle il est confronte,
            puis agit en fonction en renvoyant une simple lettre au reste du programme.
*/


class IA
{
    private:
        vector<int> tabUnitesEnnemi_IA;//stocke toutes les positions relatives des unites ennemies
        vector<int> tabUnitesAlliees_IA;//stocke toutes les positions relatives des unites alliees
        int nbRandom_IA;//un nombre aleatoire qui est utilise lors de la prise de decision
        bool pretAssaut_IA;//sert a confirmer une attaque, si l'armee d'une IA est assez grande
        int positionUniteSelectionnee_IA;//la position relative de l'unite que l'IA va incarner
        int positionUniteSelectionneeX_IA;//la position X de l'unite que l'IA va incarner
        int positionUniteSelectionneeY_IA;//la position Y de l'unite que l'IA va incarner
        char decisionFinale_IA;//le fruit de toute la reflexion de l'IA

    public:

//////////////////////////////////////////FONCTIONS UTILITAIRES///////////////////////////////////////////////////////////////////


        /** IA()
            @brief  Constructeur par defaut : Initialise les donnees membres a une valeur exagerement elevee, de facon a ce que le programme soit
                        oblige de changer ces valeurs au cours de ses differents calculs.
        */
        IA();


        /** ~IA()
            @brief  Destructeur par defaut.
        */
        ~IA();


        /** TestRegression_IA()
            @brief Test de regression du module IA, teste toutes les fonctions membres et affiche les resultats.
        */
        void TestRegression_IA();


        /** char GetDecisionFinale_IA() const
            @brief Accesseur : Recupere la donnee membre "decisionFinale_IA", qui dictera l'action de l'unite dirigee par l'IA.
        */
        char GetDecisionFinale_IA() const;


        /** int Random_IA(int a, int b)const
            @brief Renvoie un nombre aleatoire compris entre les nombres a et b.
            @param (int a, int b)
        */
        int Random_IA(int a, int b)const;


        /** void AjouterUnitesEnnemies_IA(int ID_Civilization, Plateau * plateau)
            @brief Ajoute dans la donnee membre tabUnitesEnnemi_IA toutes les unites ennemies trouvees en parcourant le plateau
            @param (int ID_Civilization, Plateau * plateau)
        */
        void AjouterUnitesEnnemies_IA(int ID_Civilization, Plateau * plateau);


        /** void AjouterUnitesAlliees_IA(int ID_Civilization, Plateau * plateau)
            @brief Ajoute dans la donnee membre tabUnitesAlliees_IA toutes les unites alliees trouvees en parcourant le plateau
            @param (int ID_Civilization, Plateau * plateau)
        */
        void AjouterUnitesAlliees_IA(int ID_Civilization,  Plateau * plateau);


////////////////////////////////////////////////////PARTIE ANALYSE//////////////////////////////////////////////////////////////////


        /** int DetectionEnnemiLePlusProche_IA( Plateau * plateau_Jeu)const
            @brief Analyse : Renvoie la position litterale de l'ennemi le plus proche (qu'on calcule a partir des dimensions du plateau)
            @param (Plateau * plateau_Jeu)
        */
        int DetectionEnnemiLePlusProche_IA(Plateau * plateau_Jeu)const;


        /** bool DetectionDesAlliesProches_IA(int ID_Civilization, Plateau * plateau, const TableauDynamique & tabUnite,int uniteSelectionnee)const
            @brief Analyse : Sert a faire des "armees" en fonction des unites alliees environnantes. L'IA choisit entre lancer l'assault
                   si l'armee est assez grande, ou attendre l'arrivee d'autres unites.
            @param (int ID_Civilization, Plateau * plateau, const TableauDynamique & tabUnite, int uniteSelectionnee)
        */
        bool DetectionDesAlliesProches_IA(int ID_Civilization, Plateau * plateau)const;


        /** int DetectionVilleLaPlusProche_IA(int ID_Civilization,  Plateau * plateau,const TableauDynamique & tabUnite, int uniteSelectionnee)const
            @brief Analyse : Renvoie la position litterale de la ville alliee la plus proche (le colon s'en sert pour s'eloigner un minimum de la ville d'ou il vient)
            @param (int ID_Civilization, Plateau * plateau, const TableauDynamique & tabUnite, int uniteSelectionnee)
        */
        int DetectionVilleLaPlusProche_IA(int ID_Civilization,Plateau * plateau,const TableauDynamique & tabUnite, int uniteSelectionnee)const;


//////////////////////////////////////////////////////////////PARTIE DECISION///////////////////////////////////////////////////////////////////////////


        /** char DecisionVille_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,int age_Civilization,
                           int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite, int uniteSelectionnee)
            @brief Decision : Si l'unite choisie est une ville (le type de l'unite vaut 0), alors cette fonction aura le choix entre :
                    acheter des cases, produire des soldats, ou nourrir des colons.
            @param (int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,int age_Civilization,
                    int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee )
        */
        char DecisionVille_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,int age_Civilization,
                           int ID_Civilization,Plateau * plateau,  TableauDynamique & tabUnite, int uniteSelectionnee);


        /** char DecisionMelee_IA(int ID_Civilization,int age_Civilization,
                            Plateau * plateau, TableauDynamique & tabUnite_Civilization,int uniteSelectionnee )
            @brief Decision : Si l'unite choisie est une unite de melee (de type 2,4 ou 6), alors cette fonction indiquera a l'unite si elle doit
                    se deplacer/attaquer ou attendre des allies.
            @param (int ID_Civilization, int age_Civilization,
                           Plateau * plateau, TableauDynamique & tabUnite_Civilization,int uniteSelectionnee)
        */
        char DecisionMelee_IA(int ID_Civilization, int age_Civilization,
                           Plateau * plateau,TableauDynamique & tabUnite_Civilization,int uniteSelectionnee );


        /** char DecisionDistance_IA(int ID_Civilization, int age_Civilization,
                            Plateau * plateau,TableauDynamique & tabUnite_Civilization,int uniteSelectionnee  )
            @brief Decision : Si l'unite choisie est une unite de distance (de type 3,5 ou 7), alors cette fonction indiquera a l'unite si elle
                    doit se deplacer/attaquer ou attendre des allies.
            @param (int ID_Civilization,int age_Civilization,
                            Plateau * plateau,TableauDynamique & tabUnite_Civilization,int uniteSelectionnee)
        */
        char DecisionDistance_IA(int ID_Civilization,int age_Civilization,
                            Plateau * plateau,TableauDynamique & tabUnite_Civilization,int uniteSelectionnee);


        /** char DecisionBombe_IA(int ID_Civilization, Plateau * plateau,TableauDynamique & tabUnite, int uniteSelectionnee)
            @brief Decision : Si l'unite choisie est la bombe atomique (type 8), alors cette fonction indiquera a la bombe si elle est a portee
                    de tir d'une unite ennemie.
            @param (int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee )
        */
        char DecisionBombe_IA(int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee );


        /** void Decision_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,
                                  int age_Civilization,int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee )
            @brief Decision : C'est la super-fonction de la classe, celle qui gere tout en appelant toutes les autres en fonction du type d'unite selectionnee,
                    des ressources de la civilisation, etc...
            @param (int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,
                                  int age_Civilization, int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee)
        */
        void Decision_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,
                                  int age_Civilization,int ID_Civilization, Plateau * plateau, TableauDynamique & tabUnite,int uniteSelectionnee);


///////////////////////////////////////////////////////////PARTIE ACTIONS///////////////////////////////////////////////////////////////////////////


        /** char Bombardement_IA()const
            @brief Action : Enclenche le bombardement (renvoie la lettre B au reste du programme))
        */
        char Bombardement_IA()const;


        /** char Atomisation_IA()const
            @brief Action : Enclenche l'atomisation (renvoie la lettre N au reste du programme)
        */
        char Atomisation_IA()const;


        /** char Deplacement_IA(int ID_Civilization,int age_Civilization,
                                 Plateau * plateau,TableauDynamique & tabUnite, int uniteSelectionnee)
            @brief Action : Indique a l'unite selectionnee dans quelle direction aller, c'est-a-dire vers l'ennemi le plus proche. Pour les unites
                    a distance, en fonction de leur portee, indique si l'unite doit se deplacer ou attaquer a distance.
            @param (int ID_Civilization, int age_Civilization,
                     Plateau * plateau,TableauDynamique & tabUnite,int uniteSelectionnee)
        */
        char Deplacement_IA(int ID_Civilization, int age_Civilization,
                             Plateau * plateau,TableauDynamique & tabUnite, int uniteSelectionnee);


        /** char DeplacementSansEncombre(int ID_Civilization, Plateau * plateau_Jeu,  TableauDynamique & tabUnite_Civilization, int uniteSelectionnee,char decisionSansVerif)
            @brief Verifie qu'une unite ne sera pas genee par une autre unite lors d'un deplacement, si tel est le cas la fonction le detectera et indiquera une nouvelle direction (elle aussi
                   sans obstacle) pour l'unite.
            @param (int ID_Civilization,Plateau * plateau_Jeu, TableauDynamique & tabUnite_Civilization, int uniteSelectionnee, char decisionSansVerif)
        */
        char DeplacementSansEncombre(int ID_Civilization, Plateau * plateau_Jeu, TableauDynamique & tabUnite_Civilization, int uniteSelectionnee,char decisionSansVerif);


};


#endif  //_IA_H_INCLUDED
