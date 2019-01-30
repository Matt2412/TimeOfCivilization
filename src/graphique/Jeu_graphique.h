#ifndef JEUGRAPHIQUE_H_INCLUDED
#define JEUGRAPHIQUE_H_INCLUDED

#include "../txt/Plateau.h"
#include "../txt/Civilization.h"
#include "../txt/IA.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

/*! \brief La classe Jeu_graphique permet l'execution du programme en MODE GRAPHIQUE. En effet, cette classe gere les tours de jeu,
ajoute des joueurs au tableau des joueurs. Elle creee un plateau de 800 cases. C'est cette classe qui
execute les actions du joueur humain ou IA. Les ressources des participants sont augmentees a chaque tour
dans la classe Jeu.Le module Jeu s'occupe aussi de l'achat d'unites et de cases. Le bombardement
(attaque a distance) est effectue dans cette partie.*/

/*! \author BILLAUD Pierre / LEVEQUE Vincent / CHERRIER Matthieu
*/

class Jeu_graphique
{
private:
    bool finDePartie_JeuGraphique;
    int tour_JeuGraphique;
    string nomCiv_JeuGraphique;
    Plateau *  plateau_JeuGraphique;
    int nbCiv_JeuGraphique;
    Civilization * tabCiv_JeuGraphique;

    //PARTIE GRAPHIQUE :
    /*Ressources liées principalement au chargement de textures, sprites, fonts,
     issus du dossier data et à leur utilisation*/

    //VUE
    int VueX;
    int VueY;

    //Texte
    sf::Text text,text1,text2,text3,text4,text5,text6,text7,text8,textAchatC,textAchatUAgeI,textAchatUAgeII,textAchatUAgeIII,textModeB,valeurNouriture,valeurScience,valeurProd,valeurOr,valeurTour,
    PM_PV;
    sf::Font font;
    sf::Font font2;

    //Textures

    sf::Texture texture;
    sf::Texture textureLogo;
    sf::Texture texturePartieRap;
    sf::Texture texturePartiePerso;
    sf::Texture textureOcean;
    sf::Texture textureTerre;
    sf::Texture textureVilleAmi;
    sf::Texture textureVilleEnnemi;
    sf::Texture CasePossedeeAmi;
    sf::Texture CasePossedeeEnnemi;

    sf::Texture textureChar;
    sf::Texture textureHoplite;
    sf::Texture textureArcher;
    sf::Texture textureCanon;
    sf::Texture textureHussard;
    sf::Texture textureColon;
    sf::Texture textureLM;
    sf::Texture textureBombeAmi;

    sf::Texture textureCharE;
    sf::Texture textureHopliteE;
    sf::Texture textureArcherE;
    sf::Texture textureCanonE;
    sf::Texture textureHussardE;
    sf::Texture textureColonE;
    sf::Texture textureLME;
    sf::Texture textureBombeE;

    sf::Texture textureOr;
    sf::Texture textureNourriture;
    sf::Texture textureProd;

    sf::Texture textureScience;
    sf::Texture textureScienceAge2;
    sf::Texture textureScienceAge3;

    sf::Texture textureFond;
    sf::Texture textureFond2;
    sf::Texture textureQuitter;
    sf::Texture textureFin;
    sf::Texture textureFinV;
    sf::Texture bout3;
    sf::Texture bout4;
    sf::Texture bout5;
    sf::Texture bout6;
    sf::Texture boutRetour;

    //Sprites

    sf::Sprite sprite;
    sf::Sprite spriteLogo;
    sf::Sprite spritePartieRap;
    sf::Sprite spritePartiePerso;
    sf::Sprite spriteOcean;
    sf::Sprite spriteTerre;
    sf::Sprite spriteVilleAmi;
    sf::Sprite spriteVilleEnnemi;
    sf::Sprite spriteCasePossedeeAmi;
    sf::Sprite spriteCasePossedeeEnnemi;

    sf::Sprite spriteChar;
    sf::Sprite spriteHoplite;
    sf::Sprite spriteArcher;
    sf::Sprite spriteCanon;
    sf::Sprite spriteHussard;
    sf::Sprite spriteColon;
    sf::Sprite spriteLM;
    sf::Sprite spriteBombeAmi;

    sf::Sprite spriteCharE;
    sf::Sprite spriteHopliteE;
    sf::Sprite spriteArcherE;
    sf::Sprite spriteCanonE;
    sf::Sprite spriteHussardE;
    sf::Sprite spriteColonE;
    sf::Sprite spriteLME;
    sf::Sprite spriteBombeE;

    sf::Sprite spriteOr;
    sf::Sprite spriteProd;

    sf::Sprite spriteScience;
    sf::Sprite spriteScienceAge2;
    sf::Sprite spriteScienceAge3;

    sf::Sprite spriteNourriture;
    sf::Sprite spriteFond;
    sf::Sprite spriteFond2;
    sf::Sprite spriteQuitter;
    sf::Sprite spriteFin;
    sf::Sprite spriteFinV;
    sf::Sprite spriteBout3;
    sf::Sprite spriteBout4;
    sf::Sprite spriteBout5;
    sf::Sprite spriteBout6;
    sf::Sprite spriteBoutRetour;

    //Musique
    sf::SoundBuffer buffer;
    sf::Sound Intro;
    sf::SoundBuffer buffer2;
    sf::Sound Defaite;
    sf::SoundBuffer buffer3;
    sf::Sound MusiqueJeu;
    sf::SoundBuffer buffer4;
    sf::Sound Victoire;


public:
    Jeu_graphique();
    Jeu_graphique(int nbJoueur, string nomCiv_Jeu2);
    ~Jeu_graphique();

    /*! \brief  void Action_JeuGraphique (char action, char action2,Unite * u, Civilization & Civ, sf::View & view
                                 ,sf::View & view2, sf::View & minimapView, sf::View & BarreRessource)
    Choisit l'action en fonction du choix de l'action que l'on veut faire pour l'unite selectionnee
    @param (char action, char action2,Unite * u, Civilization & Civ, sf::View & view
                                 ,sf::View & view2, sf::View & minimapView, sf::View & BarreRessource)*/
    int Action_JeuGraphique (char  action,char  action2, Unite * u, Civilization & Civ, sf::RenderWindow & window,
                    sf::View & view, sf::View & view2,sf:: View & minimapView,sf::View & BarreRessource);

    /*! \brief  void ActionIA_JeuGraphique (Unite * u, Civilization & Civ, char actionParam)
    Choisit l'action en fonction du choix de l'action que l'IA choisit de faire
    @param (Unite * u, Civilization & Civ, char actionParam)*/
    void ActionIA_JeuGraphique(Unite * u, Civilization & Civ, char actionParam);

    /*! \brief  void  Acheter_Unite_JeuGraphique (char action2, int x,int y,  int ID_Civ)
    S'occupe de l'achat d'Unite lorsque c'est au tour d'une ville. Cette fonction verifie que le joueur
   a assez d'argent et si c'est le cas, ajoute la nouvelle unite au tableau de la bonne Civilisation.
    @param (char action2, int x,int y,  int ID_Civ)*/
    void Acheter_Unite_JeuGraphique(char action2, int x,int y,  int ID_Civ);

    /*! \brief  void  AttaqueUniteBombardement_JeuGraphique (int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
    Execute l'attaque des unites de distance et verifie si cela est possible. Le soldat pointe vers
   un ennemi et l'attaque a distance.
    @param (int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)*/
    void AttaqueUniteBombardement_JeuGraphique(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine);

    /*! \brief  void AttaqueUniteMelee_JeuGraphique(int i, int j,Unite* u, char action,bool & ok)
    Execute l'attaque d'une unite de melee (attaque au corps a corps) et verifie si cela est possible
     @param (int i, int j,Unite* u, char action,bool & ok)*/
    void AttaqueUniteMelee_JeuGraphique(int i, int j,Unite* u, char action,bool & ok);

    /*! \brief void AugmentationAge_JeuGraphique()
   Augmente l'age de la Civilisation si le joueur a atteint le niveau de science requis pour passer
   a l'ere superieure*/
    void AugmentationAge_JeuGraphique();

     /*! \brief void Acheter_Case_JeuGraphique(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
    Verifie que le joueur a assez de ressources pour acquerir la case selectionnee. Cette fonction passe
    la donnee proprioCase de -1 a 0 ou l'ID de la civilisation concernee.
     @param (int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)*/
    void Acheter_Case_JeuGraphique(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine);

     /*! \brief  void AchatCaseAutomatiqueIA_JeuGraphique (int civSelect, int uniteSelect)
    Cette fonction est executee uniquement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void AchatCaseAutomatiqueIA_JeuGraphique (int civSelect, int uniteSelect);

     /*! \brief void AtomisationAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect)
    Cette fonction est executee uniquement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void AtomisationAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect);

     /*! \brief  void BombardementAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect)
   Cette fonction est execute seulement pour le tour des IAs.
     @param (int civSelect, int uniteSelect)*/
    void BombardementAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect);//qd on l'appelle le distance bombarde l'ennemi le plus proche

    Civilization* getTabCiv_JeuGraphique();

    /*! \brief  void Construction_JeuGraphique(int nbJoueur, string nomCiv_Jeu2)
   Cette fonction est execute lorsque l'on choisit son mode de jeu afin de creer
   une partie en accord avec le choix du joueur (nb de joueurs etc...)
     @param (int nbJoueur, string nomCiv_Jeu2)*/
    void Construction_JeuGraphique(int nbJoueur, string nomCiv_Jeu2);

    /*! \brief  string ConvertisseurIntEnString_JeuGraphique(const int & i)
   Convertit l'entier passe en parametre pour renvoyer une chaine de caractere
   representant l'entier
     @param (const int & i)*/
    string ConvertisseurIntEnString_JeuGraphique (const int & i);

    /*! \brief void DistribuerRessource_JeuGraphique()
   Distribue les ressources(Or,Science, Production, Nourriture) en debut de tour */
    void DistribuerRessource_JeuGraphique();

     /*! \brief  void DefinirProprioUnite_JeuGraphique()
   Affecte un proprietaire a chaque unite du jeu en debut de tour*/
    void DefinirProprioUnite_JeuGraphique();

     /*! \brief  void DefinirCaseDejaOccupe_JeuGraphique(int x, int y)
   Change l'etat d'occupation  de la case en debut de tour
     @param (int x, int y)*/
    void DefinirCaseDejaOccupe_JeuGraphique(int x, int y);

    /*! \brief void DefinirTouteCaseDejaOccupe_JeuGraphique()
   Aplique la fonction DefinirCaseDejaOccupe a toutes les cases du plateau. Si il n'y a personne sur la
   case alors elle reste innocupee */
    void DefinirTouteCaseDejaOccupe_JeuGraphique ();

    /*! \brief  void DeplacementUnite_JeuGraphique(int i, int j,Unite* u,char action)
   Execute le deplacement d'unite de tout type et verifie si cela est possible
     @param (int i, int j,Unite* u,char action)*/
    void DeplacementUnite_JeuGraphique(int i, int j,Unite* u,char action);

     /*! \brief  void GestionTourGraph_JeuGraphique(sf::RenderWindow & window)
   Execute les actions du joueur en fonction de ses choix(Choix humain ou choix automatique IA)
    @param (sf::RenderWindow & window)*/
    void GestionTourGraph_JeuGraphique(sf::RenderWindow & window);

    /*! \brief  void RetablirCaseNulle_JeuGraphique(int x)
   Retablit les cases possedees par le joueur x a leur etat d'origine s'il a perdu.
     @param (int x)*/
    void RetablirCaseNulle_JeuGraphique(int x);


    /*! \brief  void RetablirPM_JeuGraphique(TableauDynamique & tabUnite)
   Retablit les Points de Mouvement des Unites en debut de tour
     @param (TableauDynamique & tabUnite)*/
    void RetablirPM_JeuGraphique(TableauDynamique & tabUnite);

    /*! \brief  Unite* GetUniteParCoord_JeuGraphique(int x, int y)
   Cherche une unite en fonction de ses coordonnees passes en parametre
   @param (int x, int y)*/
    Unite* GetUniteParCoord_JeuGraphique(int x, int y);

    /*! \brief  void VerificationUnitesMortes_Jeu_JeuGraphique()
   Verifie en debut de tour les unites mortes lors d'un combat et les supprime du tableau.*/
    void VerificationUnitesMortes_JeuGraphique();

    /*! \brief void VerificationActionIA_JeuGraphique(char & reponse, int civSelectionnee, int uniteSelectionnee)
        Verifie les actions de l'IA pour attribuer a chaque action de l'IA la bonne touche
     @param (char & reponse, int civSelectionnee, int uniteSelectionnee)*/
    void VerificationActionIA_JeuGraphique(char & reponse, int civSelectionnee, int uniteSelectionnee);
    //Traite les cas non pris en compte dans la classe IA car trop compliqué + les étapes

    //AFFICHAGE GRAPHIQUE

        /*! \brief  void Accueil_JeuGraphique()
    Creee et lance une fenetre windows.*/
    void Accueil_JeuGraphique();


    /*! \brief void AffichGraph_JeuGraphique(sf::RenderWindow & window,Unite * u, sf::View   view, sf::View  view2
                        ,sf::View & BarreRessource, sf::View & minimapView
                        ,int BougeCamera, int mode)
        Permet l'affichage graphique des textures, sprites et polices charges depuis la fonction ChargerPoliceTexture()
     @param (sf::RenderWindow & window,Unite * u, sf::View   view, sf::View  view2
                        ,sf::View & BarreRessource, sf::View & minimapView
                        ,int BougeCamera, int mode)*/
    void AffichGraph_JeuGraphique(sf::RenderWindow & window,Unite * u, sf::View   view, sf::View  view2
                        ,sf::View & BarreRessource, sf::View & minimapView
                        ,int BougeCamera, int mode);

        /*! \brief  void ChargerPoliceTexture_JeuGraphique()
    Permet le chargement des textures, sprites et polices de caractere*/
    void ChargerPoliceTexture_JeuGraphique();

     /*! \brief void DeplacerCamera_JeuGraphique(sf::View & view, sf::View & view2, sf::View & minimapView,sf::View & BarreRessource, sf::RenderWindow & window, Unite * u)
        Gere les actions du joueur humain en associant chaque touche a une action
     @param (sf::View & view, sf::View & view2, sf::View & minimapView,sf::View & BarreRessource, sf::RenderWindow & window, Unite * u)*/
    void DeplacerCamera_JeuGraphique(sf::View & view, sf::View & view2, sf::View & minimapView,sf::View & BarreRessource, sf::RenderWindow & window, Unite * u);

    /*! \brief  void Fin_JeuGraphique(sf::RenderWindow & window, sf::View & view)
   Affiche l'cran de Defaite
    @param  (sf::RenderWindow & window, sf::View & view)*/
    void Fin_JeuGraphique(sf::RenderWindow & window, sf::View & view);


    /*! \brief  void FinV_JeuGraphique(sf::RenderWindow & window, sf::View & view)
   Affiche l'ecran de Victoire
    @param  (sf::RenderWindow & window, sf::View & view)*/
    void FinV_JeuGraphique(sf::RenderWindow & window, sf::View & view);

     /*! \brief MenuPrincipal_JeuGraphique(sf::RenderWindow & window)
   Affiche le Menu principal
    @param  (sf::RenderWindow & window)*/
    void MenuPrincipal_JeuGraphique(sf::RenderWindow & window);

      /*! \brief PartiePerso_JeuGraphique(sf::RenderWindow & window)
   Affiche le Menu de choix lors d'une partie personnalisee
    @param  (sf::RenderWindow & window)*/
    void PartiePerso_JeuGraphique(sf::RenderWindow & window);

       /*! \brief Gagnant_JeuGraphique(sf::RenderWindow & window, sf::View & view)
    Fonction qui determine l'ecran de fin (victoire ou defaite)
    @param  (sf::RenderWindow & window, sf::View & view)*/
    void Gagnant_JeuGraphique(sf::RenderWindow & window, sf::View & view);

    /** void TestRegression_JeuGraphique()
        @brief  Test de regression du module Jeu_graphique, teste toutes les fonctions membres et affiche les resultats.
    */
    void TestRegression_JeuGraphique ();
};

#endif // JEU_H_INCLUDED

