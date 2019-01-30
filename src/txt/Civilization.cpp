#include "Civilization.h"


//Sélectionne un nombre au hasard
int Rand_a_b2(int a, int b){

    return rand()%(b-a) +a;
}

    //Constructeur de la civilisation qui est pour l'instant mis aux paramètres de 1vs1
Civilization::Civilization()
{
    enVie_Civilization=true;
    or_Civilization=50;
    nourriture_Civilization=50;
    production_Civilization=50;
    science_Civilization=0;
    age_Civilization=1;

    Unite *Ville = new Unite(0,0,DefinirVilleDepartX_Civilization(),DefinirVilleDepartY_Civilization());
    tabUnite.AjouterElement(Ville);//ajout de la ville de départ dans le tableau d'unité de la civilisation créee

}

Civilization::~Civilization()
{
    for(unsigned int i=0;i<tabUnite.taille_utilisee;i++)
    {
        delete getUniteDeTabUnite(i);
    }
    cout<<"Civilisation detruite"<<endl;
}

//Getters
bool Civilization::getEnVie()const {return enVie_Civilization;}
string Civilization::getNomCivilization()const {return nom_Civilization;}
int Civilization::getCivilizationID()const {return ID_Civilization;}
int Civilization::getNourritureCivilization()const {return nourriture_Civilization;}
int Civilization::getscience_Civilization()const {return science_Civilization;}
int Civilization::getOrCivilization()const {return or_Civilization;}
int Civilization::getProductionCivilization()const {return production_Civilization;}
int Civilization::getage_Civilization()const {return age_Civilization;}

    //Setters
void Civilization::setEnVie(const bool x){enVie_Civilization=x;}
void Civilization::setNomCivilization(const string x){nom_Civilization=x;}
void Civilization::setCivilizationID (const int x){ID_Civilization=x;}
void Civilization::setNourritureCivilization (const int x){nourriture_Civilization=x;}
void Civilization::setOrCivilization (const int x){or_Civilization=x;}
void Civilization::setProductionCivilization (const int x){production_Civilization=x;}
void Civilization::setscienceCivilization(const int x){science_Civilization=x;}
void Civilization::setage_Civilization (const int x){age_Civilization=x;}
    //Autres fonctions

int Civilization::DefinirVilleDepartX_Civilization() /*Choisi au hasard un nombre compris entre 0 et 40 non inclus
pour placer la ville de départ*/
{
    int nbAleatoire = Rand_a_b2(1,39);
    return nbAleatoire;
    }

int Civilization::DefinirVilleDepartY_Civilization() /*Choisi au hasard un nombre compris entre 0 et 20 non inclus
     pour placer la ville de départ*/
{
    int nbAleatoire = Rand_a_b2(1,19);
    return nbAleatoire;
}

Unite* Civilization::getUniteDeTabUnite(int k)const
{
    assert(k>=0);
    return (Unite*)tabUnite.valeurIemeElement_Unite(k);
}

TableauDynamique & Civilization::getTabUnite()
{
    return tabUnite;
}


void Civilization::TestRegression_Civilization()
{
    int testINT;

    Unite * ville0 = new Unite(0,1,2,2);
    Unite * tank0 = new Unite(6,2,3,2);
    tabUnite.AjouterElement(ville0);
    tabUnite.AjouterElement(tank0);


    cout<<"Voici le test de regression du module Civilization, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree une civilisation avec des unites. "<<endl;


    cout<<"- int rand_a_b2(4, 9) renvoie un nombre compris entre 4 et 9 : ";
    testINT = Rand_a_b2(4,9);
    cout<<testINT<<endl;


    cout<<"- int Civilization::DefinirVilleDepartX_Civilization() renvoie un nombre compris entre 1 et 40 : ";
    testINT = DefinirVilleDepartX_Civilization();
    cout<<testINT<<endl;


    cout<<"- int Civilization::DefinirVilleDepartY_Civilization() renvoie un nombre compris entre 1 et 20 : ";
    testINT = DefinirVilleDepartY_Civilization();
    cout<<testINT<<endl;


    cout<<"- Unite* Civilization::getUniteDeTabUnite(int k)const  renvoie la i-eme unite du tableau d'unite de cette civilisation (nous afficherons le nom des 2 unites) : ";
    cout<<getUniteDeTabUnite(1)->getnomUnite()<<" et " <<getUniteDeTabUnite(2)->getnomUnite()<<endl;


    cout<<"- TableauDynamique & Civilization::getTabUnite()  renvoie le tableau d'unite (fonctionne comme un getter), nous afficherons le 1er element de ce tableau : ";
    cout<<getTabUnite().valeurIemeElement_Unite(0)->getnomUnite()<<endl;

    delete ville0; delete tank0;
}






