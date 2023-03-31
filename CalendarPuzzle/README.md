# Projet complexité et récursivité - Calendar Puzzle
Auteurs: HENRY Steven, MARTINIÈRE Hugo, MÉHU Thomas, SID'AHMED Sidi.
Date: 31/03/2023.

## Définition du sujet
Ce projet repose sur le casse-tête appelé "daily calendar puzzle".

On nous demande le nombre de solutions existantes pour 31 triplets (jour, quantile, mois).

Nous avons conclu de l'exemple donné dans l'énoncé (54 solutions pour le samedi 1er janvier) 
qu'il était toléré de pivoter les pièces, mais pas de les retourner.

## Modélisation 
Il nous a d'abord fallu modéliser formellement le problème. Nous avons 
modélisé le plateau de jeu ainsi que les différentes pièces avec des données binaires de 8 bits par 
8 (0 pour les cases vides et 1 pour les cases occupées ou inaccessibles). 

Nous avons créé différentes structures de données qui sont définies dans les fichiers sources et les fichiers headers correspondants. (board.c/h, util.c/h, shape.c/h, solver.c/h, main.c).

Les dimensions des pièces et du tableau étant fixées, les variables sont les positions de chaque pièce 
ainsi que leur orientation. Les coordonnées de chaque pièce devront rester dans la limite du tableau,
tandis qu'on définit 4 orientations possibles (tous les 90°).

Le code est composé de 4 parties :

### board.c/h
*board.c* permet de créer et de configurer la grille de jeu (remplir/vider les cases, placer la date et les bordures).

Nous avons créé une structure *Board* qui prend en attribut un *short* *\*rows* qui représente les différentes lignes de la grille.

- *fillRow()* 
Remplit les cases d'une ligne en leur appliquant un masque (passer les valeur de 0 à 1 pour les cases
souhaités). 

- *freeRow()*
Permet de libérer une ligne en lui soustrayant le masque (passe la valeur des cases 1 en 0).

- *setBordure()*
Utilise *fillRow()* pour créer des bordures extérieures. Pour améliorer la performance du modèle, il a été pertinent d'agrandir la taille du tableau de 1 vers le haut, le bas, la droite et la gauche et cette fonction permet d'empecher le placement de pièces sur ces mêmes extensions (Remplissage de 1). Cette fonction sert aussi à palcer les cases inaccessibles du plateau (en remplissant de 1 les 4 cases en bas à gauche et le 2 cases en haut à droite de la grille). 
	
- *fillDateCells()*
Utilise *fillRow()* pour remplir les 3 cases du plateau qui correspondent à la date entrée dans les arguments la fonction.

- *configureBoard()*
Permet de générer une grille avec ses bordures et la date voulue en appelant *setBordure()*, et *fillDateCells()*.

- *printBoard()*
Permet d'afficher une grille dans la console pour avoir un rendu visuel. Cette fonction était utilisée afin de résoudre les erreurs.

### shape.c/h

*shape.c* permet de créer les différentes formes du jeu (pièces et motifs insolvables) ainsi que de leur appliquer des rotations. Comme dit précédemment, nous n'avons pas pris en compte le fait que les pièces pouvaient être renversées.
Ce fichier permet aussi de créer des "motifs insolvables" qui nous ont permis de réduire grandement la complexité, nous en parlerons plus précisemment dans la prochaine partie.

Ce fichier contient la structure Piece qui a pour argument trois *char* : la forme de la pièce dans *pieceRows*, la hauteur de la pièce *height*, sa largeur *width* et un booléen *symetric* indiquant si la pièce est symétrique ou non.

Ce fichier contient aussi la structure StopingPattern qui a pour données deux *char* : *pieceRows* qui définit les cases remplies par le motif insolvable, et patternMask qui contient le masque de détection du motif pour le board. Les deux autres données sont des *char*: sa hauteur *height* et sa largeur *width*.

- *initPieces()*
Permet créer une liste des 10 pièces du problèmes et de définir leur forme dans leur attribut *\*pieceRows* de manière binaire.

- *initStoppingPatterns()*
Similaire à *initPieces()* mais pour les motifs insolvables

- *rotatePiece()*
Permet de tourner de 90° une pièce dans le sens horaire et enregistre cette nouvelle orientation dans la pièce.

- *printPiece()*
Permet d'afficher une pièce dans la console pour avoir un rendu visuel (utile à des fins de débugging).

- *printStoppingPattern()*
Permet d'afficher un motif insolvable dans la console pour avoir un rendu visuel. Cette fonction était utilisée afin de résoudre les erreurs.

### Solver
*solver.c* contient toutes les fonctions permettant de résoudre le problème et dont on parlera plus précisemment plus tard.

### Main	
*main.c* contient la fonction main. Elle lance la résolution du problème et mesure le temps passé pour les calculs.

## Nos choix pour réduire la complexité du code
Le choix de l'utilisation d'objets binaires a pour but de limiter la complexité de l'algorithme.
Nous avons alors pu travailler avec des masques et des comparateurs logiques binaires 
afin de réaliser les différentes fonctions ce qui permettait de traiter le tableau ligne par ligne et non case par case.

1) Pour placer une pièce sur le plateau, on utilise des masques binaires multiples (un pour chaque 
ligne) afin de vérifier si la pièce peut être placée dans un premier temps, puis effectivement la placer. Ce processus est généralisé, peu importe la taille de la pièce au travers des fonctions *placePiece()*, *isPiecePlaceable()* et *removePiece()* (présentes au sein des fichiers *solver.c/h*).

2) La fonction *isSolvable()* permet également de tester si, lors du remplissage du plateau, des "motifs insolvables" sont détectés. Ces motifs insolvables sont des ensemble de cases vides et 
isolées qui ne pourront jamais être remplies (ex : une case unique vide et isolée ne pourra jamais être remplie car aucune pièce ne peut rentrer dedans. Idem pour 2 cases isolées et vides colatérales).
Nous n'avons pas pris en compte tout les motifs insolvables pour éviter d'ajouter trop de vérifications qui nuieraient à la performance du programme. Nous avons choisi d'implémenter 10 motifs parmis 15 que nous avons trouvé.
L'idée de cette vérfication est simple : après avoir posé chaque pièce la fonction *isSolvable()* vérifie qu'aucun motif insolvable n'est présent. Si un motif est détecté, la pose de la pièce est annulée.
Son fonctionnement est similaire à celui utilisé pour la fonction *solve()* expliquée plus loin.

3) Les positions de placement des pièces sont calculées avant le placement, ce qui permet de ne pas vérifier que celles-ci dépassent du tableau lors de l'exécution du solveur.


## L'algorithme de résolution
Notre solveur fonctionne avec la logique suivante : 

Tant que toutes les pièces ne sont pas posées, on pose la pièce avec l'indice suivant.
Notre algorithme fonctionne avec les fonctions suivantes:

- *canPlacePiece()*
Vérifie que la tentative de pose ne chevauche pas d'autre pièce.
Pour cela, la fonction utilise un principe de masquage illustré ci-après.
Supposons que nous ayons un tableau 4x4 représenté par la matrice binaire suivante, qui représente notre tableau:
```
1 1 1 1
1 0 0 1
1 0 0 0
1 1 1 1
```
Et nous voulons placer une pièce de 2x2 avec la matrice binaire suivante a la position (1,2) (colonne 1, ligne 2) :
```
    0 1 2 3 
   ---------
0 | 0 0 0 0
1 | 0 0 1 1
2 | 0 0 1 1
3 | 0 0 0 0
```
Pour vérifier si la pièce peut être placée sur le plateau sans empiéter sur les pièces, nous devons dans un premier temps déterminer où sont les espaces libres.

Pour cela, nous inversons d'abord les octets du plateau à l'aide de l'opérateur bitwise NOT (~), qui transforme chaque bit 0 en bit 1 et vice versa. Nous obtenons ainsi la matrice binaire suivante :
```
0 0 0 0
0 1 1 0
0 1 1 1
0 0 0 0
```
Ensuite, dans le but de superposer le modèle de la pièce (positioné à droite des octets) et le plateau, nous devons décaler les colonnes du tableau au travers de l'opérateur de décalage binaire *>>*. 

Nous obtenons ainsi la matrice binaire suivante qui va être masquée au modèle.
```
0 0 0 0
0 0 1 1
0 0 1 1
0 0 0 0
```

Enfin, nous appliquons un opérateur ET bit à bit (&) de la pièce sur le tableau qui fera ressortir quels sont les bits libres. Tous les bits affichant 1 sont les bits qui font partie de la pièce et qui sont libres sur le plateau. Les bits à 0 sont soit occupés pas utile pour le placement de cette pièce.
Nous obtenons ainsi la matrice binaire suivante, qui est le masque :
```
0 0 0 0
0 0 1 1
0 0 1 1
0 0 0 0
```
Nous pouvons maintenant utiliser ce résultat afin de le comparer à la pièce à placer. Si les deux élements sont identiques, la pièce est positionnable. 

- *placePiece()*
Cette fonction permet comme son nom l'indique à placer une pièce sur la zone de jeu. 

- *removePiece()*
Cette fonction permet comme son nom l'indique à retirer une pièce sur la zone de jeu. 

- *solve()*
Cette fonction est celle qui permet de déterminer le nombre de solutions du casse-tête pour une configuration donnée. 
Son fonctionnement est le suivant:
\- Placer la pièce n°0,
\- Vérifier qu'elle puisse rentrer,
\- Vérifier qu'aucun motif insolvable n'apparaît,
\- Placer la pièce n°1 en suivant la même procédure si les conditions précédentes sont remplies,
\- Placer la pièce autre part si les conditions précédentes ne sont pas remplies,
\- Tourner la pièce de 90° jusqu'à faire 360° en répétant la procédure précédente.

## Résultats

Sur l'exemple du sujet (samedi 1er janvier) obtenons 54 solutions en 0,6 sec. Pour 31 jours aléatoires nous avons une moyenne de 0.34s. Le meilleur temps obtenu est 0.09s.