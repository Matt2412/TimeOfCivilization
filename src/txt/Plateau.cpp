
#include "Plateau.h"



    //Constructeur du plateau qui est pour l'instant mis aux paramètres de 1vs1
Plateau::Plateau()
{

}

Plateau::Plateau(int tailleHorizontale_Plateau2,int tailleVerticale_Plateau2)
{
    int Compteur=0;int k =0; // Compteur sert pour les Y et k pour les X
    tailleHorizontale_Plateau=tailleHorizontale_Plateau2;
    tailleVerticale_Plateau=tailleVerticale_Plateau2;
    nbCase_Plateau = 800;
    tabCase_Plateau = new Case[nbCase_Plateau];// 20*40=800 -> Plateau de 1vs1
    for (int j=0;j<nbCase_Plateau;j++)//On définit les coordonnées des cases du plateau
    {
        tabCase_Plateau[j].setCaseID(j);//on définit l'ID de la case (qui va de 0 à 799)
        tabCase_Plateau[j].setX(k);//On définit la position x de la case
        tabCase_Plateau[j].setY(Compteur);//On définit la position y de la case
        if(tabCase_Plateau[j].getTypeCase()==0){tabCase_Plateau[j].setNourritureParCase(1);tabCase_Plateau[j].setScienceParCase(1);}
        if(tabCase_Plateau[j].getTypeCase()==1){tabCase_Plateau[j].setOrParCase(1);tabCase_Plateau[j].setProductionParCase(1);}
        k=k+1;
        if(k==40){k=0;Compteur=Compteur+1;}
    }
}

int Plateau::TypeIemeCase_Plateau ( int indice) //Renvoi le type d'une case ciblée
{
    return tabCase_Plateau[indice].getTypeCase();
}

int Plateau::XiemeCase_Plateau ( int indice) //Renvoi le type d'une case ciblée
{
    return tabCase_Plateau[indice].getX();
}

int Plateau::YiemeCase_Plateau ( int indice) //Renvoi le type d'une case ciblée
{
    return tabCase_Plateau[indice].getY();
}

Case& Plateau::GetCaseIDParCoordonnees_Plateau(int x, int y) {return tabCase_Plateau[y*tailleHorizontale_Plateau+x];}

int Plateau::gettailleHorizontale() const {return tailleHorizontale_Plateau;}
int Plateau::gettailleVerticale() const {return tailleVerticale_Plateau;}
int Plateau::getNbCase() const {return nbCase_Plateau;}
void Plateau::settailleHorizontale(int x) {tailleHorizontale_Plateau=x;}
void Plateau::settailleVerticale(int x) {tailleVerticale_Plateau=x;}
void Plateau::setNbCase (int x) {nbCase_Plateau=tailleVerticale_Plateau*tailleHorizontale_Plateau;}


Case& Plateau::GetCaseDeTabCase_Plateau(int k) {return tabCase_Plateau[k];}

Plateau::~Plateau()
{
    cout<<"Plateau detruit"<<endl;
    delete [] tabCase_Plateau;
}


void Plateau::TestRegression_Plateau()
{
    int testINT;

    cout<<"Voici le test de regression du module Plateau, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree un plateau avec une seule case "<<endl;

    Plateau testPLATEAU(1,1);

    cout<<"- int TypeIemeCase_Plateau(const int indice) renvoie le type de i-eme case du plateau : "<<endl;
    testINT = testPLATEAU.TypeIemeCase_Plateau(1);
    cout<<testINT<<endl;

    cout<<"- int XiemeCase_Plateau (const int indice) renvoie la position X de la i-eme case du plateau"<<endl;
    testINT = testPLATEAU.XiemeCase_Plateau(1);
    cout<<testINT<<endl;

    cout<<"- int YiemeCase_Plateau (const int indice) renvoie la position Y de la i-eme case du plateau"<<endl;
    testINT = testPLATEAU.YiemeCase_Plateau(1);
    cout<<testINT<<endl;


    cout<<"Ceci marque la fin du test de regression du module Plateau."<<endl;
}



