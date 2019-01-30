
#include "Jeu_graphique.h"



//Sélectionne un nombre au hasard
int rand_a_b4(int a, int b){

    return rand()%(b-a) +a;
}

Jeu_graphique::Jeu_graphique(){};
Jeu_graphique::Jeu_graphique(int nbJoueur, string nomCiv_Jeu2)
{
    finDePartie_JeuGraphique = false;
    tour_JeuGraphique = 0;
    nomCiv_JeuGraphique = nomCiv_Jeu2;
    plateau_JeuGraphique = new Plateau(40,20);
    nbCiv_JeuGraphique = nbJoueur;
    tabCiv_JeuGraphique = new Civilization[nbCiv_JeuGraphique];
    tabCiv_JeuGraphique[0].setNomCivilization(nomCiv_Jeu2);
    for(int ID=0; ID<nbJoueur; ID++)
    {
        tabCiv_JeuGraphique[ID].setCivilizationID(ID);
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(tabCiv_JeuGraphique[ID].getUniteDeTabUnite(0)->getposX(),tabCiv_JeuGraphique[ID].getUniteDeTabUnite(0)->getposY()).setProprioCase(ID);
        //La case de la ville de depart a comme proprietaire l'ID de la civilisation
    }
}

void Jeu_graphique::Construction_JeuGraphique(int nbJoueur, string nomCiv_Jeu2)
{
    assert(nbJoueur>1);
    finDePartie_JeuGraphique = false;
    tour_JeuGraphique = 0;
    nomCiv_JeuGraphique = nomCiv_Jeu2;
    plateau_JeuGraphique = new Plateau(40,20);
    nbCiv_JeuGraphique = nbJoueur;
    tabCiv_JeuGraphique = new Civilization[nbCiv_JeuGraphique];
    tabCiv_JeuGraphique[0].setNomCivilization(nomCiv_Jeu2);
    for(int ID=0; ID<nbJoueur; ID++)
    {
        tabCiv_JeuGraphique[ID].setCivilizationID(ID);
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(tabCiv_JeuGraphique[ID].getUniteDeTabUnite(0)->getposX(),tabCiv_JeuGraphique[ID].getUniteDeTabUnite(0)->getposY()).setProprioCase(ID);
        //La case de la ville de depart a comme proprietaire l'ID de la civilisation
    }
}

void Jeu_graphique::RetablirPM_JeuGraphique(TableauDynamique & tabUnite)//A faire en debut de tour
{

    for (int j=0; j<nbCiv_JeuGraphique;j++)
    {//civilizations
        for(unsigned int i=0; i<tabCiv_JeuGraphique[j].getTabUnite().taille_utilisee;i++)
        {//unites
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==0){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(0);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==1){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==2){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==3){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(1);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==4){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(3);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==5){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(2);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==6){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(5);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==7){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(3);}
            if(tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->gettypeUnite()==8){tabCiv_JeuGraphique[j].getUniteDeTabUnite(i)->setPM(0);}
        }
    }
}

void Jeu_graphique::DistribuerRessource_JeuGraphique() //A faire en debut de tour
{
    int proprio;
    for(int i=0;i< plateau_JeuGraphique->gettailleHorizontale()* plateau_JeuGraphique->gettailleVerticale();i++)//parcourir toutes les cases
    {
        proprio =  plateau_JeuGraphique->GetCaseDeTabCase_Plateau(i).getProprioCase();
        if (proprio != -1) //avec -1 pas de proprio
        {
            tabCiv_JeuGraphique[proprio].setNourritureCivilization(tabCiv_JeuGraphique[proprio].getNourritureCivilization()+ plateau_JeuGraphique->GetCaseDeTabCase_Plateau(i).getNourritureParCase());
            tabCiv_JeuGraphique[proprio].setProductionCivilization(tabCiv_JeuGraphique[proprio].getProductionCivilization()+ plateau_JeuGraphique->GetCaseDeTabCase_Plateau(i).getProductionParCase());
            tabCiv_JeuGraphique[proprio].setOrCivilization(tabCiv_JeuGraphique[proprio].getOrCivilization()+ plateau_JeuGraphique->GetCaseDeTabCase_Plateau(i).getOrParCase());
            tabCiv_JeuGraphique[proprio].setscienceCivilization(tabCiv_JeuGraphique[proprio].getscience_Civilization()+ plateau_JeuGraphique->GetCaseDeTabCase_Plateau(i).getScienceParCase());
        }
    }
}

int Jeu_graphique::Action_JeuGraphique (char action,char action2, Unite * u, Civilization & Civ, sf::RenderWindow & window,
                   sf::View & view, sf::View & view2, sf::View & minimapView,sf::View & BarreRessource)
{
    assert(action>0 && action<256);
    assert(action2>0 && action2<256);
    assert(u->getproprioUnite()==0);
    bool ok = true;
    int mode=0;
    if (u->gettypeUnite()==0)
    {//ville
        do{
                bool ok2=true;
                switch(action)
                {
                    case 'f':
                    ok = false;
                    break;
                    case 'a'://Acheter une unité
                        mode=1;
                        ok2=true;
                        AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessource,0,mode);
                        while(ok2)
                        {
                            switch(action2)
                            {
                                case 'c': //Colon
                                    if (Civ.getNourritureCivilization()>=50)
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(),Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;

                                case 'h'://Hoplite
                                    if ((Civ.getProductionCivilization()>=10)&&(Civ.getage_Civilization()==1))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;
                                case 'a'://Archer
                                     if ((Civ.getProductionCivilization()>=15)&&(Civ.getage_Civilization()==1))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;
                                case 'm'://Hussard
                                    if ((Civ.getProductionCivilization()>=25)&&(Civ.getage_Civilization()==2))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;
                                case 'k'://Canon
                                    if ((Civ.getProductionCivilization()>=35)&&(Civ.getage_Civilization()==2))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;
                                case 't'://Tank
                                    if ((Civ.getProductionCivilization()>=150)&&(Civ.getage_Civilization()==3))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
                                    }
                                    ok2=false;
                                    break;
                                case 'l'://Lance missile
                                    if ((Civ.getProductionCivilization()>=250)&&(Civ.getage_Civilization()==3))
                                    {
                                       Acheter_Unite_JeuGraphique(action2, u->getposX(),u->getposY(), Civ.getCivilizationID());
                                       return 1;
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
                        sf::Event event3;
                        int PositionOrigineX = u->getposX(); int PositionOrigineY = u->getposY();//Position initial en x et y de l'unité
                        mode=2;
                        AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessource,0,mode);
                        ok2=true;
                        u->setDST(8);
                        u->setPM(8);//On met les PM de la ville à 8
                        while (window.pollEvent(event3) || ok2==true)
                        {
                            switch (event3.type)
                            {
                                case sf::Event::Closed:
                                window.close();
                                ok2=false;
                                break;
                                case sf::Event::KeyPressed:
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                {
                                    Acheter_Case_JeuGraphique(0,-1 ,u,'w',ok2,PositionOrigineX,PositionOrigineY );
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                                {
                                    Acheter_Case_JeuGraphique(-1,0 ,u,'a',ok2,PositionOrigineX,PositionOrigineY );
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                                {
                                    Acheter_Case_JeuGraphique(0,1 ,u,'s',ok2,PositionOrigineX,PositionOrigineY );
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                                {
                                    Acheter_Case_JeuGraphique(1,0 ,u,'d',ok2,PositionOrigineX,PositionOrigineY );
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                                {
                                    plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                                    plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    ok2=false;
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                                {
                                    if (Civ.getOrCivilization()>=10)
                                    {
                                        Acheter_Case_JeuGraphique(0,0,u,'v',ok2,PositionOrigineX,PositionOrigineY);
                                    }
                                }
                                break;
                                default:
                                break;
                            }
                            AffichGraph_JeuGraphique(window,u,view,view2,minimapView,BarreRessource,0,mode);
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
                    switch(action)
                    {
                        case 'w' :
                        DeplacementUnite_JeuGraphique(0,-1 ,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'a' :
                        DeplacementUnite_JeuGraphique(-1,0 ,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 's' :
                        DeplacementUnite_JeuGraphique(0,1 ,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'd' :
                        DeplacementUnite_JeuGraphique(1,0 ,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'v':
                        u->Fonder_Ville(action);
                        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setProprioCase(u->getproprioUnite());//Le proprio de la case prend la valeur de l'ID de la civilisation
                        ok = false;
                        u->setPM(0);
                        break;
                        case 'f':
                        ok = false;
                        break;
                     }
                }while (ok);
        }
    }
    if ((u->gettypeUnite()==2)or(u->gettypeUnite()==4)or(u->gettypeUnite()==6))//Actions des soldats de melees et du tank
    {
        if(u->getPM()>=1)
        {
            do {
                    switch(action)
                    {
                         case 'w' :
                         if(u->getposY()>0)
                         {
                            AttaqueUniteMelee_JeuGraphique(0,-1,u,action,ok);
                         }
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;
                         case 'a' :
                         if(u->getposX()>0)
                         {
                            AttaqueUniteMelee_JeuGraphique(-1,0,u,action,ok);
                         }
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;
                         case 's' :
                        if( u->getposY() <19)
                        {
                           AttaqueUniteMelee_JeuGraphique(0,1,u,action,ok);
                        }
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;
                         case 'd' :
                        if( u->getposX()< 39)
                        {
                            AttaqueUniteMelee_JeuGraphique(1,0,u,action,ok);
                        }
                         if(u->getPM()==0)
                         {
                            ok = false;
                         }
                         break;
                         case 'f':
                         ok=false;
                         break;
                    }

                    return 1;
                }while(ok);
        }
        return 1;
    }
    if ((u->gettypeUnite()==3)or(u->gettypeUnite()==5)or(u->gettypeUnite()==7))
    {//distance
         BACK://le goto est plus bas, lorsque le distance veut quitter le mode bombardement
          if(u->getPM()>=1)
          {
              do {
                    mode=0;
                    switch(action)
                    {
                         case 'w' :
                         DeplacementUnite_JeuGraphique(0,-1 ,u,action);return 1;
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;
                         case 'a' :
                         DeplacementUnite_JeuGraphique(-1,0,u,action);return 1;
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;
                        case 's' :
                        DeplacementUnite_JeuGraphique(0,1,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'd' :
                        DeplacementUnite_JeuGraphique(1,0,u,action);return 1;
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'f':
                        ok=false;
                        break;
                        case 'b' : //mode bombardement
                        sf::Event event3;
                        int PositionOrigineX = u->getposX(); int PositionOrigineY = u->getposY();//Position initial en x et y de l'unité
                        int PmOrigine = u->getPM();mode=1;
                        bool ok2=true;
                        u->setPM(u->getDST());
                        while (window.pollEvent(event3) || ok2==true)
                        {
                            switch (event3.type)
                            {
                                case sf::Event::Closed:
                                window.close();
                                ok2=false;
                                break;
                                case sf::Event::KeyPressed:
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                                {
                                    AttaqueUniteBombardement_JeuGraphique(0,-1 ,u,'w',ok2,PositionOrigineX,PositionOrigineY );

                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                                {
                                    AttaqueUniteBombardement_JeuGraphique(-1,0 ,u,'a',ok2,PositionOrigineX,PositionOrigineY);
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                                {
                                    AttaqueUniteBombardement_JeuGraphique(0,1 ,u,'s',ok2,PositionOrigineX,PositionOrigineY);
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                                {
                                    AttaqueUniteBombardement_JeuGraphique(1,0 ,u,'d',ok2,PositionOrigineX,PositionOrigineY);
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                                {
                                   plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                                    plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    ok2=false;
                                }
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
                                {
                                    plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                                    u->setposX(PositionOrigineX); u->setposY(PositionOrigineY); u->setPM(PmOrigine);
                                    plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                                    goto BACK;
                                }
                                break;
                                default:
                                break;
                            }
                                DefinirTouteCaseDejaOccupe_JeuGraphique();
                                VerificationUnitesMortes_JeuGraphique();
                                AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessource,0,mode);
                         }

                         plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(PositionOrigineX,PositionOrigineY).setDejaOccupe(-1);
                         u->setposX(PositionOrigineX); u->setposY(PositionOrigineY);
                         plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(PositionOrigineX,PositionOrigineY).setDejaOccupe(u->getproprioUnite());
                         u->setPM(PmOrigine);
                         ok = false;
                         break;
                     }
                  }while(ok);
          }
    }
    if  (u->gettypeUnite()==8)
    {

    }
 return 0;
}

void Jeu_graphique::VerificationUnitesMortes_JeuGraphique ()
{
    if(tour_JeuGraphique>1)
    {
        //Pour chaque civilisation on parcourt son tableau d'unités et on supprime ses unités mortes
        int compteurCivEnnemis=0; int compteurVillesAmis=0;
         for (int i =0; i<nbCiv_JeuGraphique;i++ )
         {
             for (unsigned int j = 0; j<tabCiv_JeuGraphique[i].getTabUnite().taille_utilisee;j++)
             {
                 if (tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->getPV()<=0)
                 {
                     tabCiv_JeuGraphique[i].getTabUnite().SupprimerElement(j);
                 }
             }
         }
         //Pour chaque civilisation, on compte son nombre de villes : Pour  les villes ennemis puis pour villes amis.
         for (int i =0; i<nbCiv_JeuGraphique;i++ )
         {
             for (unsigned int j = 0; j<tabCiv_JeuGraphique[i].getTabUnite().taille_utilisee;j++)
             {
                 if (i!=0)
                 {
                    if (tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->gettypeUnite()==0)
                    {
                        compteurCivEnnemis=compteurCivEnnemis+1;//Compteur qui s'incrémente que si un ennmi possède une ville
                    }
                 }
                 else
                 {
                     if (tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->gettypeUnite()==0)
                     {
                         compteurVillesAmis=compteurVillesAmis+1;//Compteur qui s'incrémente que si le joueur possède une ville
                     }
                 }
            }
         }
        if (compteurCivEnnemis==0)//Si le compteur CivEnnemi est à 0, cela signifie que les ennmis n'ont plus de ville, donc le joueur gagne
        {

            nbCiv_JeuGraphique=1; finDePartie_JeuGraphique=true;
        }
        if (compteurVillesAmis==0)
        {
            nbCiv_JeuGraphique=1; finDePartie_JeuGraphique=true;
        }
    }

}

void Jeu_graphique::AugmentationAge_JeuGraphique()
{
    for (int i =0; i<nbCiv_JeuGraphique;i++ )
    {
        if (tabCiv_JeuGraphique[i].getscience_Civilization()>=100)
        {
            if (tabCiv_JeuGraphique[i].getage_Civilization()!=2)
            {
                 tabCiv_JeuGraphique[i].setage_Civilization(2);
            }
        }
        if(tabCiv_JeuGraphique[i].getscience_Civilization()>=300)
        {
            if (tabCiv_JeuGraphique[i].getage_Civilization()!=3)
            {
                tabCiv_JeuGraphique[i].setage_Civilization(3);
            }
        }
    }
}

void Jeu_graphique::GestionTourGraph_JeuGraphique( sf::RenderWindow & window )
{

    /*Unite *BombeA = new Unite(6,0,20,10); //On cree une unite artificiellement pour les tests
    tabCiv_JeuGraphique[0].getTabUnite().AjouterElement(BombeA);
    */


    Intro.stop();
    MusiqueJeu.play();
    MusiqueJeu.setLoop(true);
    //VUE NUMERO 1
    sf::View view(sf::Vector2f(100, 100), sf::Vector2f(700, 700));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    VueX=5; VueY=5;

    //VUE NUMERO 2
    sf::View view2;
    view2.setViewport(sf::FloatRect(0, 0.88, 0.7,1));

    sf::View minimapView;
    minimapView.setViewport(sf::FloatRect(0.75, 0.75, 0.25f, 0.25f));

    sf::View BarreRessource;
    BarreRessource.setViewport(sf::FloatRect(0, 0, 1,0.08f));

    //TANT QUE LA FENETRE WINDOW EST OUVERTE :
     while (window.isOpen())
    {
        tour_JeuGraphique += 1;
        DefinirTouteCaseDejaOccupe_JeuGraphique ();
        VerificationUnitesMortes_JeuGraphique();
        DistribuerRessource_JeuGraphique();
        AugmentationAge_JeuGraphique();
        DefinirProprioUnite_JeuGraphique();

        for(int compteurTourCiv=0;compteurTourCiv<nbCiv_JeuGraphique;compteurTourCiv++)//tant que toutes les civ n'ont pas fini leur tour
        {
             if(compteurTourCiv == 0) //c'est au tour du joueur
             {
                 for(unsigned int compteurUniteCiv=0;compteurUniteCiv<tabCiv_JeuGraphique[0].getTabUnite().taille_utilisee;compteurUniteCiv++)
                 {//Parcourt toutes les unites de tabUnite du joueur
                    DeplacerCamera_JeuGraphique(view,view2,minimapView, BarreRessource,window,tabCiv_JeuGraphique[0].getUniteDeTabUnite(compteurUniteCiv));
                     //On passe en paramètre l'unité joué, l'affichage et la civilisation jouée
                     if (finDePartie_JeuGraphique==true){goto FINDEJEU;}//SI LES VILLES ENNEMIS SONT MORTES ALORS ON QUITTE LA BOUCLE

                 }
             }
             else
             {
                for(unsigned int compteurUniteCiv=0;compteurUniteCiv<tabCiv_JeuGraphique[compteurTourCiv].getTabUnite().taille_utilisee;compteurUniteCiv++)
                {
                    if (tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==0 || tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==8  )
                    {//on rajoute 1 PM si c'est une ville ou une bombe parce que ...
                        tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->setPM(1);
                    }
                    while(tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->getPM()>0 )
                    {
                        IA test;
                        test.Decision_IA(tabCiv_JeuGraphique[compteurTourCiv].getNourritureCivilization(),//int nourriture_Civilization
                                   tabCiv_JeuGraphique[compteurTourCiv].getProductionCivilization(),//int production_Civilization
                                   tabCiv_JeuGraphique[compteurTourCiv].getOrCivilization(),         //int or_Civilization
                                   tabCiv_JeuGraphique[compteurTourCiv].getscience_Civilization(),    //int science_Civilization
                                   tabCiv_JeuGraphique[compteurTourCiv].getage_Civilization(),         //int age_Civilization
                                   compteurTourCiv,                                          //int ID_Civilization
                                   plateau_JeuGraphique,                                          //const Plateau & plateau_JeuGraphique
                                   tabCiv_JeuGraphique[compteurTourCiv].getTabUnite(),            //const Civilization & tabUnite
                                   compteurUniteCiv                                      //int uniteSelectionnee
                                   );
                         char test2 = test.GetDecisionFinale_IA();
                         DefinirProprioUnite_JeuGraphique();
                         DefinirTouteCaseDejaOccupe_JeuGraphique ();
                         VerificationUnitesMortes_JeuGraphique();
                         if (finDePartie_JeuGraphique==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE
                         VerificationActionIA_JeuGraphique(test2,compteurTourCiv,compteurUniteCiv);
                         if (finDePartie_JeuGraphique==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE
                         ActionIA_JeuGraphique(tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv), tabCiv_JeuGraphique[compteurTourCiv],test2);
                         if (finDePartie_JeuGraphique==true){goto FINDEJEU;}//SI LE JOUEUR HUMAIN EST MORT ON QUITTE LA BOUCLE
                     }
                     if (tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==0 || tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->gettypeUnite()==8  )
                     {//si c'est une ville ou une bombe, on remet ses PM a 0 car on les a ajoutes plus haut
                         tabCiv_JeuGraphique[compteurTourCiv].getUniteDeTabUnite(compteurUniteCiv)->setPM(0);
                     }

                }//fin tour civ
              }
              RetablirPM_JeuGraphique(tabCiv_JeuGraphique[compteurTourCiv].getTabUnite());
              RetablirCaseNulle_JeuGraphique(compteurTourCiv);
            }

    }

FINDEJEU : MusiqueJeu.stop();Gagnant_JeuGraphique(window,view);
}

void Jeu_graphique::BombardementAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect)
{//detecte l'ennemi le plus proche pour le bombarder automatiquement
    assert(civSelect>0);
    assert(uniteSelect>-1);
    assert(tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->gettypeUnite()==3
           || tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->gettypeUnite()==5
           || tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->gettypeUnite()==7   );

    int posX = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getposX();
    int posY = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getposY();
    //detection de l'ennemi le plus proche, normalement a portee du distance
    int minimumDistanceX = tabCiv_JeuGraphique[0].getUniteDeTabUnite(0)->getposX();
    int minimumDistanceY = tabCiv_JeuGraphique[0].getUniteDeTabUnite(0)->getposY();
    int nouveauMinimumDistanceX;
    int nouveauMinimumDistanceY;
    int DistanceX = 60; int DistanceY=60; int DistanceXY=60;

    for(int j=0; j<plateau_JeuGraphique->gettailleVerticale();j++)
    {
        for(int i=0;i<plateau_JeuGraphique->gettailleHorizontale();i++)
        {
            if((plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != -1) &&
              (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != civSelect))
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
    int ATKdeMoi = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getATK();
    int PDVdeEnnemi = GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getPV();
    GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->setPV( PDVdeEnnemi - ATKdeMoi );

    cout<<"L'unite "<<tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getnomUnite()<<
    " de la civilisation "<<civSelect<<" vient d'attaquer "<< GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getnomUnite()
    << " de la civilisation "<<GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getproprioUnite()<<". Il lui reste "<<
    PDVdeEnnemi<<" PDV."<<endl;

    if( GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getPV() <= 0 )
    {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(minimumDistanceX,minimumDistanceY).setDejaOccupe(-1);
    }
    VerificationUnitesMortes_JeuGraphique();
}

void Jeu_graphique::AchatCaseAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect)
{
      assert(civSelect>0);
      assert(uniteSelect>-1);
      assert(tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->gettypeUnite()==0);

      //On détermine la pos x et y de l'unité puis on choisit aléatoire une pos x et y non loin de l'unité pour acheter une case
      int posUniteX = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getposX();
      int posUniteY = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getposY();
      int posXCase =  rand_a_b4(posUniteX-8, posUniteX+9);
      if(posXCase<0){posXCase=0;}
      if(posXCase>39){posXCase=39;}
      int posYCase =  rand_a_b4(posUniteY-8, posUniteY+9);
      if(posYCase<0){posYCase=0;}
      if(posYCase>19){posXCase=19;}

      if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(posXCase,posYCase).getProprioCase() == -1)
      {
          if (tabCiv_JeuGraphique[civSelect].getOrCivilization()>=10)
          {
              plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(posXCase,posYCase).setProprioCase(civSelect);
            tabCiv_JeuGraphique[civSelect].setOrCivilization(tabCiv_JeuGraphique[civSelect].getOrCivilization()-10);
            cout<<"La civilisation "<<civSelect<<" vient d'acheter une case en ("<<posXCase<<" , "<<posYCase<<")."<<endl;
          }
          else
          {
              cout<<"Pas assez d'or"<<endl;
          }
      }
      else
      {
          cout<<"Case déjà achetée, achat impossible"<<endl;
      }

}

void Jeu_graphique::AtomisationAutomatiqueIA_JeuGraphique(int civSelect, int uniteSelect)
{//detecte l'ennemi le plus proche pour l'atomiser automatiquement

    assert(civSelect>0);
    assert(uniteSelect>-1);
    assert(tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->gettypeUnite()==8);

    //detection de l'ennemi le plus proche, normalement a portee du distance
    int minimumDistanceX = tabCiv_JeuGraphique[0].getUniteDeTabUnite(0)->getposX();
    int minimumDistanceY = tabCiv_JeuGraphique[0].getUniteDeTabUnite(0)->getposY();
    int minimumDistance  = minimumDistanceX + minimumDistanceY * plateau_JeuGraphique->gettailleHorizontale();
    int nouveauMinimumDistanceX;
    int nouveauMinimumDistanceY;
    int nouveauMinimumDistance;

    for(int j=0; j<plateau_JeuGraphique->gettailleVerticale();j++)
    {
        for(int i=0;i<plateau_JeuGraphique->gettailleHorizontale();i++)
        {
            if((plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != -1) &&
              (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe() != civSelect))
            {
                nouveauMinimumDistanceX = i;
                nouveauMinimumDistanceY = j;
                nouveauMinimumDistance = i + j * plateau_JeuGraphique->gettailleHorizontale();
                if(nouveauMinimumDistance < minimumDistance)
                {
                    minimumDistanceX = nouveauMinimumDistanceX;
                    minimumDistanceY = nouveauMinimumDistanceY;
                    minimumDistance = nouveauMinimumDistance;
                }
            }
        }
    }
    //On a la position de l'ennemi le plus proche, maintenant il faut retrancher ses PV
    int ATKdeMoi = tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getATK();
    int PDVdeEnnemi = GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getPV();
    GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->setPV( PDVdeEnnemi - ATKdeMoi );

    cout<<"L'unite "<<tabCiv_JeuGraphique[civSelect].getUniteDeTabUnite(uniteSelect)->getnomUnite()<<
    " de la civilisation "<<civSelect<<" vient d'attaquer "<< GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getnomUnite()
    << " de la civilisation "<<GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getproprioUnite()<<". Il lui reste "<<
    PDVdeEnnemi<<" PDV."<<endl;

    if( GetUniteParCoord_JeuGraphique(minimumDistanceX,minimumDistanceY)->getPV() <= 0 )
    {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(minimumDistanceX,minimumDistanceY).setDejaOccupe(-1);
    }
    VerificationUnitesMortes_JeuGraphique();
}

void Jeu_graphique::VerificationActionIA_JeuGraphique(char & reponse, int civSelectionnee, int uniteSelectionnee)
{
    assert(civSelectionnee>0);
    assert(uniteSelectionnee>-1);
    assert(reponse<256 && reponse>0);

    if(reponse=='b')
    {//Lorsque une distance/bombe passe en mode bombardement/atomisation
    cout<<"Declenchement du mode bombardement d'une IA "<<endl;
        BombardementAutomatiqueIA_JeuGraphique(civSelectionnee, uniteSelectionnee);

        reponse = 'f';
    }
    if(reponse=='n')
    {
        cout<<"Declenchement du mode atomisation d'une IA"<<endl;
        //AtomisationAutomatiqueIA(civSelectionnee, uniteSelectionnee);

        reponse = 'f';
    }
    if(reponse=='c')
    {
        cout<<"Declenchement du mode achat de case d'une IA"<<endl;
        AchatCaseAutomatiqueIA_JeuGraphique(civSelectionnee, uniteSelectionnee);

        reponse = 'f';
    }

    //Teste si la case voulue est deja occupee, si oui on va ailleurs pour pas entrer en conflit
    int posUnite = tabCiv_JeuGraphique[civSelectionnee].getUniteDeTabUnite(uniteSelectionnee)->getposX() +
                   plateau_JeuGraphique->gettailleHorizontale() *
                   tabCiv_JeuGraphique[civSelectionnee].getUniteDeTabUnite(uniteSelectionnee)->getposY() ;
    int posUniteW = posUnite - plateau_JeuGraphique->gettailleHorizontale();
    int posUniteA = posUnite - 1;
    int posUniteS = posUnite + plateau_JeuGraphique->gettailleHorizontale();
    int posUniteD = posUnite + 1;

    int typeUnit = tabCiv_JeuGraphique[civSelectionnee].getUniteDeTabUnite(uniteSelectionnee)->gettypeUnite();

    if( (typeUnit == 2) || (typeUnit == 4) || (typeUnit == 6) )
    {//le melee va ou il veut sauf si c'est sur une unite alliee
        if( (reponse=='w') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteW).getDejaOccupe() == civSelectionnee ) )
        {
            reponse = 'a';
        }
        if( (reponse=='a') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteA).getDejaOccupe() == civSelectionnee ) )
        {
            reponse = 's';
        }
        if( (reponse=='s') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteS).getDejaOccupe() == civSelectionnee ) )
        {
            reponse = 'd';
        }
        if( (reponse=='d') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteD).getDejaOccupe() == civSelectionnee ) )
        {//si toutes les cases autour sont prises on attend
            reponse = 'f';
        }
    }
    if( ( (typeUnit == 3) || (typeUnit == 5) || (typeUnit == 7) ))
    {//le distance ne doit pas chevaucher les unites alliees ou ennemies, sauf s'il est en Mode Bombardement
    //IL FAUT IMPERATIVEMENT REGLER LE MODE BOMBARDEMENT, CAR LE CURSEUR EST OBLIGE DE CONTOURNER LES UNITES ALLIEES POUR B
        if( (reponse=='w') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteW).getDejaOccupe() != -1 ) )
        {
            reponse = 'a';
        }
        if( (reponse=='a') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteA).getDejaOccupe() != -1 ) )
        {
            reponse = 's';
        }
        if( (reponse=='s') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteS).getDejaOccupe() != -1 ) )
        {
            reponse = 'd';
        }
        if( (reponse=='d') && (plateau_JeuGraphique->GetCaseDeTabCase_Plateau(posUniteD).getDejaOccupe() != -1 ) )
        {//si toutes les cases autour sont prises on attend
            reponse = 'f';
        }
    }
}

void Jeu_graphique::RetablirCaseNulle_JeuGraphique(int x)// remettre a 0 les cases d'une civilisation quand celle-ci meurt
{
    assert(x>=0);

    int compteurVille = 0 ;
    for(unsigned int  j = 0; j<tabCiv_JeuGraphique[x].getTabUnite().taille_utilisee;j++)
    {
        if(tabCiv_JeuGraphique[x].getUniteDeTabUnite(j)->gettypeUnite()== 0)// 0 = ville
        {
            compteurVille+=1;
        }
    }
    if (compteurVille == 0)
    {
        for(int k = 0;k< plateau_JeuGraphique->gettailleHorizontale()* plateau_JeuGraphique->gettailleVerticale();k++)
        {
            if ( plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).getProprioCase() == x)
            {
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setProprioCase(-1);
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setDejaOccupe (-1);
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setOrParCase(0);
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setNourritureParCase(0);
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setScienceParCase(0);
                 plateau_JeuGraphique->GetCaseDeTabCase_Plateau(k).setProductionParCase(0);
            }
        }
    }
}

Civilization* Jeu_graphique::getTabCiv_JeuGraphique()
{
    return tabCiv_JeuGraphique;
}

//Retourne une Unite en fonction de ses coordonnées
Unite* Jeu_graphique::GetUniteParCoord_JeuGraphique(int x, int y)
{
    assert(x>=0 && x<=39);
    assert(y>=0 && y<=19);

    if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x,y).getDejaOccupe() != -1)//Vérifie que la case est occupée par quelqu'un
    {
        for (int i =0; i<nbCiv_JeuGraphique;i++ )
        {
            for (unsigned int j = 0; j<tabCiv_JeuGraphique[i].getTabUnite().taille_utilisee;j++)
            {
                if (tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->getposX()==x &&tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->getposY()==y)
                {
                    return tabCiv_JeuGraphique[i].getUniteDeTabUnite(j);
                }
            }
        }
    }

    assert(0);
}

void Jeu_graphique :: DefinirProprioUnite_JeuGraphique()
{

    for (int i =0; i<nbCiv_JeuGraphique;i++ )
    {
        for (unsigned int j = 0; j<tabCiv_JeuGraphique[i].getTabUnite().taille_utilisee;j++)
        {
            tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->setproprioUnite(i);
        }
     }
}


void Jeu_graphique :: DefinirCaseDejaOccupe_JeuGraphique(int x, int y)
{
    assert(x>=0 && x<=39);
    assert(y>=0 && y<=19);

    for (int i =0; i<nbCiv_JeuGraphique;i++ )
    {
        for (unsigned int j = 0; j<tabCiv_JeuGraphique[i].getTabUnite().taille_utilisee;j++)
        {
            if (tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->getposX()==x && tabCiv_JeuGraphique[i].getUniteDeTabUnite(j)->getposY()==y )
            {
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x,y).setDejaOccupe(i);
            }
        }
    }
}

void Jeu_graphique :: DefinirTouteCaseDejaOccupe_JeuGraphique()
{

    for (int x=0; x<plateau_JeuGraphique->gettailleHorizontale();x++)//Defini les cases occupées par les unités et les met à jour
    {
        for (int y=0; y<plateau_JeuGraphique->gettailleVerticale();y++)
        {
            DefinirCaseDejaOccupe_JeuGraphique(x,y);
        }
    }
}

void Jeu_graphique:: AttaqueUniteBombardement_JeuGraphique(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
{
    assert(posXOrigine>=0 && posXOrigine<=39);
    assert(posYOrigine>=0 && posYOrigine<=19);
    assert(i<=1 && i>=-1);assert(j<=1 && j>=-1);
    assert(action>0 && action<256);
    assert(ok2 == true || ok2 == false);
    assert(u->gettypeUnite()==3 || u->gettypeUnite()==5 || u->gettypeUnite()==7   );


    if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
    {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité adans la direction voulue
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case voulue  est maintenant occupée par l'unité
        cout<<u->getPM()<<"PM"<<endl;
        if (u->getPM() == 0)
        {
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setPM(u->getDST()); u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
        }
    }
    else if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()!= u->getproprioUnite()) //Si la case est occupé par un ennemi
    {
        //On bombarde l'unité en question
        Unite* u1 = GetUniteParCoord_JeuGraphique(u->getposX()+i,u->getposY()+j);
        Case& c2 = plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j);
        u->Bombarder_Unite(
                           u1,
                           c2
                           );

        if(GetUniteParCoord_JeuGraphique(u->getposX()+i,u->getposY()+j)->getPV()<=0) //Si l'unité ennemie est morte alors
        {
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setDejaOccupe(-1);
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());

            VerificationUnitesMortes_JeuGraphique ();//On vérifie les unités mortes pour cleaner

             //Alors la case qu'occupe actuellement le soldat est inoccupée
            // u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité au nord
            //plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case du nord est maintenant occupée par l'unité
            ok2 = false;
        }
        else
        {
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
            ok2=false;
        }
   }
    else if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()== u->getproprioUnite()) //Si la case est occupé par un ami
    {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->setposX(posXOrigine); u->setposY(posYOrigine);//On renvoi l'unité sur sa position d'origine
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//On occupe la case d'origine
    }
}

void Jeu_graphique:: AttaqueUniteMelee_JeuGraphique(int i, int j,Unite* u,char action, bool & ok)
{
    assert(i<=1 && i>=-1);assert(j<=1 && j>=-1);
    assert(action>0 && action<256);
    assert(ok == true || ok == false);
    assert(u->gettypeUnite()==2 || u->gettypeUnite()==4 || u->gettypeUnite()==6   );

     if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case visée est innocupée alors
     {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité au nord
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case du nord est maintenant occupée par l'unité

     }
    else if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()!=u->getproprioUnite()) //Si la case est occupé par un ennemi
    {
        //On affronte l'unité au nord
        Unite* u1 = GetUniteParCoord_JeuGraphique(u->getposX()+i,u->getposY()+j);
        Case& c2 = plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j);
        u->Affronter_Unite(
                           u1,
                           c2
                           );
        if(GetUniteParCoord_JeuGraphique(u->getposX()+i,u->getposY()+j)->getPV()<=0) //Si l'unité ennemie est morte alors
        {
            if (u->getPV()>0)//Si l'unité qui attaque est vivante
            {
                VerificationUnitesMortes_JeuGraphique () ;//On vérifie les unités mortes pour cleaner
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité selon le choix
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case choisie est maintenant occupée par l'unité
                ok = false;

            }
            else // Si l'unité qui attaque est morte et l'attaquée aussi
            {
                VerificationUnitesMortes_JeuGraphique();
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//La case de l'attaquant est inoccupée car il est mort
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setDejaOccupe(-1);//La case de l'attaquée est inoccupée car il est mort

                cout<<"Votre unite est morte lors d'une attaque heroique, il a réussi dans un ultime souffle a tuer l'ennemi egalement"<<endl;
                ok=false;
            }
        }
        else
        {
            if (u->getPV()<=0) // Si l'unité qui attaque est morte mais pas l'attaquée
                {
                     plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                     VerificationUnitesMortes_JeuGraphique(); cout<<"Votre unite est morte lors d'une attaque heroique"<<endl;
                }
                ok=false;
        } //Si l'unité ennemie est en vie, alors le joueur ne se déplace pas

        u->setPM(0);
            //Faire une fonction qui défini l'ID des unités en fonction de leur place dans le tableau; En chaque début de tour cette fonction est appellée
    }
}

void Jeu_graphique:: DeplacementUnite_JeuGraphique(int i, int j,Unite* u,char action)
{
    assert(i<=1 && i>=-1);
    assert(j<=1 && j>=-1);
    assert(u->gettypeUnite()>0 && u->gettypeUnite()<9);
    assert(action>0 && action<256);

    if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
    {
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
        u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité selon la direction choisie
        plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case choisie est maintenant occupée par l'unité
    }
}


void Jeu_graphique :: Acheter_Unite_JeuGraphique(char action2, int x,int y,  int ID_Civ)
{
    assert(action2>0 && action2<256);
    assert(x>=0 && x<40);
    assert(y>=0 && y<20);
    assert(ID_Civ>-1);


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
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X+1;
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

        if (position=="Nord")
        {
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X+1;
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

        if (position=="Est")
        {
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
            else
            {
                X=X-1;
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }
        if(position=="Sud")
        {
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }

        }
        if(position=="SudOuest")
        {
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }
        }
        if(position=="SudEst")
        {
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X-1;
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y-1;}
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }
         if(position=="NordEst")
         {
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X-1;
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
             }
         }
         if(position=="NordOuest")
         {
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X<39) {ok3=false;}
             else
             {
                 X=X+1;
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()>=0 && x+X==39) {Y=Y+1;}
                 if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y+Y).getDejaOccupe()<0 && x+X==39) {ok3=false;}
            }
        }

        /*if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(x+X,y).getDejaOccupe()<0 && x+X<40) {ok3=false;}
        else {X=X+1;}*/
     }
     switch(action2)
     {
        case 'c':
        {//Colon
            Unite *Colon= new Unite(1,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Colon);
            tabCiv_JeuGraphique[ID_Civ].setNourritureCivilization(tabCiv_JeuGraphique[ID_Civ].getNourritureCivilization()-50);
            break;
        }
        case 'g':
        {//Colon
            Unite *Colon= new Unite(1,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Colon);
            tabCiv_JeuGraphique[ID_Civ].setNourritureCivilization(tabCiv_JeuGraphique[ID_Civ].getNourritureCivilization()-50);
            break;
        }
        case 'h'://Hoplite
        {
            Unite *Hoplite= new Unite(2,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Hoplite);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-10);
            break;
         }

        case 'a'://Archer
        {
            Unite *Archer= new Unite(3,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Archer);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-15);
            break;
        }
        case 'm'://Hussard
        {
            Unite *Hussard= new Unite(4,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Hussard);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-25);
            break;
        }

        case 'k'://Canon
        {
            Unite *Canon= new Unite(5,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Canon);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-35);
            break;
        }
        case 't'://Tank
        {
            Unite *Tank= new Unite(6,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(Tank);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-150);
            break;
        }
        case 'l'://Lance missile
        {
            Unite *LanceMissile= new Unite(7,ID_Civ,x+X,y+Y);
            tabCiv_JeuGraphique[ID_Civ].getTabUnite().AjouterElement(LanceMissile);
            tabCiv_JeuGraphique[ID_Civ].setProductionCivilization(tabCiv_JeuGraphique[ID_Civ].getProductionCivilization()-250);
            break;
        }
    }
}

Jeu_graphique::~Jeu_graphique()
{

    delete  plateau_JeuGraphique;
    plateau_JeuGraphique=NULL;
    delete [] tabCiv_JeuGraphique;
    tabCiv_JeuGraphique=NULL;
    cout<<"Le jeu est supprime (fin de la partie)"<<endl;
}

void Jeu_graphique :: ActionIA_JeuGraphique(Unite * u, Civilization & Civ, char actionParam)
{

    assert(u->gettypeUnite()>-1);
    assert(Civ.getCivilizationID()>0);
    assert(actionParam>0 && actionParam<256);

    bool ok;
    char action;
    if (u->gettypeUnite()==0)
    {//ville

        action = actionParam;
        switch(action)
        {
            case 'g': //Colon
                if (Civ.getNourritureCivilization()>=50)
                {
                   Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(), Civ.getCivilizationID());
                }
                break;
            case 'h'://Hoplite
                if (Civ.getProductionCivilization()>=10)
                {
                   Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;

            case 'a'://Archer
                 if (Civ.getProductionCivilization()>=15)
                 {
                     Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                 }
                 break;
            case 'm'://Hussard
                 if (Civ.getProductionCivilization()>=25)
                 {
                     Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                 }
                break;
            case 'k'://Canon
                if (Civ.getProductionCivilization()>=35)
                {
                   Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;
            case 't'://Tank
                if (Civ.getProductionCivilization()>=150)
                {
                   Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;
            case 'l'://Lance missile
                if (Civ.getProductionCivilization()>=250)
                {
                   Acheter_Unite_JeuGraphique(action, u->getposX(),u->getposY(),  Civ.getCivilizationID());
                }
                break;
            case 'f': //Cas ou le joueur ne veut plus acheter
                break;
        }
        u->setPM(0);
    }
    if (u->gettypeUnite()==1) //Actions du colon
    {
        if(u->getPM()>=1)
        {
            action = actionParam;
            switch(action)
            {
                case 'w' :
                DeplacementUnite_JeuGraphique(0,-1 ,u,action);

                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;
                case 'a' :
                DeplacementUnite_JeuGraphique(-1,0 ,u,action);
                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;
                case 's' :
                DeplacementUnite_JeuGraphique(0,1 ,u,action);
                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;
                case 'd' :
                DeplacementUnite_JeuGraphique(1,0 ,u,action);
                if(u->getPM()==0)
                {
                    ok = false;
                }
                break;
                case 'v':
                u->Fonder_Ville(action);
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setProprioCase(u->getproprioUnite());//Le proprio de la case prend la valeur de l'ID de la civilisation
                ok = false;
                break;
                case 'f':
                u->setPM(0);
                ok = false;
                break;
             }
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
                 AttaqueUniteMelee_JeuGraphique(0,-1,u,action,ok);
                 if(u->getPM()==0)
                 {
                     ok = false;
                 }
                 break;
                 case 'a' :
                 AttaqueUniteMelee_JeuGraphique(-1,0,u,action,ok);
                 if(u->getPM()==0)
                 {
                    ok = false;
                 }
                 break;
                 case 's' :
                 AttaqueUniteMelee_JeuGraphique(0,1,u,action,ok);
                 if(u->getPM()==0)
                 {
                    ok = false;
                 }
                 break;
                 case 'd' :
                 AttaqueUniteMelee_JeuGraphique(1,0,u,action,ok);
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
        }
    }
    if ((u->gettypeUnite()==3)or(u->gettypeUnite()==5)or(u->gettypeUnite()==7))
    {
        if(u->getPM()>=1)
        {
            do {
                    action = actionParam;
                    switch(action)
                    {
                         case 'w' :
                         DeplacementUnite_JeuGraphique(0,-1 ,u,action);
                         if(u->getPM()==0)
                         {
                             ok = false;
                         }
                         break;
                        case 'a' :
                        DeplacementUnite_JeuGraphique(-1,0,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 's' :
                        DeplacementUnite_JeuGraphique(0,1,u,action);
                        if(u->getPM()==0)
                        {
                            ok = false;
                        }
                        break;
                        case 'd' :
                        DeplacementUnite_JeuGraphique(1,0,u,action);
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
}

void Jeu_graphique :: Acheter_Case_JeuGraphique(int i, int j,Unite* u,char action, bool & ok2, int posXOrigine, int posYOrigine)
{
    assert(i<=1 && i>=-1);
    assert(j<=1 && j>=-1);
    assert(u->gettypeUnite()==0);
    assert(action>0 && action<256);
    assert(ok2 == true || ok2 == false);
    assert(posXOrigine>=0 && posXOrigine<40);
    assert(posYOrigine>=0 && posYOrigine<20);

    if (action=='w'|| action=='s' || action=='a' || action=='d' )
    {
        if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getDejaOccupe()==-1)//Si la case au nord est innocupée alors
        {
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->Deplacer_Unite(action,plateau_JeuGraphique->gettailleHorizontale(),plateau_JeuGraphique->gettailleVerticale());//On déplace l'unité adans la direction voulue
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());//La case voulue  est maintenant occupée par l'unité
            cout<<u->getPM()<<"PM"<<endl;
            if (u->getPM() == 0)
            {
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);
                u->setPM(u->getDST()); u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
            }
        }
        else
        {
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
            u->setposX(posXOrigine); u->setposY(posYOrigine);
            plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
        }
    }
    if (action=='v')//ACTION POUR VALIDER L'ACHAT D'UNE CASE!
    {
            //Si la case n'a pas de proprio
           if  (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getProprioCase()<0
                || plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).getProprioCase()>=nbCiv_JeuGraphique )
            {
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX()+i,u->getposY()+j).setProprioCase(u->getproprioUnite());//La case a maintenant le propri
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                u->setPM(0);
                ok2=false;
                cout<<"Case achetee"<<endl;
                tabCiv_JeuGraphique[u->getproprioUnite()].setOrCivilization( tabCiv_JeuGraphique[u->getproprioUnite()].getOrCivilization()-10 ); //Enleve 10 or lors de l'achat de case
            }
            else //SI il veut acheter une case déjà possédée par une IA
            {
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(-1);//Alors la case qu'occupe actuellement le soldat est inoccupée
                u->setposX(posXOrigine); u->setposY(posYOrigine);
                plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(u->getposX(),u->getposY()).setDejaOccupe(u->getproprioUnite());
                cout<<"Achat de case impossible"<<endl;
            }
    }
}

//------------------------------------------FONCTION LIEES A l'AFFICHAGE GRAPHIQUE-------------------------------//

//---------------------------------------------------------------------------------------------------------------//


void Jeu_graphique:: AffichGraph_JeuGraphique ( sf::RenderWindow & window, Unite*u, sf::View  view, sf::View  view2, sf::View & minimapView, sf::View & BarreRessource
                                      ,int BougeCamera, int mode)
{

    assert(mode>=0 && mode<=4);

    window.clear();
    if (BougeCamera==0)
    {
        VueX=u->getposX()*60;VueY=u->getposY()*60;
        view.setCenter(VueX,VueY);
        minimapView.setCenter(VueX,VueY);
    }
    view.setCenter(VueX,VueY);
    window.setView(view);
    for (int j=0; j<plateau_JeuGraphique->gettailleVerticale(); j++)
    {
        for (int i=0; i<plateau_JeuGraphique->gettailleHorizontale(); i++)
        {
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getTypeCase()==0)
            {
                spriteOcean.setPosition(sf::Vector2f(i*60, j*60));
                window.draw(spriteOcean);
            }
            else
            {
                spriteTerre.setPosition(sf::Vector2f(i*60,j*60));
                window.draw(spriteTerre);
            }
            if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getProprioCase()==0)
            {
                    spriteCasePossedeeAmi.setPosition(sf::Vector2f(i*60,j*60));
                    window.draw(spriteCasePossedeeAmi);
            }
            if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getProprioCase()>0)
            {
                    spriteCasePossedeeEnnemi.setPosition(sf::Vector2f(i*60,j*60));
                    window.draw(spriteCasePossedeeEnnemi);
            }
             if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe()>-1)
            {
                if (GetUniteParCoord_JeuGraphique(i,j)->getproprioUnite()==0)
                {
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()==0)
                    {
                        spriteVilleAmi.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteVilleAmi);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 1)
                    {
                        spriteColon.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteColon);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 2)
                    {
                        spriteHoplite.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHoplite);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 3)
                    {
                        spriteArcher.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteArcher);
                    }
                     if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 4)
                    {
                        spriteHussard.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHussard);
                    }
                     if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 5)
                    {
                        spriteCanon.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCanon);
                    }
                     if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 6)
                    {
                        spriteChar.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteChar);
                    }
                     if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 7)
                    {
                        spriteLM.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteLM);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 8)
                    {
                        spriteBombeAmi.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteBombeAmi);
                    }
                }
                else
                {
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()==0 )
                    {
                        spriteVilleEnnemi.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteVilleEnnemi);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 1)
                    {
                        spriteColonE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteColonE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 2)
                    {
                        spriteHopliteE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHopliteE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 3)
                    {
                        spriteArcherE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteArcherE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 4)
                    {
                        spriteHussardE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHussardE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 5)
                    {
                        spriteCanonE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCanonE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 6)
                    {
                        spriteCharE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCharE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 7)
                    {
                        spriteLME.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteLME);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 8)
                    {
                        spriteBombeE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteBombeE);
                    }
                }
            }
        }
    }
    window.setView(minimapView);
    for (int j=0; j<plateau_JeuGraphique->gettailleVerticale(); j++)
    {
        for (int i=0; i<plateau_JeuGraphique->gettailleHorizontale(); i++)
        {
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getTypeCase()==0)
            {
                spriteOcean.setPosition(sf::Vector2f(i*60, j*60));
                window.draw(spriteOcean);
            }
            else
            {
                spriteTerre.setPosition(sf::Vector2f(i*60,j*60));
                window.draw(spriteTerre);
            }
            if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getProprioCase()==0)
            {
                    spriteCasePossedeeAmi.setPosition(sf::Vector2f(i*60,j*60));
                    window.draw(spriteCasePossedeeAmi);
            }
            if(plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getProprioCase()>0)
            {
                    spriteCasePossedeeEnnemi.setPosition(sf::Vector2f(i*60,j*60));
                    window.draw(spriteCasePossedeeEnnemi);
            }
            if (plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(i,j).getDejaOccupe()>-1)
            {
                if (GetUniteParCoord_JeuGraphique(i,j)->getproprioUnite()==0)
                {
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()==0)
                    {
                        spriteVilleAmi.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteVilleAmi);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 1)
                    {
                        spriteColon.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteColon);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 2)
                    {
                        spriteHoplite.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHoplite);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 3)
                    {
                        spriteArcher.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteArcher);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 4)
                    {
                        spriteHussard.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHussard);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 5)
                    {
                        spriteCanon.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCanon);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 6)
                    {
                        spriteChar.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteChar);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 7)
                    {
                        spriteLM.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteLM);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 8)
                    {
                        spriteBombeAmi.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteBombeAmi);
                    }
                }
                else
                {
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()==0 )
                    {
                    spriteVilleEnnemi.setPosition(sf::Vector2f(i*60,j*60));
                    window.draw(spriteVilleEnnemi);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 1)
                    {
                        spriteColonE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteColonE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 2)
                    {
                        spriteHopliteE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHopliteE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 3)
                    {
                        spriteArcherE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteArcherE);
                    }
                     if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 4)
                    {
                        spriteHussardE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteHussardE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 5)
                    {
                        spriteCanonE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCanonE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 6)
                    {
                        spriteCharE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteCharE);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 7)
                    {
                        spriteLME.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteLME);
                    }
                    if (GetUniteParCoord_JeuGraphique(i,j)->gettypeUnite()== 8)
                    {
                        spriteBombeE.setPosition(sf::Vector2f(i*60,j*60));
                        window.draw(spriteBombeE);
                    }
                }
            }
        }
    }
    window.setView(view2);
    window.draw(spriteFond);
    string RecupPM = ConvertisseurIntEnString_JeuGraphique(u->getPM());
    string RecupPV =  ConvertisseurIntEnString_JeuGraphique(u->getPV());
    PM_PV.setString("PM: " + RecupPM + " PV : " + RecupPV);
    PM_PV.setPosition(400,0);
    if (u->gettypeUnite()==0)
    {
        if(mode==0)
        {
        window.draw(text);
        window.draw(PM_PV);
        window.setView(view);
        }
        if(mode==1 && tabCiv_JeuGraphique[0].getage_Civilization()==1)
        {
            window.draw(textAchatUAgeI);
            window.setView(view);
        }
        if(mode==1 && tabCiv_JeuGraphique[0].getage_Civilization()==2)
        {
            window.draw(textAchatUAgeII);
            window.setView(view);
        }
        if(mode==1 && tabCiv_JeuGraphique[0].getage_Civilization()==3)
        {
            window.draw(textAchatUAgeIII);
            window.setView(view);
        }
        if(mode==2)
        {
            window.draw(textAchatC);
            window.setView(view);
        }
    }
    if (u->gettypeUnite()==1)
    {

        window.draw(text1);
        window.draw(PM_PV);
        window.setView(view);
    }
    if (u->gettypeUnite()==2)
    {
        window.draw(text2);
        window.draw(PM_PV);
        window.setView(view);
    }
    if (u->gettypeUnite()==3)
    {
        if(mode==0)
        {
        window.draw(text3);
        window.draw(PM_PV);
        window.setView(view);
        }
        if(mode==1)
        {
            window.draw(textModeB);
            window.setView(view);
        }
    }
    if (u->gettypeUnite()==4)
    {
        window.draw(text4);
        window.draw(PM_PV);
        window.setView(view);
    }
    if (u->gettypeUnite()==5)
    {

     if(mode==0)
        {
        window.draw(text5);
        window.draw(PM_PV);
        window.setView(view);
        }
        if(mode==1)
        {
            window.draw(textModeB);
            window.draw(PM_PV);
            window.setView(view);
        }
    }
    if (u->gettypeUnite()==6)
    {
        window.draw(text6);
        window.draw(PM_PV);
        window.setView(view);
    }
    if (u->gettypeUnite()==7)
    {
    if(mode==0)
        {
            window.draw(text7);
            window.draw(PM_PV);
            window.setView(view);
        }
        if(mode==1)
        {
            window.draw(textModeB);
            window.setView(view);
        }
    }
    if (u->gettypeUnite()==8)
    {
        window.draw(text8);

        window.draw(PM_PV);
        window.setView(view);
    }
    window.setView(BarreRessource);
    window.draw(spriteFond2);
    window.draw(spriteOr);
    window.draw(spriteProd);
    if (tabCiv_JeuGraphique[0].getage_Civilization()==1)
    {
        window.draw(spriteScience);
    }
    if (tabCiv_JeuGraphique[0].getage_Civilization()==2)
    {
         window.draw(spriteScienceAge2);
    }
    if (tabCiv_JeuGraphique[0].getage_Civilization()==3)
    {
         window.draw(spriteScienceAge3);
    }
    window.draw(spriteNourriture);
    //Affichage des ressources :
    string RecupNourriture = ConvertisseurIntEnString_JeuGraphique(tabCiv_JeuGraphique[0].getNourritureCivilization());
    valeurNouriture.setString(RecupNourriture);
    valeurNouriture.setPosition(140,120);
    valeurNouriture.setScale(0.8f, 8);
    window.draw(valeurNouriture);

   std::string RecupScience = ConvertisseurIntEnString_JeuGraphique(tabCiv_JeuGraphique[0].getscience_Civilization());
    valeurScience.setString(RecupScience);
    valeurScience.setPosition(840,120);
    valeurScience.setScale(0.8f, 8);
    window.draw(valeurScience);

    std::string RecupOr = ConvertisseurIntEnString_JeuGraphique(tabCiv_JeuGraphique[0].getOrCivilization());
    valeurOr.setString(RecupOr);
    valeurOr.setPosition(620,120);
    valeurOr.setScale(0.8f, 8);
    window.draw(valeurOr);

    std::string RecupProd = ConvertisseurIntEnString_JeuGraphique(tabCiv_JeuGraphique[0].getProductionCivilization());
    valeurProd.setString(RecupProd);
    valeurProd.setPosition(380,120);
    valeurProd.setScale(0.8f, 8);
    window.draw(valeurProd);

    std::string RecupTour = ConvertisseurIntEnString_JeuGraphique(tour_JeuGraphique);
    valeurTour.setString(RecupTour);
    valeurTour.setPosition(0,0);
    valeurTour.setScale(0.8f, 8);
    window.draw(valeurTour);

    window.setView(view);
    window.display();
}

void Jeu_graphique :: ChargerPoliceTexture_JeuGraphique()
{

    //Chargement du font :
    font.loadFromFile("data/font/Trajan.otf");
    font2.loadFromFile("data/font/Triforce.ttf");
    text.setCharacterSize(30);text1.setCharacterSize(30);text2.setCharacterSize(30);text3.setCharacterSize(30);
    text4.setCharacterSize(30);text5.setCharacterSize(30);text6.setCharacterSize(30);text7.setCharacterSize(30);
    text8.setCharacterSize(30);valeurNouriture.setCharacterSize(80);valeurScience.setCharacterSize(80);
    valeurProd.setCharacterSize(80);valeurOr.setCharacterSize(80);valeurTour.setCharacterSize(80);
    textAchatC.setCharacterSize(30);textAchatUAgeI.setCharacterSize(30);textAchatUAgeII.setCharacterSize(30);
    textAchatUAgeIII.setCharacterSize(30);textModeB.setCharacterSize(30);
    PM_PV.setCharacterSize(30);

   //Musiques
    buffer.loadFromFile("data/musique/intro.ogg");
    Intro.setBuffer(buffer);

    buffer2.loadFromFile("data/musique/defaite.ogg");
    Defaite.setBuffer(buffer2);

    buffer3.loadFromFile("data/musique/jeufond.ogg");
    MusiqueJeu.setBuffer(buffer3);

    buffer4.loadFromFile("data/musique/victoire.ogg");
    Victoire.setBuffer(buffer4);

    // choix de la police à utiliser
    text.setFont(font); // font est un sf::Font
    PM_PV.setFont(font);
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);
    text4.setFont(font);
    text5.setFont(font);
    text6.setFont(font);
    text7.setFont(font);
    text8.setFont(font);

    textAchatC.setFont(font);
    textAchatUAgeI.setFont(font);
    textAchatUAgeII.setFont(font);
    textAchatUAgeIII.setFont(font);
    textModeB.setFont(font);
    valeurNouriture.setFont(font);
    valeurNouriture.setColor(sf::Color::Black);
    valeurOr.setFont(font);
    valeurOr.setColor(sf::Color::Black);
    valeurScience.setFont(font);
    valeurScience.setColor(sf::Color::Black);
    valeurProd.setFont(font);
    valeurProd.setColor(sf::Color::Black);
    valeurTour.setFont(font2);
    valeurTour.setColor(sf::Color::Blue);

    // choix de la chaîne de caractères à afficher
    text.setString("Unite jouee : Ville \n (a-MODE ACHAT UNITE ) (c-MODE ACHAT CASE)\n (f-PASSER )");

    text1.setString("Unite jouee : Colon \n ( w,s,a,d-DEPLACER / f-PASSER / v-FONDER UNE VILLE ) ");

    text2.setString("Unite jouee : Hoplite \n ( w,s,a,d-DEPLACER OU ATTAQUER / f-PASSER )");

    text3.setString("Unite jouee : Archer \n ( w,s,a,d-DEPLACER / b- MODE BOMBARDEMENT / f-PASSER ) ");

    text4.setString("Unite jouee : Hussard \n ( w,s,a,d-DEPLACER OU ATTAQUER / f-PASSER ) ");

    text5.setString("Unite jouee : Canon  \n ( w,s,a,d-DEPLACER / b- MODE BOMBARDEMENT / f-PASSER )");

    text6.setString("Unite jouee : Tank  \n ( w,s,a,d-DEPLACER OU ATTAQUER / f-PASSER ) ");

    text7.setString("Unite jouee : Lance-M \n ( w,s,a,d-DEPLACER / b- MODE BOMBARDEMENT / f-PASSER ) ");

    text8.setString("Unite jouee : Bombe H  \n");

    textAchatC.setString("Mode achat de case :\n (w,a,s,d-DEPLACER) / v-Acheter la case / f-Passer");
    textAchatUAgeI.setString("Mode achat d'unites :\n (c-colon) (h-hoplite-AgeI) (a-archer-AgeI) (f-Passer) \n 50 Nour. - 10 Prod. - 15 Prod. ");
    textAchatUAgeII.setString("Mode achat d'unites :\n (c-colon) (m-hussard-AgeII) (k-canon-AgeII) (f-Passer) \n 50 Nour. - 25 Prod. - 35 Prod. ");
    textAchatUAgeIII.setString("Mode achat d'unites :\n (c-colon) (t-tank-AgeIII) (l-lance-missile-AgeIII) (f-Passer) \n 50 Nour. - 150 Prod. - 250 Prod. )");
    textModeB.setString("Mode BOMBARDEMENT :\n(w,a,s,d-ATTAQUER/DEPLACER) / f-Passer");

    //Chargement des textures
    texture.loadFromFile("data/Accueil.jpg");
    textureLogo.loadFromFile("data/Intro/TOC_Logo.png");
    texturePartieRap.loadFromFile("data/Intro/PartieRapide.png");
    texturePartiePerso.loadFromFile("data/Intro/PartiePerso.png");
    textureOcean.loadFromFile("data/Cases/CaseEau.png");
    textureTerre.loadFromFile("data/Cases/CaseTerre.png");
    textureVilleAmi.loadFromFile("data/Ville/VilleAmi.png");
    textureVilleEnnemi.loadFromFile("data/Ville/VilleEnnemi.png");
    CasePossedeeAmi.loadFromFile("data/Cases/CasePossedeeAmi.png");
    CasePossedeeEnnemi.loadFromFile("data/Cases/CasePossedeeEnnemi.png");

    textureHoplite.loadFromFile("data/Unites/Hoplite.png");
    textureArcher.loadFromFile("data/Unites/Archer.png");
    textureHussard.loadFromFile("data/Unites/Hussard.png");
    textureCanon.loadFromFile("data/Unites/Canon.png");
    textureColon.loadFromFile("data/Unites/Colon.png");
    textureLM.loadFromFile("data/Unites/LanceM.png");
    textureChar.loadFromFile("data/Unites/Tank.png");
    textureBombeAmi.loadFromFile("data/Unites/BombeAmi.png");

    textureHopliteE.loadFromFile("data/Unites/HopliteEnnemi.png");
    textureArcherE.loadFromFile("data/Unites/ArcherEnnemi.png");
    textureHussardE.loadFromFile("data/Unites/HussardEnnemi.png");
    textureCanonE.loadFromFile("data/Unites/CanonEnnemi.png");
    textureColonE.loadFromFile("data/Unites/ColonEnnemi.png");
    textureLME.loadFromFile("data/Unites/LanceMEnnemi.png");
    textureCharE.loadFromFile("data/Unites/TankEnnemi.png");
    textureBombeE.loadFromFile("data/Unites/BombeEnnemi.png");

    textureOr.loadFromFile("data/Ressources/or.png");
    textureProd.loadFromFile("data/Ressources/prod.png");
    textureNourriture.loadFromFile("data/Ressources/nourriture.png");

    textureScience.loadFromFile("data/Ressources/science.png");
    textureScienceAge2.loadFromFile("data/Ressources/scienceAge2.png");
    textureScienceAge3.loadFromFile("data/Ressources/scienceAge3.png");

    textureFond.loadFromFile("data/Fond.jpg");
    textureFond2.loadFromFile("data/Fond2.jpg");
    textureQuitter.loadFromFile("data/Intro/Quitter.png");
    textureFin.loadFromFile("data/Defaite.jpg");
    textureFinV.loadFromFile("data/Victoire.jpg");
    bout3.loadFromFile("data/Intro/3J.png");
    bout4.loadFromFile("data/Intro/4J.png");
    bout5.loadFromFile("data/Intro/5J.png");
    bout6.loadFromFile("data/Intro/6J.png");
    boutRetour.loadFromFile("data/Intro/Retour.png");

    //Chargement des sprites (taille)
    spriteLogo.move(175,20);
    spriteLogo.setTexture(textureLogo);

    spritePartieRap.move(293,250);
    spritePartieRap.scale(0.5f,0.5f);
    spritePartieRap.setTexture(texturePartieRap);

    spritePartiePerso.move(293,400);
    spritePartiePerso.scale(0.5f,0.5f);
    spritePartiePerso.setTexture(texturePartiePerso);

    spriteQuitter.move(293,550);
    spriteQuitter.scale(0.5f,0.5f);
    spriteQuitter.setTexture(textureQuitter);

    sprite.scale(0.55f,0.55f);
    sprite.setTexture(texture);

    spriteOcean.scale(0.1f,0.1f);
    spriteOcean.setTexture(textureOcean);

    spriteTerre.scale(0.1f,0.1f);
    spriteTerre.setTexture(textureTerre);

    spriteVilleAmi.scale(0.2f,0.2f);
    spriteVilleAmi.setTexture(textureVilleAmi);

    spriteVilleEnnemi.scale(0.07f,0.07f);
    spriteVilleEnnemi.setTexture(textureVilleEnnemi);

    spriteChar.scale(0.015f,0.015f);
    spriteChar.setTexture(textureChar);

    spriteArcher.scale(0.05f,0.05f);
    spriteArcher.setTexture(textureArcher);

    spriteHoplite.scale(0.08f,0.08f);
    spriteHoplite.setTexture(textureHoplite);

    spriteCanon.scale(0.05f,0.05f);
    spriteCanon.setTexture(textureCanon);

    spriteHussard.scale(0.05f,0.05f);
    spriteHussard.setTexture(textureHussard);

    spriteColon.scale(0.1f,0.1f);
    spriteColon.setTexture(textureColon);

    spriteLM.scale(0.07f,0.07f);
    spriteLM.setTexture(textureLM);

    spriteBombeAmi.scale(0.05f,0.05f);
    spriteBombeAmi.setTexture(textureBombeAmi);

    spriteCharE.scale(0.015f,0.015f);
    spriteCharE.setTexture(textureCharE);

    spriteArcherE.scale(0.05f,0.05f);
    spriteArcherE.setTexture(textureArcherE);

    spriteHopliteE.scale(0.08f,0.08f);
    spriteHopliteE.setTexture(textureHopliteE);

    spriteCanonE.scale(0.05f,0.05f);
    spriteCanonE.setTexture(textureCanonE);

    spriteHussardE.scale(0.05f,0.05f);
    spriteHussardE.setTexture(textureHussardE);

    spriteColonE.scale(0.1f,0.1f);
    spriteColonE.setTexture(textureColonE);

    spriteLME.scale(0.07f,0.07f);
    spriteLME.setTexture(textureLME);

    spriteBombeE.scale(0.05f,0.05f);
    spriteBombeE.setTexture(textureBombeE);

    spriteOr.scale(0.1f,1);
    spriteOr.setTexture(textureOr);
    spriteOr.move(540,40);

    spriteNourriture.scale(0.1f,1);
    spriteNourriture.setTexture(textureNourriture);
    spriteNourriture.move(90,40);

    spriteProd.scale(0.1f,1);
    spriteProd.setTexture(textureProd);
    spriteProd.move(300,40);

    spriteScience.scale(0.1f,1);
    spriteScience.setTexture(textureScience);
    spriteScience.move(760,40);

    spriteScienceAge2.scale(0.1f,1);
    spriteScienceAge2.setTexture(textureScienceAge2);
    spriteScienceAge2.move(760,40);

    spriteScienceAge3.scale(0.1f,1);
    spriteScienceAge3.setTexture(textureScienceAge3);
    spriteScienceAge3.move(760,40);

    spriteFond.scale(0.8f,0.8f);
    spriteFond.setTexture(textureFond);

    spriteFond2.scale(0.8f,2);
    spriteFond2.setTexture(textureFond2);

    spriteFin.scale(0.65f,0.65f);
    spriteFin.setTexture(textureFin);

    spriteFinV.scale(0.65f,0.65f);
    spriteFinV.setTexture(textureFinV);

    spriteCasePossedeeAmi.scale(0.05f,0.05f);
    spriteCasePossedeeAmi.setTexture(CasePossedeeAmi);

    spriteCasePossedeeEnnemi.scale(0.05f,0.05f);
    spriteCasePossedeeEnnemi.setTexture(CasePossedeeEnnemi);

    spriteBout3.move(250,270);
    spriteBout3.scale(0.5f,0.5f);
    spriteBout3.setTexture(bout3);

    spriteBout4.move(550,270);
    spriteBout4.scale(0.5f,0.5f);
    spriteBout4.setTexture(bout4);

    spriteBout5.move(250,400);
    spriteBout5.scale(0.5f,0.5f);
    spriteBout5.setTexture(bout5);

    spriteBout6.move(550,400);
    spriteBout6.scale(0.5f,0.5f);
    spriteBout6.setTexture(bout6);

    spriteBoutRetour.move(550,300);
    spriteBoutRetour.scale(0.2f,0.2f);
    spriteBoutRetour.setTexture(boutRetour);
}

void Jeu_graphique::DeplacerCamera_JeuGraphique(sf::View & view, sf::View & view2, sf::View & minimapView,sf::View & BarreRessouce,  sf::RenderWindow & window,
                                    Unite * u)
{
    assert(u->gettypeUnite()>-1 && u->gettypeUnite()<9);

    sf::Event event;
    sf::Event event2;
    int f =1;
    int compteur=0;
    char action='0';
    while ((window.pollEvent(event)) || (f==1)  )
    {
        if(f==0){break;}

         //Utilise la vue
        window.setView(view);
        //Afficher la vue
        AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessouce,compteur,0);
        // on regarde le type de l'évènement...

    switch (event.type)
    {
        // fenêtre fermée
        case sf::Event::Closed:
            window.close();
            f=0;
            break;
        // touche pressée
        case sf::Event::KeyReleased:
//----------------------------------------------MOUVEMENT DE CAMERA-----------------------------------------------------
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (VueX>=250)
                {
                    VueX=VueX-60;
                }
                // la touche "flèche gauche" est enfoncée : on bouge la caméra
                view.setCenter(VueX, VueY);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (VueX<=2250)
                {
                    VueX=VueX+60;
                }
                // la touche "flèche droite" est enfoncée : on bouge la caméra
                view.setCenter(VueX, VueY);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                if(VueY>250)
                {
                   VueY=VueY-60;
                }

                // la touche "flèche haut" est enfoncée : on bouge la caméra
                view.setCenter(VueX, VueY);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                if(VueY<1150)
                {
                   VueY=VueY+60;
                }
                // la touche "flèche droite" est enfoncée : on bouge la caméra
                view.setCenter(VueX, VueY);
            }
//---------------------------------------DEPLACEMENT DES UNITE---------------------------------------------------------
            if (u->gettypeUnite()==1 || u->gettypeUnite()==2 || u->gettypeUnite()==3 ||u->gettypeUnite()==4 ||
                u->gettypeUnite()==5 ||u->gettypeUnite()==6 ||u->gettypeUnite()==7 || u->gettypeUnite()==8 )
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    action='w';
                    Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                    if((u->getPM())<=0){f=0;}
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    action='s';
                    Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                    if(u->getPM()<=0){f=0;}
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                {
                    action='d';
                    Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                    if(u->getPM()<=0){f=0;}
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && u->gettypeUnite()!=0)
                {
                    action='a';
                    Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                    if(u->getPM()<=0){f=0;}

                }

            }


//-----------------------------------------------PASSER SON TOUR---------------------------------------------------
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
            {
                action='f';
                Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                f=0;
            }

//-----------------------------------------------FONDER UNE VILLE---------------------------------------------------
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && u->gettypeUnite()==1)
            {
                action='v';
                Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                f=0;
            }

//-----------------------------------------------ACHETER CASES---------------------------------------------------
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && u->gettypeUnite()==0)
            {
                action='c';
                Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                f=0;
            }

//-----------------------------------------------ACHETER UNITES---------------------------------------------------
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && u->gettypeUnite()==0)
            {
                AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessouce,0,1);
                int f2=1;
                action='a';
                while (window.pollEvent(event2) || f2==1)
                {
                    switch (event2.type)
                    {
                        case sf::Event::KeyReleased:

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) &&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getNourritureCivilization()>=50)
                        {
                              Action_JeuGraphique(action,'c',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::H) &&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=10)
                        {
                              Action_JeuGraphique(action,'h',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2,minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=15)
                        {
                              Action_JeuGraphique(action,'a',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)&&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=25)
                        {
                              Action_JeuGraphique(action,'m',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)&&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=35)
                        {
                              Action_JeuGraphique(action,'k',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::T)&&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=150)
                        {
                              Action_JeuGraphique(action,'t',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::L)&&
                           tabCiv_JeuGraphique[u->getproprioUnite()].getProductionCivilization()>=250)
                        {
                              Action_JeuGraphique(action,'l',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                        {
                              Action_JeuGraphique(action,'f',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                              f2=0;
                              f=0;
                        }
                        break;
                        default:
                        break;
                    }
                }

            }

//-----------------------------------------------MODE BOMBARDEMENT---------------------------------------------------

             if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
             {
                  if (u->gettypeUnite()==3 || u->gettypeUnite()==5 || u->gettypeUnite()==7)
                  {
                      AffichGraph_JeuGraphique(window,u,view,view2, minimapView,BarreRessouce,0,1);
                      action='b';
                      Action_JeuGraphique(action,'0',u,tabCiv_JeuGraphique[u->getproprioUnite()],window,view,view2, minimapView,BarreRessouce);
                      f=0;
                   }
             }
            break;
            // on ne traite pas les autres types d'évènements
            default:
            break;
            }
            compteur++;

    }

DefinirProprioUnite_JeuGraphique();
DefinirTouteCaseDejaOccupe_JeuGraphique();
VerificationUnitesMortes_JeuGraphique();

}

void Jeu_graphique::Accueil_JeuGraphique()
{
    //On charge tout le contenu multimédia
    ChargerPoliceTexture_JeuGraphique();
    // Declaration de la fenêtre windows
    sf::RenderWindow window(sf::VideoMode(1000, 700), "Time of Civilization", sf::Style::Close | sf::Style::Titlebar );
    MenuPrincipal_JeuGraphique(window);
}

void Jeu_graphique:: MenuPrincipal_JeuGraphique(sf::RenderWindow & window)
{
    Victoire.stop();
    Defaite.stop();
    sf::Event Evenement;
    window.clear();
    window.draw(sprite);
    window.draw(spriteLogo);
    window.draw(spritePartieRap);
    window.draw(spritePartiePerso);
    window.draw(spriteQuitter);
    window.display();
    Intro.play();
    Intro.setLoop(true);
    //On récupère la position des sprites cliquables
    sf::Vector2f positionBoutonRapide(spritePartieRap.getPosition());
    sf::Vector2f tailleBoutonRapide(spritePartieRap.getScale());

    sf::FloatRect monBoutonRapide(positionBoutonRapide.x, positionBoutonRapide.y,414, 118);

    sf::Vector2f positionBoutonPerso(spritePartiePerso.getPosition());
    sf::Vector2f tailleBoutonPerso(spritePartiePerso.getScale());

    sf::FloatRect monBoutonPerso(positionBoutonPerso.x, positionBoutonPerso.y, 414, 118);

    sf::Vector2f positionQuitter(spriteQuitter.getPosition());
    sf::Vector2f tailleBoutonQuitter(spriteQuitter.getScale());

    sf::FloatRect monBoutonQuitter(positionQuitter.x, positionQuitter.y, 414, 118);

    while (window.isOpen())
    {
        while (window.pollEvent(Evenement))
        {
            // on regarde le type de l'évènement...
            switch (Evenement.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    window.close();
                    break;

                // touche pressée de la souris
                case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    if(monBoutonRapide.contains(localPosition.x, localPosition.y))
                    {
                        Construction_JeuGraphique(2,"JoueurHumain");
                        GestionTourGraph_JeuGraphique(window);
                    }
                    if(monBoutonPerso.contains(localPosition.x, localPosition.y))
                    {
                        PartiePerso_JeuGraphique(window);
                    }
                    if(monBoutonQuitter.contains(localPosition.x, localPosition.y))
                    {
                       window.close();
                    }
                }
                break;
                // on ne traite pas les autres types d'évènements
                default:
                break;
            }
        }
    }
    // tant qu'il y a des évènements à traiter...
}

void Jeu_graphique::Fin_JeuGraphique(sf::RenderWindow & window, sf::View & view)
{
    view.setCenter(500,350);
    window.setView(view);
    sf::Event Evenement2;
    window.clear();
    window.draw(spriteFin);
    window.draw(spriteLogo);
    window.draw(spriteBoutRetour);
    window.draw(spriteQuitter);
    window.display();
    Defaite.play();
    Defaite.setLoop(true);

    //On récupère la position des sprites cliquables
    sf::Vector2f positionQuitter(spriteQuitter.getPosition());
    sf::Vector2f tailleBoutonQuitter(spriteQuitter.getScale());

    sf::FloatRect monBoutonQuitter(positionQuitter.x, positionQuitter.y, 414, 118);

    sf::Vector2f positionRetour(spriteBoutRetour.getPosition());
    sf::Vector2f tailleBoutonRetour(spriteBoutRetour.getScale());

    sf::FloatRect monBoutonRetour(positionRetour.x, positionRetour.y, 414, 118);


    while (window.isOpen())
    {
        while (window.pollEvent(Evenement2))
        {
            // on regarde le type de l'évènement...
            switch (Evenement2.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    window.close();
                    break;

                // touche pressée de la souris
                case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                     if(monBoutonQuitter.contains(localPosition.x, localPosition.y))
                    {
                       window.close();
                    }
                     if(monBoutonRetour.contains(localPosition.x, localPosition.y))
                    {
                       MenuPrincipal_JeuGraphique(window);
                    }
                }
                break;
                // on ne traite pas les autres types d'évènements
                default:
                break;
            }
        }
    }
}

void Jeu_graphique::FinV_JeuGraphique(sf::RenderWindow & window, sf::View & view)
{
    view.setCenter(500,350);
    window.setView(view);
    sf::Event Evenement2;
    window.clear();
    window.draw(spriteFinV);
    window.draw(spriteLogo);
    window.draw(spriteBoutRetour);
    window.draw(spriteQuitter);
    window.display();
    Victoire.play();
    Victoire.setLoop(true);

    //On récupère la position des sprites cliquables
    sf::Vector2f positionQuitter(spriteQuitter.getPosition());
    sf::Vector2f tailleBoutonQuitter(spriteQuitter.getScale());

    sf::FloatRect monBoutonQuitter(positionQuitter.x, positionQuitter.y, 414, 118);

    sf::Vector2f positionRetour(spriteBoutRetour.getPosition());
    sf::Vector2f tailleBoutonRetour(spriteBoutRetour.getScale());

    sf::FloatRect monBoutonRetour(positionRetour.x, positionRetour.y, 414, 118);


    while (window.isOpen())
    {
        while (window.pollEvent(Evenement2))
        {
            // on regarde le type de l'évènement...
            switch (Evenement2.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    window.close();
                    break;

                // touche pressée de la souris
                case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                     if(monBoutonQuitter.contains(localPosition.x, localPosition.y))
                    {
                       window.close();
                    }
                     if(monBoutonRetour.contains(localPosition.x, localPosition.y))
                    {
                       MenuPrincipal_JeuGraphique(window);
                    }
                }
                break;
                // on ne traite pas les autres types d'évènements
                default:
                break;
            }
        }
    }
}

void Jeu_graphique::PartiePerso_JeuGraphique(sf::RenderWindow & window)
{

    sf::Event Evenement3;
    window.clear();
    window.draw(sprite);
    window.draw(spriteLogo);
    window.draw(spriteBout3);
    window.draw(spriteBout4);
    window.draw(spriteBout5);
    window.draw(spriteBout6);
    window.draw(spriteQuitter);
    window.display();

    sf::Vector2f positionBouton3(spriteBout3.getPosition());
    sf::Vector2f tailleBouton3(spriteBout3.getScale());

    sf::FloatRect monBouton3(positionBouton3.x, positionBouton3.y,200, 57);

    sf::Vector2f positionBouton4(spriteBout4.getPosition());
    sf::Vector2f tailleBouton4(spriteBout4.getScale());

    sf::FloatRect monBouton4(positionBouton4.x, positionBouton4.y, 200, 57);

    sf::Vector2f positionBouton5(spriteBout5.getPosition());
    sf::Vector2f tailleBouton5(spriteBout5.getScale());

    sf::FloatRect monBouton5(positionBouton5.x, positionBouton5.y, 200, 57);

    sf::Vector2f positionBouton6(spriteBout6.getPosition());
    sf::Vector2f tailleBouton6(spriteBout6.getScale());

    sf::FloatRect monBouton6(positionBouton6.x, positionBouton6.y, 200, 57);

    sf::Vector2f positionQuitter(spriteQuitter.getPosition());
    sf::Vector2f tailleBoutonQuitter(spriteQuitter.getScale());

    sf::FloatRect monBoutonQuitter(positionQuitter.x, positionQuitter.y, 414, 118);

    while (window.isOpen())
    {
        while (window.pollEvent(Evenement3))
        {
            // on regarde le type de l'évènement...
            switch (Evenement3.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    window.close();
                    break;

                // touche pressée de la souris
                case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    if(monBouton3.contains(localPosition.x, localPosition.y))
                    {
                        Construction_JeuGraphique(3,"JoueurHumain");
                        GestionTourGraph_JeuGraphique(window);

                    }
                    if(monBouton4.contains(localPosition.x, localPosition.y))
                    {
                        Construction_JeuGraphique(4,"JoueurHumain");
                        GestionTourGraph_JeuGraphique(window);
                    }
                    if(monBouton5.contains(localPosition.x, localPosition.y))
                    {
                        Construction_JeuGraphique(5,"JoueurHumain");
                        GestionTourGraph_JeuGraphique(window);
                    }
                    if(monBouton6.contains(localPosition.x, localPosition.y))
                    {
                        Construction_JeuGraphique(6,"JoueurHumain");
                        GestionTourGraph_JeuGraphique(window);
                    }
                    if(monBoutonQuitter.contains(localPosition.x, localPosition.y))
                    {
                       window.close();
                    }
                }
                break;
                // on ne traite pas les autres types d'évènements
                default:
                break;
            }
        }
    }
}

string Jeu_graphique::ConvertisseurIntEnString_JeuGraphique (const int & i)
{
    assert(i>=0);
    stringstream ss;
    ss << i;
    string s=ss.str();
    return s;
}

void Jeu_graphique::Gagnant_JeuGraphique(sf::RenderWindow & window, sf::View & view)
{
    VerificationUnitesMortes_JeuGraphique();
    DefinirProprioUnite_JeuGraphique();
    DefinirTouteCaseDejaOccupe_JeuGraphique();

    int compteur=0;

    for (unsigned int i=0; i<tabCiv_JeuGraphique[0].getTabUnite().taille_utilisee; i++)
    {
        if(tabCiv_JeuGraphique[0].getUniteDeTabUnite(i)->gettypeUnite()==0)
        {
            compteur=compteur+1;
        }
    }
    if(compteur>0)
    {//pour choisir entre l'ecran de fin ou de defaite
        FinV_JeuGraphique(window,view);
    }

    else
    {
        Fin_JeuGraphique(window,view);
    }

}

void Jeu_graphique :: TestRegression_JeuGraphique ()
{
    cout<<"Voici le test de regression du module Jeu_graphique, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree une fenetre window."<<endl;

sf::RenderWindow TestWindow(sf::VideoMode(500, 500), "Test Regression", sf::Style::Close | sf::Style::Titlebar );

sf::Event TestEvenement;

  while (TestWindow.isOpen())
    {
        while (TestWindow.pollEvent(TestEvenement))
        {
            // on regarde le type de l'évènement...
            switch (TestEvenement.type)
            {
                // fenêtre fermée
                case sf::Event::Closed:
                    TestWindow.close();
                    break;

                // touche pressée de la souris
                case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                     TestWindow.close();
                }
                break;
                // on ne traite pas les autres types d'évènements
                default:
                break;
            }
        }
    }

    cout<<"On cree une unite puis on affiche son nom en utilisant GetUnitePArCoord."<<endl;

    Unite *Tank = new Unite(6,0,20,10);
    tabCiv_JeuGraphique[0].getTabUnite().AjouterElement(Tank);

    DefinirProprioUnite_JeuGraphique();
    DefinirCaseDejaOccupe_JeuGraphique(20,10);


    GetUniteParCoord_JeuGraphique(20,10)->getnomUnite();

    cout<<"On ajoute de la science puis on affiche son l'ere en utilisant au prealable AugmentationAge."<<endl;
    cout<<tabCiv_JeuGraphique[0].getscience_Civilization()<<endl;
     cout<<"Age de la civilisation 0 avant"<<tabCiv_JeuGraphique[0].getage_Civilization()<<endl;
    tabCiv_JeuGraphique[0].setscienceCivilization(300);
    AugmentationAge_JeuGraphique();
    cout<<tabCiv_JeuGraphique[0].getscience_Civilization()<<endl;
    cout<<"Age de la civilisation 0 après"<<tabCiv_JeuGraphique[0].getage_Civilization()<<endl;
    cout<<endl;

    cout<<"On retablit les PM d'une unité"<<endl;
    Tank->setPM(0);
    cout<<Tank->getPM()<<endl;
    RetablirPM_JeuGraphique(tabCiv_JeuGraphique[0].getTabUnite());
    cout<<Tank->getPM()<<endl;


    cout<<"On convertit un entier en chaîne de caractere"<<endl;
    cout<<ConvertisseurIntEnString_JeuGraphique(50)<<endl;

    DefinirProprioUnite_JeuGraphique();

    cout<<"On detruit une unite et on verifie que sa case s'est bien liberee en utilisant VerificationUniteMorte et DefinirTouteCaseDejaOccupe"<<endl;
    cout<<"Avant sa destruction : "<<Tank->getPV()<<endl;
    Tank->setPV(0);
    cout<<"Occupation : "<<plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(20,10).getDejaOccupe()<<endl;
    VerificationUnitesMortes_JeuGraphique();
    DefinirTouteCaseDejaOccupe_JeuGraphique();
    cout<<"Apres sa destruction : "<<Tank->getPV()<<endl;
    cout<<"Occupation : "<<plateau_JeuGraphique->GetCaseIDParCoordonnees_Plateau(20,10).getDejaOccupe()<<endl;

    cout<<"On distribue des ressources pour chaque civilisation en fonction de leurs cases possedees :"<<endl;
    cout<<"Prod : "<<tabCiv_JeuGraphique[0].getProductionCivilization()<<endl;
    cout<<"Nourriture : "<<tabCiv_JeuGraphique[0].getNourritureCivilization()<<endl;
    cout<<"Science : "<<tabCiv_JeuGraphique[0].getscience_Civilization()<<endl;
    cout<<"Or : "<<tabCiv_JeuGraphique[0].getOrCivilization()<<endl;
    DistribuerRessource_JeuGraphique();
    cout<<"Prod : "<<tabCiv_JeuGraphique[0].getProductionCivilization()<<endl;
    cout<<"Nourriture : "<<tabCiv_JeuGraphique[0].getNourritureCivilization()<<endl;
    cout<<"Science : "<<tabCiv_JeuGraphique[0].getscience_Civilization()<<endl;
    cout<<"Or : "<<tabCiv_JeuGraphique[0].getOrCivilization()<<endl;
    cout<<endl;

    Unite *Tank2 = new Unite(6,0,22,10);
    tabCiv_JeuGraphique[0].getTabUnite().AjouterElement(Tank2);

    Unite *LM = new Unite(7,1,24,10);
    tabCiv_JeuGraphique[1].getTabUnite().AjouterElement(LM);

    cout<<"On cree deux unites chacune ennemie l'une de l'autre. On observe si le tank se fait attaquer par le lance-missile"<<endl;
    cout<<"Vie du tank avant l'attaque : "<<Tank2->getPV()<<endl;

    BombardementAutomatiqueIA_JeuGraphique(1,1);

    cout<<"Vie du tank après l'attaque : "<<Tank2->getPV()<<endl;
    cout<<endl<<endl;


    cout<<"Ceci marque la fin du test de regression du module JeuGraphique"<<endl;
    delete Tank; delete Tank2; delete LM;
}

