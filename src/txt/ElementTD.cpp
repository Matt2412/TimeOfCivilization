
#include "ElementTD.h"
#include "Unite.h"


void  AfficheElementTD(ElementTD e) {
  std::cout << "Test"; //changer si besoin
}

void TestRegression_ElementTD()
{

    Unite * hoplite0 = new Unite(2,321,1,1);

    cout<<"Voici le test de regression du module ElementTD, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree une unite. "<<endl;

    cout<<"- void  AfficheElementTD(ElementTD e) n'affiche l'element passe en parametre";
    AfficheElementTD(hoplite0);

    cout<<endl;

    cout<<"Ceci marque la fin du test de regression du module ElementTD."<<endl;
    delete hoplite0;
}
