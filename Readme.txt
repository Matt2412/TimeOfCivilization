Time of Civilizations

### Informations factuelles ###
par Vincent L�v�que 11510244, Matthieu Cherrier 11507416, Pierre Billaud 11709442
Trouvable sur la forge de l'universit� sous le nom : [p1709442] Time_of_Civilizations 
ou par le biais du lien suivant : https://forge.univ-lyon1.fr/p1709442/Time_of_Civilizations


### Manuel ###
Comment compiler ?
	- Aller a la racine de l'archive et ouvrir un terminal.
	- Ecrire "make".
Comment executer ?
	- Ecrire "./bin/TOC_txt" pour jouer a la version en mode texte.
	- Ecrire "./bin/TOC_sfml" pour jouer a la version en mode graphique.
Regles du jeu :
	- Le joueur est face � un �cran d'accueil � partir duquel il peut choisir de r�aliser une 
	partie rapide, c'est-�-dire jouer contre une IA, ou il peut �galement choisir de jouer en 
	partie personnalis�e.
	- Lorsque la partie commence, chacun son tour, les joueurs devront utiliser � bon escient
	leurs unit�s afin d'�liminer militairement les unit�s adverses.
	-Chaque unit� de chaque joueur a le droit de r�aliser certaines actions sp�cifiques � chaque
	tour de jeu. Elles sont s�lectionn�es automatiquement d�s que l'action de l'unit� pr�c�dente
	se termine.
	- Chaque unit� etant diff�rente, les joueurs auront un large choix d'actions, comme par
	exemple acheter une case pour obtenir plus rapidement des ressources, ou investir dans
	 des colons pour cr�er de nouvelles villes, ou acheter des unit�s militaires.
	- Mais attention, il faudra veiller sur ses villes car une fois que le joueur n'a plus de 
	villes, il perd la partie.
	- Si le joueur humain est le dernier � poss�der des villes, il gagne.
Comment jouer ?
	Le jeu se joue integralement avec le clavier. Le programme vous indique sur quelle touche vous
	pouvez appuyer pour jouer. En effet, au debut du tour de chaque joueur le programme vous indique
	quelles actions vous pouvez entreprendre, les actions pouvant changer en fonction des unit�s.
Les fonctionnalites du programme :

	Possibilite de selectionner le nombre de joueurs voulus.
	Gestion du tour de chaque joueur.
	Gestion des ressources de chaque joueur (nourriture, or, production, science) : incr�mentation 
	automatique des ressources, des �res en fonction de la science.
	Gestion des unit�s de chaque joueur : r�tablissement de leurs points de mouvement, d�fenses
	automatiques.
	Gestion des IAs : Attaques automatiques, cr�ation de villes automatiques...
	Gestion des achats de case, d'unit�s...
	Gestion de la perte du joueur humain.
	Affichage regulier de toutes les informations pouvant aider le joueur dans ses choix (les actions
	possibles, les cases poss�d�es)
	
	- Le jeu en mode graphique : Ajouts de fonctionnalit�s li�es � l'affichage graphique :

	Affichage des cases poss�d�es par les joueurs gr�ce � un code couleur.
	Affichage des unit�s poss�d�es par les joueurs gr�ce � un code couleur.
	Affichage des caract�ristiques de l'unit� en train d'�tre jou�e.
	Cam�ra permettant de parcourir le plateau de jeu.
	Musiques qui se d�clenchent lors de la partie.
	


### Description de l'organisation de l'archive ###
- La racine
	On y trouve le fichier "Makefile" qui servira a compiler le projet. Il y a egalement les dossiers "bin",
	 "data", "doc", "obj" et "src".
	- Dans le dossier "src" on trouve les dossiers "graphique" et "txt". Le dossier graphique contient le code
		 source du jeu en mode graphique, tandis que le dossier txt contient le code source du 
		jeu en mode texte.
	- Dans le dossier "obj" on trouve deux dossiers "graphique" et "txt". Chacun d'entre eux contient des 
		fichiers objets.
	- Dans le dossier "doc" se trouvent les fichiers de documentation. Pour avoir une documentation 
		complete, aller dans le dossier "html" puis cliquer sur "index.html".
	- Dans le dossier "data" se trouvent tous les fichiers utilises par le programme et qui ne sont pas 
		des lignes de code. On y trouve principalement des images du jeu, mais aussi des polices et des
	musiques.
	- Dans le dossier "bin" se situent les deux executables TOC_sfml et TOC_txt.?

