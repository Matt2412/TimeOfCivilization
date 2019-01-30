#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "src/txt/Jeu.h"
#include "src/graphique/Jeu_graphique.h"
#include "src/txt/Plateau.h"
#include "src/txt/Civilization.h"
#include "src/txt/Unite.h"
#include "src/txt/TableauDynamique.h"
#include "src/txt/ElementTD.h"
#include "src/txt/Case.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
//#include <SFML/Main.hpp>

using namespace std;

void initialisationAleatoire ()
{
    srand(time(NULL)); // initialisation de rand

}

int main()
{
    initialisationAleatoire();//Ne se lance qu'une fois pour tout le programme
    Jeu_graphique jeu;
    jeu.Accueil_JeuGraphique();


	//Case testRegressionCase;
	//testRegressionCase.TestRegression_Case();
	//Plateau testRegressionPlateau;
	//testRegressionPlateau.TestRegression_Plateau();
	//Unite testRegressionUnite;
	//testRegressionUnite.TestRegression_Unite();
	//TableauDynamique testRegressionTableauDynamique;
	//testRegressionTableauDynamique.TestRegression_TableauDynamique();
	//Civilization testRegressionCivilization;
	//testRegressionCivilization.TestRegression_Civilization();
	//Jeu_graphique testRegressionJeuGraphique(2,"JoueurTest");
	//testRegressionJeuGraphique.TestRegression_JeuGraphique();
    //IA testRegressionIA;
	//testRegressionIA.TestRegression_IA();

    return 0;
}
