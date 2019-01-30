#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


#include "Plateau.h"
#include "Civilization.h"
#include "IA.h"


/*! \brief La classe Jeu permet l'execution du programme en MODE TEXTE. En effet, cette classe gere les toures de jeu,
ajoute des joueurs au tableau des joueurs. Elle cree un plateau de 800 cases. C'est cette classe qui
execute les actions du joueur humain ou IA. Les ressources des participants sont augmentees a chaque tour
dans la classe Jeu.Le module Jeu s'occupe aussi de l'achat d'unites et de cases. Le bombardement
(ataque a distance) est effectue dans cette partie.*/


/*! \author BILLAUD Pierre / LEVEQUE Vincent / CHERRIER Matthieu
*/

class Jeu
{
private:
    bool finDePartie_Jeu;
    int tour_Jeu;
    string nomCiv_Jeu;
    Plateau *  plateau_Jeu;
    int nbCiv_Jeu;
    Civilization * tabCiv_Jeu;

public:

    Jeu();

   /** Jeu(int nbJoueur, string nomCiv_Jeu2)
   @brief Constructeur par defaut de la classe: initialise la fin de partie a false, le tour de jeu a 0,
   le plateau a un tableau de 800 cases
   @param (int nbJoueur, string nomCiv_Jeu2)*/
   Jeu(int nbJoueur, string nomCiv_Jeu2);

   /** \brief ~Jeu()
   Destructeur de la classe: desallocation de la memoire du plateau et du tableau de Civilisations*/
    ~Jeu();

   /*! \brief  void RetablirCaseNulle(int x)
   Retablit les cases possedees par le joueur x a leur etat d'origine s'il a perdu.
     @param (int x)*/
    void RetablirCaseNulle(int x);

   /*! \brief  void GestionTourTxt_Jeu()
   Execute les actions du joueur en fonction de ses choix(Choix humain ou choix automatique IA)
   */
    void GestionTourTxt_Jeu();

   /*! \brief  void RetablirPM_Jeu(TableauDynamique & tabUnite)
   Retablit les Points de Mouvement des Unites en debut de tour
     @param (TableauDynamique & tabUnite)*/
    void RetablirPM_Jeu(TableauDynamique & tabUnite);

   /*! \brief void DistribuerRessource_Jeu()
   Distribue les ressources(Or,Science, Production, Nourriture) en debut de tour
   */
    void DistribuerRessource_Jeu();

   /*! \brief  void Action_Jeu (Unite * u, WinTXT & win, Civilization & Civ)
    Choisit l'action en fonction d'un caractere
     @param (Unite * u, WinTXT & win, Civilization & Civ)*/
    void Action_Jeu (Unite * u, WinTXT & win, Civilization & Civ);//Produit l'action d'une unite ordonne par un char


    Civilization* getTabCiv_Jeu();

    /*! \brief  Unite* GetUniteParCoord_Jeu (int x, int y)
   Cherche une unité en fonction de ses coordonnées passées en paramètre
   @param (int x, int y)*/
    Unite* GetUniteParCoord_Jeu(int x, int y);

   /*! \brief  void VerificationUnitesMortes_Jeu ()
   Verifie en debut de tour les unites mortes lors d'un combat et les supprime du tableau.
   */
    void VerificationUnitesMortes_Jeu ();

   /*! \brief  void DefinirProprioUnite()
   Affecte un proprietaire a chaque unite du jeu en debut de tour*/
    void DefinirProprioUnite();

   /*! \brief  void DefinirCaseDejaOccupe(int x, int y)
   Change l'etat d'occupation  de la case en debut de tour
     @param (int x, int y)*/
    void DefinirCaseDejaOccupe(int x, int y);

   /*! \brief void DefinirTouteCaseDejaOccupe ()
   Aplique la fonction DefinirCaseDejaOccupe a toutes les cases du plateau. Si il n'y a personne sur la
   case alors elle reste innocupee */
    void DefinirTouteCaseDejaOccupe ();

   /*! \brief  void AttaqueUniteMelee_Jeu(int i, int j,Unite* u, char action,bool & ok)
    Execute l'attaque d'une unite de melee (attaque au corps a corps) et verifie si cela est possible
     @param (int i, int j,Unite* u, char action,bool & ok)*/
    void AttaqueUniteMelee_Jeu(int i, int j,Unite* u, char action,bool & ok);

   /*! \brief  void DeplacementUnite_Jeu(int i, int j,Unite* u,char action)
   Execute le deplacement d'unite de tout type et verifie si cela est possible
     @param (int i, int j,Unite* u,char action)*/
    void DeplacementUnite_Jeu(int i, int j,Unite* u,char action);

   /*! \brief void AttaqueUniteBombardement_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
   Execute l'attaque des unites de distance et verifie si cela est possible. Le soldat pointe vers
   un ennemi et l'attaque a distance.
     @param (int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)*/
    void AttaqueUniteBombardement_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine);

    void AttaqueUniteAtomisation_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine);

   /*! \brief void AffichTxt_Jeu(WinTXT & win, Unite * u, int mode, int positionOrigineX,int positionOrigineY)
     @param (WinTXT & win, Unite * u, int mode, int positionOrigineX,int positionOrigineY)*/
    void AffichTxt_Jeu(WinTXT & win, Unite * u, int mode, int positionOrigineX,int positionOrigineY);

   /*! \brief void Acheter_Unite_Jeu(char action2, int x,int y,  int ID_Civ)
   S'occupe de l'achat d'Unite lorsque c'est au tour d'une ville. Cette fonction verifie que le joueur
   a assez d'argent et si c'est le cas, ajoute la nouvelle unite au tableau de la bonne Civilisation.
     @param (char action2, int x,int y,  int ID_Civ)*/
    void Acheter_Unite_Jeu(char action2, int x,int y,  int ID_Civ);

   /*! \brief  void ActionIA_Jeu(Unite * u, WinTXT & win, Civilization & Civ, char actionParam)
   Effectue l'action automatique decidee par l'IA en fonction des positions ennemies du plateau
     @param (Unite * u, WinTXT & win, Civilization & Civ, char actionParam)*/
    void ActionIA_Jeu(Unite * u, WinTXT & win, Civilization & Civ, char actionParam);

   /*! \brief void VerificationActionIA_Jeu(char & reponse, int civSelectionnee, int uniteSelectionnee)
        Vérifie les actions de l'IA pour attribuer à chaque action de l'IA la bonne touche
     @param (char & reponse, int civSelectionnee, int uniteSelectionnee)*/
    void VerificationActionIA_Jeu(char & reponse, int civSelectionnee, int uniteSelectionnee);//Traite les cas non pris en compte dans la classe IA car trop compliqué + les étapes

   /*! \brief  void BombardementAutomatiqueIA(int civSelect, int uniteSelect)
   Cette fonction est execute seulement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void BombardementAutomatiqueIA(int civSelect, int uniteSelect);//qd on l'appelle le distance bombarde l'ennemi le plus proche

   /*! \brief void Acheter_Case_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
    Verifie que le joueur a assez de ressources pour acquerir la case selectionnee. Cette fonction passe
    la donnee proprioCase de -1 a 0 ou l'ID de la civilisation concernee.
     @param (int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)*/
    void Acheter_Case_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine);

   /*! \brief  void AchatCaseAutomatiqueIA (int civSelect, int uniteSelect)
    Cette fonction est executee uniquement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void AchatCaseAutomatiqueIA (int civSelect, int uniteSelect);

   /*! \brief void AtomisationAutomatiqueIA(int civSelect, int uniteSelect)
    Cette fonction est executee uniquement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void AtomisationAutomatiqueIA(int civSelect, int uniteSelect);

   /*! \brief void AugmentationAge_Jeu()
   Augmente l'age de la Civilisation si le joueur a atteint le niveau de science requis pour passer
   a l'ere superieure*/
    void AugmentationAge_Jeu();
};

#endif // JEU_H_INCLUDED
