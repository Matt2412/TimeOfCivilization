#include "Case.h"



//Sélectionne un nombre au hasard
int Rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

//Fonction qui affiche la map de manière aléatoire et qui utilise pour cela la fonction rand_a_b et initialisationAleatoire
int TypeCase ()
{
    int nbAleatoire = Rand_a_b(0,101);
    if (nbAleatoire<30)//Si le nombre aléatoire est inférieur à 30 alors la Case a pour type Océan
    {return 0;}
    else {return 1;}//Sinon elle est de type Terre
}

//Constructeur de Case
Case::Case()
{
    proprioCase_Case = -1;
    type_Case = TypeCase();
    if (type_Case==0)
    {
        science_Case = 1;
        nourriture_Case = 1;
        production_Case = 0;
        or_Case = 0;
    }
    else
    {
        science_Case = 0;
        production_Case = 1;
        nourriture_Case = 0;
        or_Case = 1;
    }
    dejaOccupe_Case = -1;
    prix_Case = 10;
}

//Getters
int Case::getX()const {return x_Case;}
int Case::getY() const{return y_Case;}
int Case::getCaseID() const{return ID_Case;}
int Case::getTypeCase()const{return type_Case;}
int Case::getProprioCase() const {return proprioCase_Case;}
int Case::getOrParCase () const {return or_Case;}
int Case::getNourritureParCase () const {return nourriture_Case;}
int Case::getScienceParCase () const {return science_Case;}
int Case::getProductionParCase  () const {return production_Case;}
int Case::getPrixParCase() const {return prix_Case;}
int Case::getDejaOccupe () const {return dejaOccupe_Case;}


//Setters
void Case::setX(const int k) { x_Case=k;}
void Case::setY(const int k) { y_Case=k;}
void Case::setCaseID(const int k) { ID_Case=k;}
void Case::setTypeCase(const int k) { type_Case=k;}
void Case::setProprioCase(const int k) { proprioCase_Case=k;}
void Case::setOrParCase (const int k) { or_Case=k;}
void Case::setNourritureParCase (const int k) { nourriture_Case=k;}
void Case::setScienceParCase (const int k) { science_Case=k;}
void Case::setProductionParCase (const int k) { production_Case=k;}
void Case::setDejaOccupe (const int k) { dejaOccupe_Case=k;}

//Destructeur
Case::~Case()
{
    //cout<<"La Case est detruite"<<endl;
}

void Case::TestRegression_Case()
{
    int testINT;

    cout<<"Voici le test de regression du module Case, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree une case. "<<endl;
    cout<<"- int rand_a_b(4, 9) renvoie un nombre compris entre 4 et 9 :";
    testINT = Rand_a_b(4,9);
    cout<<testINT<<endl;

    cout<<" int TypeCase () envoie un nombre compris entre 0 et 1 :";
    testINT = TypeCase();
    cout<<testINT<<endl;

    cout<<"Ceci marque la fin du test de regression du module Case."<<endl;
}




