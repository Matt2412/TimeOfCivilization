Time of Civilizations

### Informations factuelles ###
par Vincent Lévêque 11510244, Matthieu Cherrier 11507416, Pierre Billaud 11709442
Trouvable sur la forge de l'université sous le nom : [p1709442] Time_of_Civilizations 
ou par le biais du lien suivant : https://forge.univ-lyon1.fr/p1709442/Time_of_Civilizations


### Manuel ###
Comment compiler ?
	- Aller a la racine de l'archive et ouvrir un terminal.
	- Ecrire "make".
Comment executer ?
	- Ecrire "./bin/TOC_txt" pour jouer a la version en mode texte.
	- Ecrire "./bin/TOC_sfml" pour jouer a la version en mode graphique.
Regles du jeu :
	- Le joueur est face à un écran d'accueil à partir duquel il peut choisir de réaliser une 
	partie rapide, c'est-à-dire jouer contre une IA, ou il peut également choisir de jouer en 
	partie personnalisée.
	- Lorsque la partie commence, chacun son tour, les joueurs devront utiliser à bon escient
	leurs unités afin d'éliminer militairement les unités adverses.
	-Chaque unité de chaque joueur a le droit de réaliser certaines actions spécifiques à chaque
	tour de jeu. Elles sont sélectionnées automatiquement dès que l'action de l'unité précèdente
	se termine.
	- Chaque unité etant différente, les joueurs auront un large choix d'actions, comme par
	exemple acheter une case pour obtenir plus rapidement des ressources, ou investir dans
	 des colons pour créer de nouvelles villes, ou acheter des unités militaires.
	- Mais attention, il faudra veiller sur ses villes car une fois que le joueur n'a plus de 
	villes, il perd la partie.
	- Si le joueur humain est le dernier à posséder des villes, il gagne.
Comment jouer ?
	Le jeu se joue integralement avec le clavier. Le programme vous indique sur quelle touche vous
	pouvez appuyer pour jouer. En effet, au debut du tour de chaque joueur le programme vous indique
	quelles actions vous pouvez entreprendre, les actions pouvant changer en fonction des unités.
Les fonctionnalites du programme :

	Possibilite de selectionner le nombre de joueurs voulus.
	Gestion du tour de chaque joueur.
	Gestion des ressources de chaque joueur (nourriture, or, production, science) : incrémentation 
	automatique des ressources, des ères en fonction de la science.
	Gestion des unités de chaque joueur : rétablissement de leurs points de mouvement, défenses
	automatiques.
	Gestion des IAs : Attaques automatiques, création de villes automatiques...
	Gestion des achats de case, d'unités...
	Gestion de la perte du joueur humain.
	Affichage regulier de toutes les informations pouvant aider le joueur dans ses choix (les actions
	possibles, les cases possédées)
	
	- Le jeu en mode graphique : Ajouts de fonctionnalités liées à l'affichage graphique :

	Affichage des cases possédées par les joueurs grâce à un code couleur.
	Affichage des unités possédées par les joueurs grâce à un code couleur.
	Affichage des caractéristiques de l'unité en train d'être jouée.
	Caméra permettant de parcourir le plateau de jeu.
	Musiques qui se déclenchent lors de la partie.
	


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

