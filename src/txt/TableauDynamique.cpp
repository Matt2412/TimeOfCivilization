#include <stdlib.h>
#include "ElementTD.h"
#include "TableauDynamique.h"
#include <iostream>
#include "Unite.h"

using namespace std;

TableauDynamique::TableauDynamique () {
    ad = new ElementTD [1];
    if (ad == NULL) {
      cout << "Espace memoire insuffisant" << endl;
      exit(1);
    }
    capacite = 1;
    taille_utilisee = 0;
}

TableauDynamique::~TableauDynamique () {
  if (ad != NULL) {
      delete [] ad;
      ad = NULL;
  }
}

void TableauDynamique::Vider () {
  if (ad == NULL) delete [] ad;
  ad = new ElementTD [1];
  capacite = 1;
  taille_utilisee = 0;
}

void TableauDynamique::AjouterElement( ElementTD element)
{
    ElementTD * temp;
    if(taille_utilisee == capacite)
    {
        temp=ad;
        ad=new ElementTD [2*capacite];
        capacite *= 2;
        for (unsigned int i = 0; i < taille_utilisee; i++) ad[i] = temp[i];
        delete [] temp;

    }
    ad[taille_utilisee] = element;
    taille_utilisee++;
}

void TableauDynamique::Afficher () const {
  for (unsigned int i = 0; i < taille_utilisee; i++) {
         AfficheElementTD(ad[i]);
        cout << " ";
  }
  cout << endl;
}

void TableauDynamique::SupprimerElement (unsigned int position) {
  if(position < taille_utilisee-1) {
      for(unsigned int i = position; i < taille_utilisee-1; i++)
        ad[i] = ad[i+1];
  }
  taille_utilisee--;
  if (taille_utilisee < capacite / 3) {
    ElementTD * temp = ad;
    capacite = capacite / 2;
    ad = new ElementTD [capacite];
    for(unsigned int i = 0; i < taille_utilisee; i++)
        ad[i] = temp[i];
    delete [] temp;
  }
}

ElementTD TableauDynamique::valeurIemeElement_Unite(unsigned int indice)const
{
    return ad[indice];
}


void TableauDynamique::TestRegression_TableauDynamique()
{
    int testINT;
    TableauDynamique tabTEST;
    Unite * hoplite0 = new Unite(2,31,1,1);
    tabTEST.AjouterElement(hoplite0);


    cout<<"Voici le test de regression du module TableauDynamique, nous allons tester toutes ses fonctions membres (sauf les getters/setters) et afficher leurs resultats. ";
    cout<<"Pour ces differents tests, on cree un tableau dynamique contenant plusieurs fois la meme unite "<<endl;


    cout<<"- void Afficher() const affiche le nom de tous les elements du tableau"<<endl;
    tabTEST.Afficher();
    cout<<endl;

    cout<<"- void AjouterElement (ElementTD e) ajoute un element au tableau dynamique"<<endl;
    cout<<"Le tableau avant appel : ";
    tabTEST.Afficher();
    cout<<"Le tableau apres appel : ";
    tabTEST.Afficher();
    cout<<endl;



    cout<<"- ElementTD valeurIemeElement_Unite(unsigned int indice)const renvoie l'unite au lieu de simplement renvoyer son nom";
    cout<<"Nous allons renvoyer le type du 1er element, au lieu de simplement afficher son nom : "<<endl;
    testINT =  tabTEST.valeurIemeElement_Unite(1)->gettypeUnite();
    cout<<testINT<<endl;


    cout<<"- void SupprimerElement(1) supprime le 1er element"<<endl;
    cout<<"Le tableau avant appel : ";
    tabTEST.Afficher();
    tabTEST.SupprimerElement(1);
    cout<<"Le tableau apres appel : ";
    tabTEST.Afficher();
    cout<<endl;


    cout<<"- void Vider () vide le tableau dynamique"<<endl;
    cout<<"Le tableau avant appel : ";
    tabTEST.Afficher();
    tabTEST.Vider();
    cout<<"Le tableau apres appel : ";
    tabTEST.Afficher();
    cout<<endl;

    cout<<"Ceci marque la fin du test de regression du module TableauDynamique."<<endl;
    delete hoplite0;
}





