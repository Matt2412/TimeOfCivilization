#include <vector>
#include <cmath>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

#include "IA.h"
#include "Civilization.h"
#include "Case.h"
#include "Unite.h"
#include "Plateau.h"
#include "TableauDynamique.h"

using namespace std;


IA::IA()
{
    nbRandom_IA=9999999;
    pretAssaut_IA=false;
    positionUniteSelectionnee_IA=999999;
    positionUniteSelectionneeX_IA=999999;
    positionUniteSelectionneeY_IA=999999;
    decisionFinale_IA='f';
}


IA::~IA()
{
    //cout<<"L'IA est detruite"<<endl;
}

char IA::GetDecisionFinale_IA() const {return decisionFinale_IA;}


int IA::Random_IA(int a, int b) const
{//genere un nombre aleatoire compris entre a et b

    return rand()%(b-a) +a;

}


void IA::AjouterUnitesEnnemies_IA(int ID_Civilization,  Plateau * plateau_Jeu)
{

    for(int i=0; i < plateau_Jeu->gettailleHorizontale()*plateau_Jeu->gettailleVerticale();i++)
    {
        if ((plateau_Jeu->GetCaseDeTabCase_Plateau(i).getDejaOccupe()!=ID_Civilization)&&(plateau_Jeu->GetCaseDeTabCase_Plateau(i).getDejaOccupe()!=-1))
        {//unite n'appartenant pas a l'IA
            //ne prend pas en compte le type de l'unite
            tabUnitesEnnemi_IA.push_back(i);//enregistre la case ou se situe l'ennemi
        }
    }
}


void IA::AjouterUnitesAlliees_IA(int ID_Civilization, Plateau * plateau_Jeu)
{
    for(int i=0; i < plateau_Jeu->gettailleHorizontale()*plateau_Jeu->gettailleVerticale();i++)
    {
        if (plateau_Jeu->GetCaseDeTabCase_Plateau(i).getDejaOccupe()==ID_Civilization)
        {//unite appartenant a l'IA
            //ne prend pas en compte le type de l'unite
            tabUnitesAlliees_IA.push_back(i);//enregistre la case ou se situe l'ennemi
        }
    }
}


int IA::DetectionEnnemiLePlusProche_IA(Plateau * plateau_Jeu)const
{
    int distanceX=40;int distanceY=20; int distanceXY=60;
    int uniteVise;

    for(unsigned int i=0; i<tabUnitesEnnemi_IA.size() ; i++)
    {
        int compteur=0;

        int distanceInitialeX =distanceX;
        int distanceInitialeY =distanceY;

        int posXUniteEnnemie=tabUnitesEnnemi_IA[i]%plateau_Jeu->gettailleHorizontale();

        int posYUniteEnnemie=tabUnitesEnnemi_IA[i]/plateau_Jeu->gettailleHorizontale();
        //cout<<"DetectionEnnemiLePlusProche :  ";
        //cout<<"POSITION X DE ENNEMI : "<<posXUniteEnnemie<<"  ET POSITION Y DE ENNEMI : "<<posYUniteEnnemie<<endl;

        if (abs(positionUniteSelectionneeX_IA-posXUniteEnnemie<=distanceX))
        {
                compteur+=1;
                distanceX=abs(positionUniteSelectionneeX_IA-posXUniteEnnemie);

        }
        if (abs(positionUniteSelectionneeY_IA-posYUniteEnnemie<=distanceY))
        {
                compteur+=1;
                distanceY=abs(positionUniteSelectionneeY_IA-posYUniteEnnemie);
        }
        if (compteur==2 && distanceX+distanceY<distanceXY)
        {
            distanceXY=distanceX+distanceY; uniteVise=tabUnitesEnnemi_IA[i];
        }
        else
        {
            distanceX=distanceInitialeX;
            distanceY=distanceInitialeY;
        }

    }
    return uniteVise;
}


bool IA::DetectionDesAlliesProches_IA(int ID_Civilization, Plateau * plateau_Jeu) const
{//c'est plus une confirmation d'attaque qu'une detection en fait
    int nombre = ID_Civilization;
    int compteur = 1;
    for(unsigned int i=0 ; i < tabUnitesAlliees_IA.size() ; i++)
    {
        if ( (tabUnitesAlliees_IA[i] - positionUniteSelectionnee_IA ) <= nombre )
        {
            compteur++; //si une unite alliee est proche on l'ajoute dans l'hypothetique armee
        }
        if ( (tabUnitesAlliees_IA[i] - positionUniteSelectionnee_IA ) > nombre )
        {
            compteur = compteur; //ca sert a rien mais cest pour mieux comprendre la fonction
        }
    }
    if(compteur>=nombre) return true;//l'armee est assez grande, a l'attaque !
    else
    {
        return false;//l'armee n'est pas assez grande
    }
}


int IA::DetectionVilleLaPlusProche_IA(int ID_Civilization, Plateau * plateau_Jeu,
                                      const TableauDynamique & tabUnite, int uniteSelectionnee)const
{
    int positionVille;
    int distance = 9999999;

    for(unsigned int i=0; i<tabUnite.taille_utilisee ; i++)
    {
        if(tabUnite.valeurIemeElement_Unite(i)->gettypeUnite()==0)
        {
            if(distance > tabUnite.valeurIemeElement_Unite(i)->getposY()*plateau_Jeu->gettailleHorizontale()+tabUnite.valeurIemeElement_Unite(i)->getposX() + positionUniteSelectionnee_IA )
            {
                positionVille = tabUnite.valeurIemeElement_Unite(i)->getposY()*plateau_Jeu->gettailleHorizontale()+tabUnite.valeurIemeElement_Unite(i)->getposX();
                distance = positionVille + positionUniteSelectionnee_IA;
            }
        }
    }
    return positionVille;
}


char IA::DeplacementSansEncombre(int ID_Civilization, Plateau * plateau_Jeu, TableauDynamique & tabUnite_Civilization, int uniteSelectionnee,
                                 char decisionSansVerif)
{
    int nbRandomDeplacement;
    char decisionAvecVerif = decisionSansVerif;
    //Teste si la case voulue est deja occupee, si oui on va ailleurs pour pas entrer en conflit
    int posUnite = tabUnite_Civilization.valeurIemeElement_Unite(uniteSelectionnee)->getposX() +
                   plateau_Jeu->gettailleHorizontale() *
                   tabUnite_Civilization.valeurIemeElement_Unite(uniteSelectionnee)->getposY() ;
    int posUniteW = posUnite - plateau_Jeu->gettailleHorizontale();
    int posUniteA = posUnite - 1;
    int posUniteS = posUnite + plateau_Jeu->gettailleHorizontale();
    int posUniteD = posUnite + 1;
    int typeUnit = tabUnite_Civilization.valeurIemeElement_Unite(uniteSelectionnee)->gettypeUnite();

    bool boolW=false; bool boolA=false;bool boolS = false; bool boolD=false;

    //On va dans des directions aleatoires tant que la voie n'est pas libre
    for(int i=0;i<4;i++)
    {
        if(decisionAvecVerif=='w'){ boolW=true; }
        if(decisionAvecVerif=='a'){ boolA=true; }
        if(decisionAvecVerif=='s'){ boolS=true; }
        if(decisionAvecVerif=='d'){ boolD=true; }

        if( (typeUnit == 2) || (typeUnit == 4) || (typeUnit == 6) )
        {
            if( (decisionAvecVerif=='w') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteW).getDejaOccupe() != ID_Civilization ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='a') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteA).getDejaOccupe() != ID_Civilization ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='s') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteS).getDejaOccupe() != ID_Civilization ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='d') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteD).getDejaOccupe() != ID_Civilization ) )
            {
                return decisionAvecVerif;
            }
        }
        if( (typeUnit == 3) || (typeUnit == 5) || (typeUnit == 7) )
        {
            if( (decisionAvecVerif=='w') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteW).getDejaOccupe() == -1 ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='a') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteA).getDejaOccupe() == -1 ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='s') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteS).getDejaOccupe() == -1 ) )
            {
                return decisionAvecVerif;
            }
            if( (decisionAvecVerif=='d') && (plateau_Jeu->GetCaseDeTabCase_Plateau(posUniteD).getDejaOccupe() == -1 ) )
            {
                return decisionAvecVerif;
            }
        }


        bool verifDirectionPasDejaPrise = false;

        while (verifDirectionPasDejaPrise==false)
        {
            nbRandomDeplacement = Random_IA(1,5);
            if(nbRandomDeplacement==1 && boolW==false) {verifDirectionPasDejaPrise=true; decisionAvecVerif='w';}
            if(nbRandomDeplacement==2 && boolA==false) {verifDirectionPasDejaPrise=true; decisionAvecVerif='a';}
            if(nbRandomDeplacement==3 && boolS==false) {verifDirectionPasDejaPrise=true; decisionAvecVerif='s';}
            if(nbRandomDeplacement==4 && boolD==false) {verifDirectionPasDejaPrise=true; decisionAvecVerif='d';}
        }
    }
    return 'f';
}



char IA::DecisionMelee_IA(int ID_Civilization,
                        int age_Civilization,
                        Plateau * plateau_Jeu,
                        TableauDynamique & tabUnite_Civilization,
                       int uniteSelectionnee
                       )
{
    int ennemi = DetectionEnnemiLePlusProche_IA(plateau_Jeu);
    bool allie = DetectionDesAlliesProches_IA(ID_Civilization,plateau_Jeu);

    if( (ennemi <= ID_Civilization) && (allie == false) )
    {//ennemi proche + allie loin = deplacement/attaque
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu,tabUnite_Civilization,uniteSelectionnee);
    }
    if( (ennemi > ID_Civilization) && (allie == false) )
    {//ennemi loin + allie loin = rien
        return 'f';
    }
    if( (ennemi < ID_Civilization) && (allie == true ) )
    {//ennemi proche + allie proche = deplacement/attaque
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu,tabUnite_Civilization,uniteSelectionnee);
    }
    else //if ( (ennemi > ID_Civilization) && (allie == true) )
    {//ennemi loin + allie proche = deplacement/attaque
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu,tabUnite_Civilization,uniteSelectionnee);
    }
    //1)attaquer ennemi proche
    //2)attendre qu'il y ait suffisamment d'allies autour : si oui fonction deplacement ; sinon on attend

}


char IA::DecisionDistance_IA(int ID_Civilization,
                            int age_Civilization,
                            Plateau * plateau_Jeu,
                            TableauDynamique & tabUnite_Civilization,
                           int uniteSelectionnee
                           )
{
    int ennemi = DetectionEnnemiLePlusProche_IA(plateau_Jeu);
    bool allie = DetectionDesAlliesProches_IA(ID_Civilization,plateau_Jeu);

    if( (ennemi < ID_Civilization) && (allie == false) )
    {//ennemi proche + allie loin = deplacement/attaque
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu, tabUnite_Civilization, uniteSelectionnee);
    }
    if( (ennemi > ID_Civilization) && (allie == false) )
    {//ennemi loin + allie loin = rien
        return 'f';
    }
    if( (ennemi < ID_Civilization) && (allie == true ) )
    {//ennemi proche + allie proche = deplacement/attaque
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu, tabUnite_Civilization, uniteSelectionnee);
    }
    else //if( (ennemi > ID_Civilization) && (allie == true) )
    {//ennemi loin + allie proche = deplacement
        return Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu, tabUnite_Civilization, uniteSelectionnee);
    }

}


char IA::DecisionBombe_IA(int ID_Civilization,
                            Plateau * plateau_Jeu,
                            TableauDynamique & tabUnite,
                           int uniteSelectionnee
                           )
{
    int absXennemi = DetectionEnnemiLePlusProche_IA(plateau_Jeu) % plateau_Jeu->gettailleHorizontale();
    int absYennemi = DetectionEnnemiLePlusProche_IA(plateau_Jeu) / plateau_Jeu->gettailleHorizontale();
    int absX = abs ( positionUniteSelectionneeX_IA - absXennemi );
    int absY = abs ( positionUniteSelectionneeY_IA - absYennemi );

    if( (absX + absY) < tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getDST())
    {
        return Atomisation_IA();
    }
    else
    {
        return 'f';
    }
}


char IA::Atomisation_IA()const
{   //on passe en mode atomisation
    cout<<"ON PASSE EN MODE ATOMIQUE"<<endl;
    return 'n';

}


char IA::Deplacement_IA(int ID_Civilization,
                        int age_Civilization,
                          Plateau * plateau_Jeu,
                          TableauDynamique & tabUnite,
                          int uniteSelectionnee
                          )// Deplacement d'une unite mobile
{
    int ennemi = DetectionEnnemiLePlusProche_IA(plateau_Jeu);
    switch(tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->gettypeUnite())
    {
    case 1://le colon, il s'eloigne le plus possible des ennemis

        if (ennemi < 4 * age_Civilization) // si ennemi trop pres du colon
        {
            return 'v';
        }
        if ( ID_Civilization <= DetectionVilleLaPlusProche_IA(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee) )
        { //si colon assez loin de la ville la plus proche
            return 'v';
        }
        else
        {
            nbRandom_IA = Random_IA(1,5);//sinon déplacement aléatoire
            if(nbRandom_IA==1)return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'w');
            if(nbRandom_IA==2)return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'a');
            if(nbRandom_IA==3)return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 's');
            if(nbRandom_IA==4)return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'd');
        }


    case 2: goto MELEEMARQUEUR1;break;
    case 4: goto MELEEMARQUEUR1;break;
    case 6: goto MELEEMARQUEUR1;break; //le melee, il s'approche le plus possible des ennemis
        if(1>2)
        {
            MELEEMARQUEUR1:

            int posXEnnemi=ennemi%plateau_Jeu->gettailleHorizontale();
            int posYEnnemi=ennemi/plateau_Jeu->gettailleHorizontale();

            if(posXEnnemi<positionUniteSelectionneeX_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee,'a');}
            if(posXEnnemi>positionUniteSelectionneeX_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee,'d');}
            if(posYEnnemi<positionUniteSelectionneeY_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee,'w');}
            if(posYEnnemi>positionUniteSelectionneeY_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee,'s');}
            if(posYEnnemi==positionUniteSelectionneeY_IA && posXEnnemi==positionUniteSelectionneeX_IA)assert(0);//{return 'f';}

    }
    case 3: goto DISTANCEMARQUEUR1;break;
    case 5: goto DISTANCEMARQUEUR1;break;
    case 7: goto DISTANCEMARQUEUR1;break;
        if(1>2)
        {
            DISTANCEMARQUEUR1:

            int posXEnnemi=ennemi%plateau_Jeu->gettailleHorizontale();
            int posYEnnemi=ennemi/plateau_Jeu->gettailleHorizontale();


           if ((abs(tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getposX() - posXEnnemi)>tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getDST()/2+1)
            || (abs(tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getposY() - posYEnnemi)>tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getDST()/2+1))//
            {//si la distance est plus grande que la portee du distance on se deplace

                if(posYEnnemi<positionUniteSelectionneeY_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'w');}
                if(posYEnnemi>positionUniteSelectionneeY_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 's');}
                if(posXEnnemi<positionUniteSelectionneeX_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'a');}
                if(posXEnnemi>positionUniteSelectionneeX_IA){return DeplacementSansEncombre(ID_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee, 'd');}
                if(posYEnnemi==positionUniteSelectionneeY_IA && posXEnnemi==positionUniteSelectionneeX_IA)assert(0);//{return 'f';}
            }
            else
            {//si ennemi assez proche on le bombarde
                return Bombardement_IA();
            }
        }
    }
    return 'f';
}


char IA::Bombardement_IA()const
{
    //on passe en mode curseur
    cout<<"ON PASSE EN MODE BOMBARDEMENT"<<endl;
    return 'b';
}


char IA::DecisionVille_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,
                   int age_Civilization,
                   int ID_Civilization,
                   Plateau * plateau_Jeu,
                    TableauDynamique & tabUnite,
                   int uniteSelectionnee
                   )

{
    nbRandom_IA = Random_IA(1,4);//prend une decision aleatoire entre colon/unite/case
    switch(nbRandom_IA)
    {
        case 1:
            if(nourritureCivilization >= 50)
            {//depenser la nourriture
                return 'g';
            }
            break;

        case 2:
            if(productionCivilization >= 12)
            {//depenser la production
                    if((productionCivilization >= 15)&&(age_Civilization==1))
                    {
                        int nbRandom = Random_IA(1,3);
                        if(nbRandom==1){return 'h';}
                        if(nbRandom==2){return 'a';}
                    }
                    if((productionCivilization >= 35)&&(age_Civilization==2))
                    {
                        int nbRandom = Random_IA(1,3);
                        if(nbRandom==1){return 'm';}
                        if(nbRandom==2){return 'k';}
                    }
                    if((productionCivilization >= 1000)&&(age_Civilization==3))
                    {//les civ ayant un gros ID auront moins de risque d'avoir l'atome
                        int nbRandom = Random_IA(1,ID_Civilization+1);
                        if(nbRandom <= (ID_Civilization/2) ){return 't';}
                        //if(nbRandom==ID_Civilization){return 'n';} //On desactive la fonctionnalite bombe atomique, faute de temps
                        else {return 'l';}
                    }
            }
            break;

        case 3:
            if (orCivilization >= 10 )
            {//depenser l'or
                return 'c';
                break;
            }
    }
    return 'f';//on achete rien
}


void IA::Decision_IA(int nourritureCivilization, int productionCivilization, int orCivilization, int scienceCivilization,
               int age_Civilization,
               int ID_Civilization,
                Plateau * plateau_Jeu,
                TableauDynamique & tabUnite,
               int uniteSelectionnee)
{
    char reponse;
    pretAssaut_IA = DetectionDesAlliesProches_IA(ID_Civilization, plateau_Jeu);
    positionUniteSelectionnee_IA = tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getposY()*plateau_Jeu->gettailleHorizontale()+tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->getposX();
    positionUniteSelectionneeX_IA = positionUniteSelectionnee_IA%plateau_Jeu->gettailleHorizontale();
    positionUniteSelectionneeY_IA = positionUniteSelectionnee_IA/plateau_Jeu->gettailleHorizontale();
    AjouterUnitesEnnemies_IA(ID_Civilization, plateau_Jeu);
    AjouterUnitesAlliees_IA(ID_Civilization, plateau_Jeu);

    switch(tabUnite.valeurIemeElement_Unite(uniteSelectionnee)->gettypeUnite())
    {
        case 0://ville
            reponse = DecisionVille_IA(nourritureCivilization, productionCivilization, orCivilization, scienceCivilization, age_Civilization, ID_Civilization,
                                          plateau_Jeu, tabUnite, uniteSelectionnee);
            break;
        case 1://colon
            reponse =  Deplacement_IA(ID_Civilization, age_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee);
            break;

        case 2: goto meleeMarqueur2;break;
        case 4: goto meleeMarqueur2;break;//melee
        case 6: goto meleeMarqueur2;break;
        if(1>2)
        {
            meleeMarqueur2:
            reponse = DecisionMelee_IA(ID_Civilization, age_Civilization, plateau_Jeu, tabUnite, uniteSelectionnee);
            break;
        }
        case 3: goto distanceMarqueur2;break;
        case 5: goto distanceMarqueur2;break;//distance
        case 7: goto distanceMarqueur2;break;
        if(1>2)
        {
            distanceMarqueur2:
            reponse = DecisionDistance_IA(ID_Civilization, age_Civilization,  plateau_Jeu, tabUnite, uniteSelectionnee);
            break;
        }
        case 8://atome
            reponse = DecisionBombe_IA (ID_Civilization, plateau_Jeu,tabUnite, uniteSelectionnee);
            break;
    }
    decisionFinale_IA = reponse;
}


void IA::TestRegression_IA()
{
    int testINT;
    char testCHAR;
    bool testBOOL;

    Plateau * plateauTestRegression = new Plateau(10,10);
    Civilization tabCivTestRegression[2];
    Unite * ville0 = new Unite(0,1,2,2);
    Unite * hoplite0 = new Unite(2,2,3,2);
    Unite * archer0 = new Unite(3,3,4,2);
    Unite * bombe0 = new Unite(3,4,5,2);
    tabCivTestRegression[0].getTabUnite().AjouterElement(ville0);
    tabCivTestRegression[0].getTabUnite().AjouterElement(hoplite0);
    tabCivTestRegression[0].getTabUnite().AjouterElement(archer0);
    Unite * ville1 = new Unite(0,5,4,4);
    Unite * archer1 = new Unite(3,6,5,4);
    tabCivTestRegression[1].getTabUnite().AjouterElement(ville1);
    tabCivTestRegression[1].getTabUnite().AjouterElement(archer1);


    cout<<"Voici le test de regression du module IA, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree un plateau 10x10 avec deux civilisations ayant chacunes des unites. "<<endl;
    cout<<"- int Random_IA(4, 9) renvoie un nombre compris entre 4 et 9  : "; testINT=Random_IA(4,9); cout<<testINT<<endl;


    cout<<"- void AjouterUnitesEnnemies_IA( 0 , plateauTestRegression ) remplit tabUnitesEnnemi_IA qui contient actuellement : ";
    for(unsigned int i=0;i<tabUnitesEnnemi_IA.size();i++) { testINT=tabUnitesEnnemi_IA[i];cout<<testINT<<",";}
    AjouterUnitesEnnemies_IA(0,plateauTestRegression);
    cout<<endl<<" apres appel, cette procedure ajoute dans tabUnitesEnnemi_IA les 2 ennemis : ";
    for(unsigned int i=0;i<tabUnitesEnnemi_IA.size();i++) { testINT=tabUnitesEnnemi_IA[i];cout<<testINT<<",";}
    cout<<endl;


    cout<<"- void AjouterUnitesAlliees_IA( 0, plateauTestRegression ) remplit tabUnitesAlliees_IA qui contient actuellement : ";
    for(unsigned int i=0;i<tabUnitesAlliees_IA.size();i++) { cout<<tabUnitesAlliees_IA[i]<<","; }
    AjouterUnitesAlliees_IA(0,plateauTestRegression);
    cout<<endl<<" apres appel, cette procedure ajoute dans tabUnitesAlliees_IA les allies : ";
    for(unsigned int i=0;i<tabUnitesAlliees_IA.size();i++) { cout<<tabUnitesAlliees_IA[i]<<","; }
    cout<<endl;


    positionUniteSelectionneeX_IA=2; positionUniteSelectionneeY_IA=2; positionUniteSelectionnee_IA=22;
    cout<<"- int DetectionEnnemiLePlusProche_IA( plateauTestRegression ) renvoie la position relative de l'ennemi le plus proche de notre ville : ";
    testINT = DetectionEnnemiLePlusProche_IA(plateauTestRegression);
    cout<<testINT<<endl;


    cout<<"- bool DetectionDesAlliesProches_IA(0,plateauTestRegression) confirme si l'armee est assez grande pour attaquer : ";
    testBOOL = DetectionDesAlliesProches_IA(0,plateauTestRegression);
    cout<<testBOOL<<endl;


    cout<<"- int DetectionVilleLaPlusProche(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),0) renvoie la position de la ville alliee la plus proche : ";
    testINT = DetectionVilleLaPlusProche_IA(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),0);
    cout<<testINT<<endl;


    cout<<"- char DeplacementSansEncombre(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1,'a') avant cette fonction, l'hoplite va se diriger a gauche, deja occupe par une ville";
    cout<<", la reponse renvoyee serait donc A, mais cette fonction va changer de direction pour eviter une collision, l'hoplite va donc changer de direction : ";
    testCHAR=DeplacementSansEncombre(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1,'a');
    cout<<testCHAR<<endl;


    cout<<"- char DecisionVille_IA(500,500,500,500,3,0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),0) va retourner une action, en partie influencee par les ressources";
    cout<<" de la civilisation 0 : ";
    testCHAR=DecisionVille_IA(500,500,500,500,3,0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),0);
    cout<<testCHAR<<endl;


    cout<<"- char DecisionMelee_IA(0, 3, plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1) renvoie une direction ou F : ";
    testCHAR=DecisionMelee_IA(0, 3, plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1);
    cout<<testCHAR<<endl;


    cout<<"- char DecisionDistance_IA(0, 3, plateauTestRegression,tabCivTestRegression[0].getTabUnite(),2) renvoie une direction ou F : ";
    testCHAR=DecisionDistance_IA(0, 3, plateauTestRegression,tabCivTestRegression[0].getTabUnite(),2);
    cout<<testCHAR<<endl;


    cout<<"- char DecisionBombe_IA(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),3) renvoie N ou F : ";
    testCHAR=DecisionBombe_IA(0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),3);
    cout<<testCHAR<<endl;


    cout<<"- char Bombardement_IA() renvoie N : ";
    testCHAR=Bombardement_IA();
    cout<<testCHAR<<endl;


    cout<<"- char Atomisation_IA() renvoie N : ";
    testCHAR=Atomisation_IA();
    cout<<testCHAR<<endl;


    cout<<"- char Deplacement_IA(0,3,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1) renvoie une direction : ";
    testCHAR = Deplacement_IA(0,3,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),1);
    cout<<testCHAR<<endl;


    cout<<"- void Decision_IA(500,500,500,500,3,0,plateauTestRegression,tabCivTestRegression[0].getTabUnite(),0) renvoie la reponse normale d'une ville : ";
    cout<<decisionFinale_IA<<endl;

    cout<<"Ceci marque la fin du test de regression du module IA."<<endl;


    delete ville0;   delete hoplite0;   delete archer0;   delete bombe0;   delete ville1;    delete archer1;
    delete plateauTestRegression;
}


