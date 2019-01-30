#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h
#include <cassert>
#include <unistd.h>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"

#include "Jeu.h"
#include "IA.h"

using namespace std;

//Sélectionne un nombre au hasard
int rand_a_b3(int a, int b){

    return rand()%(b-a) +a;
}

Jeu::Jeu(){};
Jeu::Jeu(int nbJoueur, string nomCiv_Jeu2)
{
    finDePartie_Jeu = false;
    tour_Jeu = 0;
    nomCiv_Jeu = nomCiv_Jeu2;
    plateau_Jeu = new Plateau(40,20);
    nbCiv_Jeu = nbJoueur;
    tabCiv_Jeu = new Civilization[nbCiv_Jeu];
    tabCiv_Jeu[0].setNomCivilization(nomCiv_Jeu2);
    for(int ID=0; ID<nbJoueur; ID++)
    {
        tabCiv_Jeu[ID].setCivilizationID(ID);
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(tabCiv_Jeu[ID].getUniteDeTabUnite(0)->getposX(),tabCiv_Jeu[ID].getUniteDeTabUnite(0)->getposY()).setProprioCase(ID);
        //La case de la ville de depart a comme proprietaire l'ID de la civilisation
    }
}


void Jeu::AffichTxt_Jeu(WinTXT & win, Unite * u, int mode, int positionOrigineX,int positionOrigineY)//Affichage Texte
{
    DefinirTouteCaseDejaOccupe ();
    VerificationUnitesMortes_Jeu();
    DefinirProprioUnite();

   // créer un flux de sortie
    std::ostringstream ossTours,ossOr, ossNourriture, ossScience,ossProd, ossUniteType,OssUnitePM, OssUniteNom, OssJoueur, OssPosX, OssPosY,OssJoueurVie;
    std::ostringstream ossProprioCase;

    // écrire un nombre dans le flux
    ossTours << tour_Jeu; ossNourriture << tabCiv_Jeu[0].getNourritureCivilization();ossProd<<tabCiv_Jeu[0].getProductionCivilization();
    ossOr <<tabCiv_Jeu[0].getOrCivilization(); ossScience<<tabCiv_Jeu[0].getscience_Civilization();ossUniteType<<u->gettypeUnite();
    OssUnitePM << u->gettypeUnite(); OssUniteNom<<u->getnomUnite();
    OssJoueur <<u->getproprioUnite();OssPosX<<u->getposX(); OssPosY<<u->getposY(); OssJoueurVie<<u->getPV();
    ossProprioCase<<u->getproprioUnite();

    // récupérer une chaîne de caractères
    string tours = ossTours.str();
    string NbOr = ossOr.str();string NbProd = ossProd.str(); string NbScience = ossScience.str(); string NbNourriture=ossNourriture.str();
    string UnitePm= OssUnitePM.str(); string UniteType = ossUniteType.str(); string UniteNom=OssUniteNom.str();
    string Joueur =OssJoueur.str(); string JoueurPosX =OssPosX.str();string JoueurPosY =OssPosY.str(); string VieUnite= OssJoueurVie.str();
    string ProprioCase =ossProprioCase.str();

    win.clear();

    for(int x=0;x<plateau_Jeu->gettailleHorizontale();++x)
    {
        for(int y=0;y<plateau_Jeu->gettailleVerticale();++y)
        {
             if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getTypeCase()==0)//Affiche le type de case
            {
                win.print(x+plateau_Jeu->gettailleHorizontale()+75,y+10,'-');
            }
            if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getTypeCase()==1)//Affiche le type de case
            {
                win.print(x+plateau_Jeu->gettailleHorizontale()+75,y+10,'-');
            }

            if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getProprioCase()==u->getproprioUnite())
            {
                win.print(x+plateau_Jeu->gettailleHorizontale()+75,y+10,ProprioCase[0]);
            }

            if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getDejaOccupe()>=0)
            {
                switch(GetUniteParCoord_Jeu(x, y)->gettypeUnite())//Affiche le type d'unité sur les cases
                {
                    case 0:
                    win.print(x+65 ,y+10,'V');
                    break;

                    case 1:
                    win.print(x+65 ,y+10,'C');
                    break;

                    case 2:
                    win.print(x+65 ,y+10,'H');
                    break;

                     case 3:
                    win.print(x+65 ,y+10,'A');
                    break;

                     case 4:
                    win.print(x+65 ,y+10,'M');
                    break;

                     case 5:
                    win.print(x+65 ,y+10,'K');
                    break;

                     case 6:
                    win.print(x+65,y+10,'T');
                    break;

                    case 7:
                    win.print(x+65 ,y+10,'L');
                    break;

                    case 8:
                    win.print(x+65 ,y+10,'B');
                    break;
                }
            }
            else
            {
                win.print(x+65 ,y+10,'-');
            }
        }
    }

    win.print(20,8,'T'); //Affichage des tours
    win.print(26,8,tours[0]);win.print(27,8,tours[1]);

    win.print(60,plateau_Jeu->gettailleVerticale()+22,'J'); //Affichage des tours
    win.print(70,plateau_Jeu->gettailleVerticale()+22,Joueur[0]);

    win.print(60,plateau_Jeu->gettailleVerticale()+23,'x'); //Affichage des tours
    win.print(68,plateau_Jeu->gettailleVerticale()+23,JoueurPosX[0]);
    win.print(69,plateau_Jeu->gettailleVerticale()+23,JoueurPosX[1]);
    win.print(75,plateau_Jeu->gettailleVerticale()+23,'y'); //Affichage des tours
    win.print(84,plateau_Jeu->gettailleVerticale()+23,JoueurPosY[0]);
    win.print(85,plateau_Jeu->gettailleVerticale()+23,JoueurPosY[1]);

    win.print(60,plateau_Jeu->gettailleVerticale()+24,'V'); //Affichage des vies de l'unité sélectionnée :
    win.print(75,plateau_Jeu->gettailleVerticale()+24,VieUnite[0]);
    win.print(76,plateau_Jeu->gettailleVerticale()+24,VieUnite[1]);

    win.print(20,plateau_Jeu->gettailleVerticale()+11,'R');

    win.print(20,plateau_Jeu->gettailleVerticale()+14,'N');
    win.print(32,plateau_Jeu->gettailleVerticale()+14,NbNourriture[0]);win.print(33,plateau_Jeu->gettailleVerticale()+14,NbNourriture[1]);
    win.print(34,plateau_Jeu->gettailleVerticale()+14,NbNourriture[2]); win.print(35,plateau_Jeu->gettailleVerticale()+14,NbNourriture[3]);

    win.print(20,plateau_Jeu->gettailleVerticale()+15,'P');
    win.print(32,plateau_Jeu->gettailleVerticale()+15,NbProd[0]);win.print(33,plateau_Jeu->gettailleVerticale()+15,NbProd[1]);
    win.print(34,plateau_Jeu->gettailleVerticale()+15,NbProd[2]);win.print(35,plateau_Jeu->gettailleVerticale()+15,NbProd[3]);

    win.print(20,plateau_Jeu->gettailleVerticale()+16,'O');
    win.print(24,plateau_Jeu->gettailleVerticale()+16,NbOr[0]);win.print(25,plateau_Jeu->gettailleVerticale()+16,NbOr[1]);
    win.print(26,plateau_Jeu->gettailleVerticale()+16,NbOr[2]);win.print(27,plateau_Jeu->gettailleVerticale()+16,NbOr[3]);

    win.print(20,plateau_Jeu->gettailleVerticale()+17,'S');
    win.print(29,plateau_Jeu->gettailleVerticale()+17,NbScience[0]);win.print(30,plateau_Jeu->gettailleVerticale()+17,NbScience[1]);
    win.print(31,plateau_Jeu->gettailleVerticale()+17,NbScience[2]);win.print(32,plateau_Jeu->gettailleVerticale()+17,NbScience[3]);

    if(u->gettypeUnite()==0)
    {
        const char * ch = "Unite selectionnee : VILLE";
        const char * ch1 = "TOUCHES DISPONIBLES : ";
        const char * ch2 ="a : Mode ACHAT UNITE";
        const char * ch3 ="c : Mode ACHAT CASE";
        const char * ch4 ="f : Passer son tour";
        const char * ch5 ="MODE ACHAT UNITE ACTIVE";
        const char * ch6 ="ACHATS DISPONIBLES : ";

        win.print(65,plateau_Jeu->gettailleVerticale()+13,*ch);
        win.print(65,plateau_Jeu->gettailleVerticale()+15,*ch1);
        win.print(95,plateau_Jeu->gettailleVerticale()+15,*ch2);
        win.print(95,plateau_Jeu->gettailleVerticale()+16,*ch3);
        win.print(95,plateau_Jeu->gettailleVerticale()+17,*ch4);
        if (mode==1)
        {
            win.print(75,plateau_Jeu->gettailleVerticale()+18,*ch5);
            win.print(65,plateau_Jeu->gettailleVerticale()+19,*ch6);
            win.print(95,plateau_Jeu->gettailleVerticale()+19,'c');
            win.print(115,plateau_Jeu->gettailleVerticale()+19,'h');
            win.print(95,plateau_Jeu->gettailleVerticale()+20,'a');
            win.print(115,plateau_Jeu->gettailleVerticale()+20,'m');
            win.print(95,plateau_Jeu->gettailleVerticale()+21,'k');
            win.print(115,plateau_Jeu->gettailleVerticale()+21,'t');
            win.print(95,plateau_Jeu->gettailleVerticale()+22,'l');
        }
        if (mode==2)
        {
            const char * ch7 ="MODE ACHAT CASE ACTIVE";
            const char * ch8 ="ACTIONS DISPONIBLES : ";
            const char * ch9 =" v : Valider l\'achat de la case ";
            win.print(75,plateau_Jeu->gettailleVerticale()+18,*ch7);
            win.print(65,plateau_Jeu->gettailleVerticale()+19,*ch8);
            win.print(95,plateau_Jeu->gettailleVerticale()+19,'w');
            win.print(115,plateau_Jeu->gettailleVerticale()+19,'s');
            win.print(95,plateau_Jeu->gettailleVerticale()+20,'a');
            win.print(115,plateau_Jeu->gettailleVerticale()+20,'d');
            win.print(95,plateau_Jeu->gettailleVerticale()+21,*ch9);

            //ACTIVATION VISUEL DU MODE BOMBARDEMENT
             for (int i=-(u->getDST());i<=0;i++)//Triangle supérieur gauche
            {
                for (int j =-i-(u->getDST());j<=0;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }

            for (int i=-(u->getDST());i<=0;i++)//Triangle supérieur droit
            {
                for (int j =0;j<=(u->getDST())+i;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }

             for (int i=0;i<=u->getDST();i++)
            {
                for (int j =0;j<=u->getDST()-i;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }
            for (int i=0;i<=u->getDST();i++)
            {
                for (int j =0;j>=-(u->getDST())+i;j--)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(positionOrigineX+j,positionOrigineY+i).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }
        }
    }
    if (u->gettypeUnite()==1 )

    {
        const char * ch1 = "TOUCHES DISPONIBLES : ";
        const char * ch4 ="f : Passer son tour";
        const char * ch10 ="Unite selectionnee : COLON";
        const char * ch11 ="w,a,s,d : DEPLACEMENT";
        const char * ch12 ="v : Fonder une ville";
        win.print(65,plateau_Jeu->gettailleVerticale()+13,*ch10);
        win.print(65,plateau_Jeu->gettailleVerticale()+15,*ch1);
        win.print(95,plateau_Jeu->gettailleVerticale()+15,*ch11);
        win.print(95,plateau_Jeu->gettailleVerticale()+16,*ch12);
        win.print(95,plateau_Jeu->gettailleVerticale()+17,*ch4);
    }
    if (u->gettypeUnite()==2 || u->gettypeUnite()==4 || u->gettypeUnite()==6 )
    {
        const char * ch1 = "TOUCHES DISPONIBLES : ";
        const char * ch4 ="f : Passer son tour";
        const char * ch11 ="w,a,s,d : DEPLACEMENT";
        const char * ch13 ="Unite selectionnee : MELEE";

        win.print(65,plateau_Jeu->gettailleVerticale()+13,*ch13);
        win.print(65,plateau_Jeu->gettailleVerticale()+15,*ch1);
        win.print(95,plateau_Jeu->gettailleVerticale()+15,*ch11);
        win.print(95,plateau_Jeu->gettailleVerticale()+16,*ch4);
    }
    if (u->gettypeUnite()==3 || u->gettypeUnite()==5 || u->gettypeUnite()==7 )
    {
        const char * ch1 = "TOUCHES DISPONIBLES : ";
        const char * ch4 ="f : Passer son tour";
        const char * ch11 ="w,a,s,d : DEPLACEMENT";
        const char * ch14 ="Unite selectionnee : DISTANCE";
        const char * ch15 ="b - mode bombardement";

        win.print(65,plateau_Jeu->gettailleVerticale()+13,*ch14);
        win.print(65,plateau_Jeu->gettailleVerticale()+15,*ch1);
        win.print(65,plateau_Jeu->gettailleVerticale()+15,*ch11);
        win.print(95,plateau_Jeu->gettailleVerticale()+16,*ch15);
        win.print(95,plateau_Jeu->gettailleVerticale()+17,*ch4);

        if (mode==1) //SI LE MODE BOMBARDEMENT EST ACTIF
        {
             const char * ch16 ="MODE BOMBARDEMENT ACTIVE";
            win.print(75,plateau_Jeu->gettailleVerticale()+19,*ch16);
            win.print(75,plateau_Jeu->gettailleVerticale()+20,'b');


             for (int i=-(u->getDST());i<=0;i++)//Triangle supérieur gauche
            {
                for (int j =-i-(u->getDST());j<=0;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }

            for (int i=-(u->getDST());i<=0;i++)//Triangle supérieur droit
            {
                for (int j =0;j<=(u->getDST())+i;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }

             for (int i=0;i<=u->getDST();i++)
            {
                for (int j =0;j<=u->getDST()-i;j++)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(j+positionOrigineX,i+positionOrigineY).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }
            for (int i=0;i<=u->getDST();i++)
            {
                for (int j =0;j>=-(u->getDST())+i;j--)
                {
                    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(positionOrigineX+j,positionOrigineY+i).getDejaOccupe()==-1)//SI la case est inoccupée;
                    {
                        win.print(65+positionOrigineX+j,positionOrigineY+10+i,'*');
                    }
                }
            }
        }
    }
    win.print(u->getposX()+65,u->getposY()+10,'X');
	win.draw();
}

void Jeu::RetablirPM_Jeu(TableauDynamique & tabUnite)//A faire en debut de tour
{
    for (int j=0; j<nbCiv_Jeu;j++)
    {//civilizations
        for(unsigned int i=0; i<tabCiv_Jeu[j].getTabUnite().taille_utilisee;i++)
        {//unites
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==0){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(0);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==1){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==2){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==3){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(1);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==4){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(3);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==5){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==6){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(5);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==7){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(3);}
            if(tabCiv_Jeu[j].getUniteDeTabUnite(i)->gettypeUnite()==8){tabCiv_Jeu[j].getUniteDeTabUnite(i)->setPM(0);}
        }
    }
}

void Jeu::DistribuerRessource_Jeu() //A faire en debut de tour
{
    int proprio;
    for(int i=0;i< plateau_Jeu->gettailleHorizontale()* plateau_Jeu->gettailleVerticale();i++)//parcourir toutes les cases
    {
        proprio =  plateau_Jeu->GetCaseDeTabCase_Plateau(i).getProprioCase();
        if (proprio != -1) //avec -1 pas de proprio
        {
            tabCiv_Jeu[proprio].setNourritureCivilization(tabCiv_Jeu[proprio].getNourritureCivilization()+ plateau_Jeu->GetCaseDeTabCase_Plateau(i).getNourritureParCase());
            tabCiv_Jeu[proprio].setProductionCivilization(tabCiv_Jeu[proprio].getProductionCivilization()+ plateau_Jeu->GetCaseDeTabCase_Plateau(i).getProductionParCase());
            tabCiv_Jeu[proprio].setOrCivilization(tabCiv_Jeu[proprio].getOrCivilization()+ plateau_Jeu->GetCaseDeTabCase_Plateau(i).getOrParCase());
            tabCiv_Jeu[proprio].setscienceCivilization(tabCiv_Jeu[proprio].getscience_Civilization()+ plateau_Jeu->GetCaseDeTabCase_Plateau(i).getScienceParCase());
        }
    }
}

void Jeu::Action_Jeu (Unite * u, WinTXT & win, Civilization & Civ)
{
    bool ok = true;
    char action;
    int mode=0;
    AffichTxt_Jeu(win, u, mode,0,0);

    if (u->gettypeUnite()==0)
    {//ville
        do{
                bool ok2=true;
                mode=0;
                action = win.getCh();
                switch(action)
                {
                    case 'f':
                    ok = false;
                    break;

                    case 'a'://Acheter une unité
                        mode=1;
                        AffichTxt_Jeu(win,u, mode,0,0);
                        ok2=true;
                        char action2;
                        while(ok2)
                        {
                            action2 = win.getCh();
                            switch(action2)
                            {
                                case 'c': //Colon
                                    if (Civ.getNourritureCivilization()>=50)
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(), 0);
                                    }
                                    ok2=false;
                                    break;

                                case 'h'://Hoplite
                                    if ((Civ.getProductionCivilization()>10)&&(Civ.getage_Civilization()==1))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 'a'://Archer
                                     if ((Civ.getProductionCivilization()>15)&&(Civ.getage_Civilization()==1))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 'm'://Hussard
                                    if ((Civ.getProductionCivilization()>25)&&(Civ.getage_Civilization()==2))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 'k'://Canon
                                    if ((Civ.getProductionCivilization()>35)&&(Civ.getage_Civilization()==2))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 't'://Tank
                                    if ((Civ.getProductionCivilization()>150)&&(Civ.getage_Civilization()==3))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 'l'://Lance missile
                                    if ((Civ.getProductionCivilization()>250)&&(Civ.getage_Civilization()==3))
                                    {
                                       Acheter_Unite_Jeu(action2, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                                    }
                                    ok2=false;
                                    break;

                                case 'f': //Cas ou le joueur ne veut plus acheter
                                ok2=false;
                                break;
                            }
                            ok = false;
                        }
                        break;

                    case 'c'://Acheter une case
                        int PositionOrigineX = u->getposX(); int PositionOrigineY = u->getposY();//Position initial en x et y de l'unité
                        mode=2;
                        AffichTxt_Jeu(win,u, mode,0,0);
                        ok2=true;
                        char action3;
                        u->setDST(8);
                        u->setPM(8);//On met les PM de la ville à 8
                        while(ok2)
                        {
                            action3 = win.getCh();
                            switch(action3)
                            {
                                case 'w':
                                    Acheter_Case_Jeu(0,-1 ,u,action3,ok2,PositionOrigineX,PositionOrigineY );
                                    break;

                                case 'a':
                                    Acheter_Case_Jeu(-1,0 ,u,action3,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 's':
                                    Acheter_Case_Jeu(0,1 ,u,action3,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 'd':
                                    Acheter_Case_Jeu(1,0 ,u,action3,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 'f': //Cas ou le joueur ne veut plus attaquer
                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    ok2=false;
                                    break;

                                case 'v' :
                                    Acheter_Case_Jeu(0,0,u,action3,ok2,PositionOrigineX,PositionOrigineY);
                                break;
                            }
                        AffichTxt_Jeu(win,u, mode,PositionOrigineX,PositionOrigineY);
                        }
                    u->setPM(0); u->setDST(0);//On remet les PM de la ville à 0
                    ok = false;
                    break;
                }
           }while (ok);
    }

    if (u->gettypeUnite()==1) //Actions du colon
    {
        if(u->getPM()>=1)
        {
            do {
                    action = win.getCh();
                    switch(action)
                    {
                        case 'w' :
                        DeplacementUnite_Jeu(0,-1 ,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'a' :
                        DeplacementUnite_Jeu(-1,0 ,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 's' :
                        DeplacementUnite_Jeu(0,1 ,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'd' :
                        DeplacementUnite_Jeu(1,0 ,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'v':
                        u->Fonder_Ville(action);
                        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setProprioCase(u->getproprioUnite());//Le proprio de la case prend la valeur de l'ID de la civilisation
                        ok = false;
                        break;

                        case 'f':
                        ok = false;
                        break;
                     }
                     AffichTxt_Jeu(win,u, mode,0,0);
                }while (ok);
        }
    }

    if ((u->gettypeUnite()==2)or(u->gettypeUnite()==4)or(u->gettypeUnite()==6))//Actions des soldats de melees et du tank
    {
        if(u->getPM()>=1)
        {
            do {
                    action = win.getCh();

                    switch(action)
                    {
                         case 'w' :
                         AttaqueUniteMelee_Jeu(0,-1,u,action,ok);
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;

                         case 'a' :
                         AttaqueUniteMelee_Jeu(-1,0,u,action,ok);
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;

                         case 's' :
                         AttaqueUniteMelee_Jeu(0,1,u,action,ok);
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;

                         case 'd' :
                         AttaqueUniteMelee_Jeu(1,0,u,action,ok);
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;

                         case 'f':
                         ok=false;
                         break;
                    }
                    AffichTxt_Jeu(win,u, mode,0,0);
                }while(ok);
        }
    }

    if ((u->gettypeUnite()==3)or(u->gettypeUnite()==5)or(u->gettypeUnite()==7))
    {//distance
         BACK://le goto est plus bas, lorsque le distance veut quitter le mode bombardement
          if(u->getPM()>=1)
          {
              do {
                    mode=0;
                    action = win.getCh();

                    AffichTxt_Jeu(win,u,mode,0,0);
                    switch(action)
                    {
                         case 'w' :
                         DeplacementUnite_Jeu(0,-1 ,u,action);
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;
                         case 'a' :
                         DeplacementUnite_Jeu(-1,0,u,action);
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;

                        case 's' :
                        DeplacementUnite_Jeu(0,1,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'd' :
                        DeplacementUnite_Jeu(1,0,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'f':
                        ok=false;
                        break;

                        case 'b' : //mode bombardement

                        int PositionOrigineX = u->getposX(); int PositionOrigineY = u->getposY();//Position initial en x et y de l'unité
                        int PmOrigine = u->getPM();mode=1;
                        AffichTxt_Jeu(win,u,mode,PositionOrigineX,PositionOrigineY);
                        bool ok2=true; char action2;
                        u->setPM(u->getDST());

                        while(ok2) /*Boucle while dans laquelle le personnage peut viser toutes les cases à sa portée
                      On modélise cela par le déplacement de l'unité dans un périmètre défini par sa portée
                      Au moment ou l'unité se déplace sur une unité ennemie, on appelle la fonction pour
                      le corps à corps et l'unité que le joueur dirige retourne alors à sa place en ayant attaqué
                      EN fonction de ses vies etc celle-ci peut mourir ou non, tout comme l'unité adverse (comme au CAC)*/
                        {
                            action2 = win.getCh();
                            switch(action2)
                            {
                                case 'w':
                                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                                    AttaqueUniteBombardement_Jeu(0,-1 ,u,action2,ok2,PositionOrigineX,PositionOrigineY );
                                    break;

                                case 'a':
                                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                                    AttaqueUniteBombardement_Jeu(-1,0 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 's':
                                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                                    AttaqueUniteBombardement_Jeu(0,1 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 'd':
                                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                                    AttaqueUniteBombardement_Jeu(1,0 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                                    break;

                                case 'f': //Cas ou le joueur ne veut plus attaquer

                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    ok2=false;
                                    break;

                                case 'b': //Cas ou le joueur ne veut plus attaquer et revenir au mode normal

                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY); u->setPM(PmOrigine);
                                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    goto BACK;
                                    break;
                             }
                             DefinirTouteCaseDejaOccupe();
                             VerificationUnitesMortes_Jeu();
                             AffichTxt_Jeu(win,u, mode,PositionOrigineX,PositionOrigineY);
                         }
                         plateau_Jeu->GetCaseIDParCoordonnees_Plateau(PositionOrigineX,PositionOrigineY).setDejaOccupe(-1);
                         u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                         plateau_Jeu->GetCaseIDParCoordonnees_Plateau(PositionOrigineX,PositionOrigineY).setDejaOccupe(u->getproprioUnite());
                         u->setPM(PmOrigine);
                         ok = false;
                         break;
                     }
                  }while(ok);
          }
    }
    if  (u->gettypeUnite()==8)
    {
        int PositionOrigineX = u->getposX();
        int PositionOrigineY = u->getposY();//Position initial en x et y de l'unité
        mode=1;
        AffichTxt_Jeu(win,u,mode,PositionOrigineX,PositionOrigineY);
        bool ok2=true; char action2;
        u->setPM(u->getDST());

        while(ok2) /*Boucle while dans laquelle le personnage peut viser toutes les cases à sa portée
      On modélise cela par le déplacement de l'unité dans un périmètre défini par sa portée
      Au moment ou l'unité se déplace sur une unité ennemie, on appelle la fonction pour
      le corps à corps et l'unité que le joueur dirige retourne alors à sa place en ayant attaqué
      EN fonction de ses vies etc celle-ci peut mourir ou non, tout comme l'unité adverse (comme au CAC)*/
        {
            action2 = win.getCh();
            switch(action2)
            {
                case 'w':
                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                    AttaqueUniteAtomisation_Jeu(0,-1 ,u,action2,ok2,PositionOrigineX,PositionOrigineY );
                    break;

                case 'a':
                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                    AttaqueUniteAtomisation_Jeu(-1,0 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                    break;

                case 's':
                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                    AttaqueUniteAtomisation_Jeu(0,1 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                    break;

                case 'd':
                    cout<<u->getposX()<<" / "<<u->getposY()<<" : Position"<<endl;
                    AttaqueUniteAtomisation_Jeu(1,0 ,u,action2,ok2,PositionOrigineX,PositionOrigineY);
                    break;

                case 'f': //Cas ou le joueur ne veut plus attaquer

                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                    ok2=false;
                    break;

             }
             DefinirTouteCaseDejaOccupe();
             VerificationUnitesMortes_Jeu();
             AffichTxt_Jeu(win,u, mode,PositionOrigineX,PositionOrigineY);
         }
    }
    AffichTxt_Jeu(win, u,mode,0,0);
}

void Jeu::VerificationUnitesMortes_Jeu ()
{
    if(tour_Jeu>1)
    {
        int compteurCivEnnemis=0; int compteurVillesAmis=0;
         for (int i =0; i<nbCiv_Jeu;i++ )
         {
             for (unsigned int j = 0; j<tabCiv_Jeu[i].getTabUnite().taille_utilisee;j++)
             {
                 if (tabCiv_Jeu[i].getUniteDeTabUnite(j)->getPV()<=0)
                 {
                     tabCiv_Jeu[i].getTabUnite().SupprimerElement(j);
                 }
             }
         }
         for (int i =0; i<nbCiv_Jeu;i++ )
         {
             for (unsigned int j = 0; j<tabCiv_Jeu[i].getTabUnite().taille_utilisee;j++)
             {
                 if (i!=0)
                 {
                    if (tabCiv_Jeu[i].getUniteDeTabUnite(j)->gettypeUnite()==0)
                    {
                        compteurCivEnnemis=compteurCivEnnemis+1;//Compteur qui s'incrémente que si un ennmi possède une ville
                    }
                 }
                 else
                 {
                     if (tabCiv_Jeu[i].getUniteDeTabUnite(j)->gettypeUnite()==0)
                     {
                         compteurVillesAmis=compteurVillesAmis+1;//Compteur qui s'incrémente que si le joueur possède une ville
                     }
                 }
            }
         }
        if (compteurCivEnnemis==0 || compteurVillesAmis==0)//Si le compteur CivEnnemi est à 0, cela signifie que les ennmis n'ont plus de ville, donc le joueur gagne
        {
            nbCiv_Jeu=1; finDePartie_Jeu=true;
        }
    }
}

void Jeu::AugmentationAge_Jeu()
{
    for (int i =0; i<nbCiv_Jeu;i++ )
    {
        if (tabCiv_Jeu[i].getscience_Civilization()>=100)
        {
            if (tabCiv_Jeu[i].getage_Civilization()!=2)
            {
                 tabCiv_Jeu[i].setage_Civilization(2);
            }
        }
        if(tabCiv_Jeu[i].getscience_Civilization()>=300)
        {
            if (tabCiv_Jeu[i].getage_Civilization()!=3)
            {
                tabCiv_Jeu[i].setage_Civilization(3);
            }
        }
    }
}

void Jeu::GestionTourTxt_Jeu()
{
    WinTXT win (180,50);

    while(finDePartie_Jeu==false)//tant qu'il reste des joueurs la partie continue
    {
        tour_Jeu += 1;

        DefinirTouteCaseDejaOccupe ();
        VerificationUnitesMortes_Jeu();
        DistribuerRessource_Jeu();
        AugmentationAge_Jeu();

        for(int compteurTourCiv=0;compteurTourCiv<nbCiv_Jeu;compteurTourCiv++)//tant que toutes les civ n'ont pas fini leur tour
        {
             if(compteurTourCiv == 0) //c'est au tour du joueur
             {
                 for(unsigned int compteurUniteCiv=0;compteurUniteCiv<tabCiv_Jeu[0].getTabUnite().taille_utilisee;compteurUniteCiv++)
                 {//Parcourt toutes les unites de tabUnite du joueur

                     DefinirTouteCaseDejaOccupe ();
                     VerificationUnitesMortes_Jeu();

                     Action_Jeu(tabCiv_Jeu[0].getUniteDeTabUnite(compteurUniteCiv), win, tabCiv_Jeu[0]);
                     DefinirProprioUnite();
                     DefinirTouteCaseDejaOccupe ();
                     VerificationUnitesMortes_Jeu();
                     //On passe en paramètre l'unité joué, l'affichage et la civilisation jouée
                     if (finDePartie_Jeu==true){goto FINDEJEU;}//SI LES VILLES ENNEMIS SONT MORTES ALORS ON QUITTE LA BOUCLE
                 }
             }
             else //c'est au tour de l'IA
             {
                 for(unsigned int compteurUniteCiv=0;compteurUniteCiv<tabCiv_Jeu[compteurTourCiv].getTabUnite().taille_utilisee;compteurUniteCiv++)
                 {
                     if( (tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==0) ||
                         ( tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==8  ) )
                     {//on rajoute 1 PM si c'est une ville ou une bombe parce que ...
                         tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->setPM(1);
                     }
                     while(tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->getPM()>0 )
                     {
                         IA test;
                         test.Decision_IA(tabCiv_Jeu[compteurTourCiv].getNourritureCivilization(),//int nourriture_Civilization
                                   tabCiv_Jeu[compteurTourCiv].getProductionCivilization(),//int production_Civilization
                                   tabCiv_Jeu[compteurTourCiv].getOrCivilization(),         //int or_Civilization
                                   tabCiv_Jeu[compteurTourCiv].getscience_Civilization(),    //int science_Civilization
                                   tabCiv_Jeu[compteurTourCiv].getage_Civilization(),         //int age_Civilization
                                   compteurTourCiv,                                          //int ID_Civilization
                                   plateau_Jeu,                                          //const Plateau & plateau_Jeu
                                   tabCiv_Jeu[compteurTourCiv].getTabUnite(),            //const Civilization & tabUnite
                                   compteurUniteCiv);                                  //int uniteSelectionnee);
                         char test2 = test.GetDecisionFinale_IA();
                         DefinirProprioUnite();
                         DefinirTouteCaseDejaOccupe ();
                         VerificationUnitesMortes_Jeu();
                         if (finDePartie_Jeu==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE
                         VerificationActionIA_Jeu(test2,compteurTourCiv,compteurUniteCiv);
                         if (finDePartie_Jeu==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE
                         ActionIA_Jeu(tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv), win, tabCiv_Jeu[compteurTourCiv],test2);
                         if (finDePartie_Jeu==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE

                         if( (tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==0) ||
                             (tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==8)  )
                         {//si c'est une ville ou une bombe, on remet ses PM a 0 car on les a ajoutes plus haut
                            tabCiv_Jeu[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->setPM(0);
                         }

                     }

                 }//fin tour civ
             }
             RetablirPM_Jeu(tabCiv_Jeu[compteurTourCiv].getTabUnite());
             RetablirCaseNulle(compteurTourCiv);
        }
    }
    //GO TO QUI PERMET DE SORTIR DE LA BOUCLE
    FINDEJEU: cout<<"FIN DE LA PARTIE! ";
}

void Jeu::AchatCaseAutomatiqueIA (int civSelect, int uniteSelect) //PAS ENCORE LIEE A AUCUNE FONCTION, IL FAUDRA LA PLACER DANS GESTION TOUR TXT.
{
      //On détermine la pos x et y de l'unité puis on choisit aléatoire une pos x et y non loin de l'unité pour acheter une case
      int posUniteX = tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getposX();
      int posUniteY = tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getposY();
      int posXCase =  rand_a_b3(posUniteX-8, posUniteX+9);
      int posYCase =  rand_a_b3(posUniteY-8, posUniteY+9);

      if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(posXCase,posYCase).getProprioCase() == -1)
      {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(posXCase,posYCase).setProprioCase(civSelect);
            tabCiv_Jeu[civSelect].setOrCivilization(tabCiv_Jeu[civSelect].getOrCivilization()-10);
            cout<<"La civilisation "<<civSelect<<" vient d'acheter une case en ("<<posXCase<<" , "<<posYCase<<")."<<endl;
      }
      else
      {
          cout<<"Case déjà achetée, achat impossible"<<endl;
      }

}

void Jeu::BombardementAutomatiqueIA(int civSelect, int uniteSelect)
{//detecte l'ennemi le plus proche pour le bombarder automatiquement

    int posX = tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getposX();
    int posY = tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getposY();
    //detection de l'ennemi le plus proche, normalement a portee du distance
    int minimumDistanceX = tabCiv_Jeu[0].getUniteDeTabUnite(0)->getposX();
    int minimumDistanceY = tabCiv_Jeu[0].getUniteDeTabUnite(0)->getposY();
    int nouveauMinimumDistanceX;
    int nouveauMinimumDistanceY;

    int DistanceX = 60; int DistanceY=60; int DistanceXY=60;

    for(int j=0; j<plateau_Jeu->gettailleVerticale();j++)
    {
        for(int i=0;i<plateau_Jeu->gettailleHorizontale();i++)
        {
            if((plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != -1) &&
              (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != civSelect))
              //si  la case n'est pas vide et est occupée par un ennmi alors
              {
                    nouveauMinimumDistanceX = i;
                    nouveauMinimumDistanceY = j;

                    DistanceX=abs(nouveauMinimumDistanceX-posX);
                    DistanceY=abs(nouveauMinimumDistanceY-posY);

                    if (DistanceX+DistanceY<=DistanceXY)
                    {
                        DistanceXY=DistanceX+DistanceY;
                        minimumDistanceX = nouveauMinimumDistanceX;
                        minimumDistanceY = nouveauMinimumDistanceY;
                    }
                    else
                    {
                        DistanceX=abs(minimumDistanceX-posX);
                        DistanceY=abs(minimumDistanceY-posY);
                    }
              }
        }
    }
    //On a la position de l'ennemi le plus proche, maintenant il faut retrancher ses PV

    cout<<"POSITION X : " << minimumDistanceX<<"/ POSITION Y : "<<minimumDistanceY<<endl;
    int ATKdeMoi = tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getATK();
    int PDVdeEnnemi = GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getPV();
    GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->setPV( PDVdeEnnemi - ATKdeMoi );

    cout<<"L'unite "<<tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getnomUnite()<<
    " de la civilisation "<<civSelect<<" vient d'attaquer "<< GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getnomUnite()
    << " de la civilisation "<<GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getproprioUnite()<<". Il lui reste "<<
    PDVdeEnnemi<<" PDV."<<endl;

    if( GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getPV() <= 0 )
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(minimumDistanceX,minimumDistanceY).setDejaOccupe(-1);
    }
    VerificationUnitesMortes_Jeu();
}



void Jeu::AtomisationAutomatiqueIA(int civSelect, int uniteSelect)
{//detecte l'ennemi le plus proche pour l'atomiser automatiquement
    //detection de l'ennemi le plus proche, normalement a portee du distance
    int minimumDistanceX = tabCiv_Jeu[0].getUniteDeTabUnite(0)->getposX();
    int minimumDistanceY = tabCiv_Jeu[0].getUniteDeTabUnite(0)->getposY();
    int minimumDistance  = minimumDistanceX + minimumDistanceY * plateau_Jeu->gettailleHorizontale();
    int nouveauMinimumDistanceX;
    int nouveauMinimumDistanceY;
    int nouveauMinimumDistance;

    for(int j=0; j<plateau_Jeu->gettailleVerticale();j++)
    {
        for(int i=0;i<plateau_Jeu->gettailleHorizontale();i++)
        {
            if((plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != -1) &&
              (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != civSelect))
            {
                nouveauMinimumDistanceX = i;
                nouveauMinimumDistanceY = j;
                nouveauMinimumDistance = i + j * plateau_Jeu->gettailleHorizontale();
                if(nouveauMinimumDistance < minimumDistance)
                {
                    minimumDistanceX = nouveauMinimumDistanceX;
                    minimumDistanceY = nouveauMinimumDistanceY;
                    minimumDistance = nouveauMinimumDistance;
                }
            }
        }
    }
    //On a la position de l'ennemi le plus proche, maintenant il faut annihiler ses PV

    cout<<"L'unite "<<tabCiv_Jeu[civSelect].getUniteDeTabUnite(uniteSelect)->getnomUnite()<<
          " de la civilisation "<<civSelect<<" vient d'atomiser : ";

    for(int j=minimumDistanceY-2 ; j<minimumDistanceY+2 ; j++)
    {//atomiser une zone assez large
        for(int i=minimumDistanceX-2 ; i<minimumDistanceX+2 ; i++)
        {
            if( plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != -1 &&
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != civSelect )
            {
                cout<<GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getnomUnite()<< " de la civilisation "
                <<GetUniteParCoord_Jeu(minimumDistanceX,minimumDistanceY)->getproprioUnite()<<" , ";
                GetUniteParCoord_Jeu(i,j)->setPV(0);
            }
        }
    }

    cout<<endl;

    //tabCiv_Jeu->getUniteDeTabUnite(uniteSelect)->setPV(0);//supprimer bombe apres utilisation

    DefinirTouteCaseDejaOccupe();

    VerificationUnitesMortes_Jeu();
}

void Jeu::VerificationActionIA_Jeu(char & reponse, int civSelectionnee, int uniteSelectionnee)
{
    if(reponse=='b')
    {//Lorsque une distance/bombe passe en mode bombardement/atomisation
    cout<<"Declenchement du mode bombardement d'une IA "<<endl;
        BombardementAutomatiqueIA(civSelectionnee, uniteSelectionnee);
        reponse = 'f';
    }
    if(reponse=='n')
    {
        cout<<"Declenchement du mode atomisation d'une IA"<<endl;
        AtomisationAutomatiqueIA(civSelectionnee, uniteSelectionnee);
        reponse = 'f';
    }
    if(reponse=='c')
    {
        cout<<"Declenchement du mode achat de case d'une IA"<<endl;
        AchatCaseAutomatiqueIA(civSelectionnee, uniteSelectionnee);
        reponse = 'f';
    }
}

void Jeu::RetablirCaseNulle(int x)// remettre a 0 les cases d'une civilisation quand celle-ci meurt
{
    int compteurVille = 0 ;
    for(unsigned int  j = 0; j<tabCiv_Jeu[x].getTabUnite().taille_utilisee;j++)
    {
        if(tabCiv_Jeu[x].getUniteDeTabUnite(j)->gettypeUnite()== 0)// 0 = ville
        {
            compteurVille+=1;
        }
    }
    if (compteurVille == 0)
    {
        for(int k = 0;k< plateau_Jeu->gettailleHorizontale()* plateau_Jeu->gettailleVerticale();k++)
        {
            if ( plateau_Jeu->GetCaseDeTabCase_Plateau(k).getProprioCase() == x)
            {
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setProprioCase(-1);
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setDejaOccupe (-1);
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setOrParCase(0);
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setNourritureParCase(0);
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setScienceParCase(0);
                 plateau_Jeu->GetCaseDeTabCase_Plateau(k).setProductionParCase(0);
            }
        }
    }
}

Civilization* Jeu::getTabCiv_Jeu()
{
    return tabCiv_Jeu;
}


//Retourne une Unite en fonction de ses coordonnées
Unite* Jeu::GetUniteParCoord_Jeu(int x, int y)
{
    if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getDejaOccupe() != -1)//Vérifie que la case est occupée par quelqu'un
    {
        for (int i =0; i<nbCiv_Jeu;i++ )
        {
            for (unsigned int j = 0; j<tabCiv_Jeu[i].getTabUnite().taille_utilisee;j++)
            {
                if (tabCiv_Jeu[i].getUniteDeTabUnite(j)->getposX()==x &&tabCiv_Jeu[i].getUniteDeTabUnite(j)->getposY()==y)
                {
                    return tabCiv_Jeu[i].getUniteDeTabUnite(j);
                }
            }
        }
    }
    if(plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).getDejaOccupe() == -1)
    {
        return NULL;
    }
    assert(0);
}

void Jeu :: DefinirProprioUnite()
{
    for (int i =0; i<nbCiv_Jeu;i++ )
    {
        for (unsigned int j = 0; j<tabCiv_Jeu[i].getTabUnite().taille_utilisee;j++)
        {
            tabCiv_Jeu[i].getUniteDeTabUnite(j)->setproprioUnite(i);
        }
     }
}

void Jeu :: DefinirCaseDejaOccupe(int x, int y)
{
    for (int i =0; i<nbCiv_Jeu;i++ )
    {
        for (unsigned int j = 0; j<tabCiv_Jeu[i].getTabUnite().taille_utilisee;j++)
        {
            if (tabCiv_Jeu[i].getUniteDeTabUnite(j)->getposX()==x && tabCiv_Jeu[i].getUniteDeTabUnite(j)->getposY()==y )
            {
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x,y).setDejaOccupe(i);
            }
        }
    }
}

void Jeu :: DefinirTouteCaseDejaOccupe()
{
    for (int x=0; x<plateau_Jeu->gettailleHorizontale();x++)//Defini les cases occupées par les unités et les met à jour
    {
        for (int y=0; y<plateau_Jeu->gettailleVerticale();y++)
        {
            DefinirCaseDejaOccupe(x,y);
        }
    }
}

void Jeu:: AttaqueUniteBombardement_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
{
    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité adans la direction voulue
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case voulue  est maintenant occupée par l'unité
        cout<<u->getPM()<<"PM"<<endl;
        if (u->getPM() == 0)
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setPM(u->getDST()); u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
        }
    }
    else if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()!= u->getproprioUnite()) //Si la case est occupé par un ennemi
    {
        //On bombarde l'unité en question
        Unite* u1 = GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j);
        Case& c2 = plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j);
        u->Bombarder_Unite(
                           u1,
                           c2
                           );

        if(GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j)->getPV()<=0) //Si l'unité ennemie est morte alors
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setDejaOccupe(-1);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());

            VerificationUnitesMortes_Jeu ();//On vérifie les unités mortes pour cleaner

             //Alors la case qu'occupe actuellement le soldat est inoccupée
            // u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité au nord
            //plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case du nord est maintenant occupée par l'unité
            ok2 = false;
        }
        else
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
            ok2=false;
        }
   }
    else if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()== u->getproprioUnite()) //Si la case est occupé par un ami
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->setposX(posXOrigine); u->setposY(posYOrigine);//On renvoi l'unité sur sa position d'origine
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//On occupe la case d'origine
    }
}

void Jeu:: AttaqueUniteAtomisation_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
{
        if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité adans la direction voulue
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case voulue  est maintenant occupée par l'unité
        cout<<u->getPM()<<"PM"<<endl;
        if (u->getPM() == 0)
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setPM(u->getDST()); u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
        }
    }
    else if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()!= u->getproprioUnite()) //Si la case est occupé par un ennemi
    {
        //On bombarde l'unité en question
        Unite* u1 = GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j);
        Case& c2 = plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j);

        for(int jj=c2.getY()-2 ; jj<c2.getY()+2 ; jj++)
        {//atomiser une zone assez large
            for(int ii=c2.getX()-2 ; ii<c2.getX()+2 ; ii++)
            {
                if( plateau_Jeu->GetCaseIDParCoordonnees_Plateau(ii,jj).getDejaOccupe() != -1 &&
                    plateau_Jeu->GetCaseIDParCoordonnees_Plateau(ii,jj).getDejaOccupe() != u1->getproprioUnite() )
                {
                    cout<<GetUniteParCoord_Jeu(ii,jj)->getnomUnite()<< " de la civilisation "
                    <<GetUniteParCoord_Jeu(ii,jj)->getproprioUnite()<<" , ";
                    u1 = GetUniteParCoord_Jeu(ii,jj);
                    c2 = plateau_Jeu->GetCaseIDParCoordonnees_Plateau(ii,jj);
                    u->Atomiser_Unite(u1,c2);
                }
            }
        }

        if(GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j)->getPV()<=0) //Si l'unité ennemie est morte alors
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setDejaOccupe(-1);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());

            VerificationUnitesMortes_Jeu ();//On vérifie les unités mortes pour cleaner

             //Alors la case qu'occupe actuellement le soldat est inoccupée
            // u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité au nord
            //plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case du nord est maintenant occupée par l'unité
            ok2 = false;
        }
        else
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
            ok2=false;
        }
   }
    else if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()== u->getproprioUnite()) //Si la case est occupé par un ami
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->setposX(posXOrigine); u->setposY(posYOrigine);//On renvoi l'unité sur sa position d'origine
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//On occupe la case d'origine
    }
}


void Jeu:: AttaqueUniteMelee_Jeu(int i, int j,Unite* u,char action, bool & ok)
{
     if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case visée est innocupée alors
     {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité au nord
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case du nord est maintenant occupée par l'unité
     }
    else if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()!=u->getproprioUnite()) //Si la case est occupé par un ennemi
    {
        //On affronte l'unité au nord
        Unite* u1 = GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j);//l'unité qu'on va attaquer
        Case& c2 = plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j);//la case sur laquelle se trouve l'ennemi
        u->Affronter_Unite(
                           u1,
                           c2
                           );

        if(GetUniteParCoord_Jeu(u->getposX()+i,u->getposY()+j)->getPV()<=0) //Si l'unité ennemie est morte alors
        {
            if (u->getPV()>0)//Si l'unité qui attaque est vivante
            {
                VerificationUnitesMortes_Jeu () ;//On vérifie les unités mortes pour cleaner
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité selon le choix
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case choisie est maintenant occupée par l'unité
                ok = false;
            }
            else // Si l'unité qui attaque est morte
            {
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//La case de l'attaquant est inoccupée car il est mort
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setDejaOccupe(-1);//La case de l'attaquée est inoccupée car il est mort
                VerificationUnitesMortes_Jeu();
                cout<<"Votre unite est morte lors d'une attaque heroique, il a réussi dans un ultime souffle a tuer l'ennemi egalement"<<endl;
                ok=false;
            }
        }
        else
        {
            if (u->getPV()<=0) // Si l'unité qui attaque est morte mais pas l'attaquée
                {
                     plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                     VerificationUnitesMortes_Jeu(); cout<<"Votre unite est morte lors d'une attaque heroique"<<endl;
                }
                ok=false;
        } //Si l'unité ennemie est en vie, alors le joueur ne se déplace pas
        u->setPM(0);
            //Faire une fonction qui défini l'ID des unités en fonction de leur place dans le tableau; En chaque début de tour cette fonction est appellée
    }
}

void Jeu:: DeplacementUnite_Jeu(int i, int j,Unite* u,char action)
{
    if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1 )//Si la case au nord est innocupée alors
    {
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité selon la direction choisie
        plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case choisie est maintenant occupée par l'unité
    }
}

void Jeu :: Acheter_Unite_Jeu(char action2, int x,int y,  int ID_Civ)
{
    bool ok3=true; int X=0,Y=0; // Booléen et entiers pour trouver un emplacement non occupé pour générer une unité
    while (ok3)
    {
        string position ="";
        if (y==0) {position = position+"Nord";}
        if (y==19) {position = position+"Sud";}
        if (x==0){ position = position+"Ouest";}
        if (x==39){position = position+"Est";}

        if (position =="Nord") {Y=Y+1;} if (position =="Ouest") {X=X+1;}
        if (position =="Sud") {Y=Y-1;} if (position =="Est") {X=X-1;}
        if (position =="NordOuest") {Y=Y+1;X=X+1;} if (position =="SudOuest") {X=X+1;Y=Y-1;}
        if (position =="SudEst") {Y=Y-1;X=X-1;} if (position =="NordEst") {X=X-1;Y=Y-1;}
        if (position=="" || position=="Ouest" )
        {
            if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X+1;
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

        if (position=="Nord")
        {
            if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X+1;
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

        if (position=="Est")
        {
            if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X-1;
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }
        if(position=="Sud")
        {
             if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }

        }
        if(position=="SudOuest")
        {
             if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }
        }
        if(position=="SudEst")
        {
             if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X-1;
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }
         if(position=="NordEst")
         {
             if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X-1;
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }
         }
         if(position=="NordOuest")
         {
             if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                 if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

     }
     switch(action2)
     {
        case 'c':
        {//Colon
            Unite *Colon= new Unite(1,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Colon);
            tabCiv_Jeu[ID_Civ].setNourritureCivilization(tabCiv_Jeu[ID_Civ].getNourritureCivilization()-50);
            break;
        }
        case 'h'://Hoplite
        {
            Unite *Hoplite= new Unite(2,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Hoplite);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-10);
            break;
         }

        case 'a'://Archer
        {
            Unite *Archer= new Unite(3,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Archer);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-15);
            break;
        }
        case 'm'://Hussard
        {
            Unite *Hussard= new Unite(4,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Hussard);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-25);
            break;
        }

        case 'k'://Canon
        {
            Unite *Canon= new Unite(5,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Canon);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-35);
            break;
        }
        case 't'://Tank
        {
            Unite *Tank= new Unite(6,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(Tank);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-150);
            break;
        }
        case 'l'://Lance missile
        {
            Unite *LanceMissile= new Unite(7,ID_Civ,x+X,y+Y);
            tabCiv_Jeu[ID_Civ].getTabUnite().AjouterElement(LanceMissile);
            tabCiv_Jeu[ID_Civ].setProductionCivilization(tabCiv_Jeu[ID_Civ].getProductionCivilization()-250);
            break;
        }
    }
}

Jeu::~Jeu()
{
    delete  plateau_Jeu;
    delete [] tabCiv_Jeu;
    cout<<"Le jeu est supprime (fin de la partie)"<<endl;
}

void Jeu :: ActionIA_Jeu(Unite * u, WinTXT & win, Civilization & Civ, char actionParam)
{

    bool ok;
    char action;
    bool mode=false;
    AffichTxt_Jeu(win, u, mode,0,0);

    if (u->gettypeUnite()==0)
    {//ville
        mode=false;
        action = actionParam;
        switch(action)
        {
            case 'c': //Colon
                if (Civ.getNourritureCivilization()>=50)
                {
                   Acheter_Unite_Jeu(action, u->getposX(),u->getposY(), Civ.getCivilizationID());
                }
                break;
            case 'h'://Hoplite
                if (Civ.getProductionCivilization()>10)
                {
                   Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;

            case 'a'://Archer
                 if (Civ.getProductionCivilization()>15)
                 {
                     Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                 }
                 break;

            case 'm'://Hussard
                 if (Civ.getProductionCivilization()>25)
                 {
                     Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                 }
                break;

            case 'k'://Canon
                if (Civ.getProductionCivilization()>35)
                {
                   Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;

            case 't'://Tank
                if (Civ.getProductionCivilization()>150)
                {
                   Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }

                break;

            case 'l'://Lance missile
                if (Civ.getProductionCivilization()>250)
                {
                   Acheter_Unite_Jeu(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }

                break;

            case 'f': //Cas ou le joueur ne veut plus acheter

                break;

        }
        u->setPM(0);
        AffichTxt_Jeu(win,u, mode,0,0);
    }
    if (u->gettypeUnite()==1) //Actions du colon
    {
        if(u->getPM()>=1)
        {
            action = actionParam;
            switch(action)
            {
                case 'w' :
                DeplacementUnite_Jeu(0,-1 ,u,action);

                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;

                case 'a' :
                DeplacementUnite_Jeu(-1,0 ,u,action);

                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;

                case 's' :
                DeplacementUnite_Jeu(0,1 ,u,action);

                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;

                case 'd' :
                DeplacementUnite_Jeu(1,0 ,u,action);

                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;

                case 'v':
                u->Fonder_Ville(action);
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setProprioCase(u->getproprioUnite());//Le proprio de la case prend la valeur de l'ID de la civilisation
                ok = false;
                break;

                case 'f':
                u->setPM(0);
                ok = false;
                break;
             }
             AffichTxt_Jeu(win,u, mode,0,0);
        }
    }

    if ((u->gettypeUnite()==2)or(u->gettypeUnite()==4)or(u->gettypeUnite()==6))//Actions des soldats de melees et du tank
    {
        if(u->getPM()>=1)
        {
            action = actionParam;

            switch(action)
            {
                 case 'w' :
                 AttaqueUniteMelee_Jeu(0,-1,u,action,ok);
                 if(u->getPM()==0)
                 {
                     ok = false;
                 }
                 break;

                 case 'a' :

                 AttaqueUniteMelee_Jeu(-1,0,u,action,ok);

                 if(u->getPM()==0)
                 {
                    ok = false;
                 }
                 break;

                 case 's' :

                 AttaqueUniteMelee_Jeu(0,1,u,action,ok);

                 if(u->getPM()==0)
                 {
                    ok = false;
                 }
                 break;

                 case 'd' :

                 AttaqueUniteMelee_Jeu(1,0,u,action,ok);

                 if(u->getPM()==0)
                 {
                    ok = false;
                 }
                 break;

                 case 'f':
                 u->setPM(0);
                 ok=false;
                 break;
            }
            AffichTxt_Jeu(win,u, mode,0,0);
        }
    }
    if ((u->gettypeUnite()==3)or(u->gettypeUnite()==5)or(u->gettypeUnite()==7))
    {

        if(u->getPM()>=1)
        {
            do {
                    mode=false;
                    action = actionParam;

                    AffichTxt_Jeu(win,u,mode,0,0);
                    switch(action)
                    {
                         case 'w' :
                         DeplacementUnite_Jeu(0,-1 ,u,action);
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;

                        case 'a' :
                        DeplacementUnite_Jeu(-1,0,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 's' :
                        DeplacementUnite_Jeu(0,1,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;

                        case 'd' :
                        DeplacementUnite_Jeu(1,0,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'f':
                        u->setPM(0);
                        ok=false;
                        break;
                    }
                }while(ok);
        }
    }
    if  (u->gettypeUnite()==8)
    {

    }
    AffichTxt_Jeu(win, u,mode,0,0);
}

void Jeu :: Acheter_Case_Jeu(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
{
    if (action=='w'|| action=='s' || action=='a' || action=='d' )
    {
        if (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->Deplacer_Unite(action,plateau_Jeu->gettailleHorizontale(),plateau_Jeu->gettailleVerticale());//On déplace l'unité adans la direction voulue
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case voulue  est maintenant occupée par l'unité
            cout<<u->getPM()<<"PM"<<endl;
            if (u->getPM() == 0)
            {
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                u->setPM(u->getDST()); u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
            }
        }
        else
        {
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
        }
    }
    if (action=='v')//ACTION POUR VALIDER L'ACHAT D'UNE CASE!
    {
            //Si la case n'a pas de proprio
           if  (plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getProprioCase()<0
                || plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getProprioCase()>=nbCiv_Jeu )
            {
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setProprioCase(u->getproprioUnite());//La case a maintenant le propri
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                u->setPM(0);
                ok2=false;
                cout<<"Case achetee"<<endl;
                tabCiv_Jeu[u->getproprioUnite()].setOrCivilization( tabCiv_Jeu[u->getproprioUnite()].getOrCivilization()-10 ); //Enleve 10 or lors de l'achat de case
            }
            else //SI il veut acheter une case déjà possédée par une IA
            {
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_Jeu->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                cout<<"Achat de case impossible"<<endl;
            }
    }
}
