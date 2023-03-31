Hugo Martin
# Projet complexité et récursivité


## Définition du sujet
Ce projet repose sur le casse-tête appelé "daily calendar puzzle".

On nous demande le nombre de solutions existantes pour 31 triplets (jour, quantile, mois).

Nous avons conclu de l'exemple donné dans l'énoncé (54 solutions pour le samedi 1er janvier) 
qu'il était toléré de pivoter les pièces, mais pas de les retourner.

## Modélisation 
Il nous a d'abord fallu modéliser formellement le problème. 

Les dimensions des pièces et du tableau étant fixées, les variables sont les positions de chaque pièce 
ainsi que leur orientation. Les coordonnées de chaque pièce devront rester dans la limite du tableau,
tandis qu'on définit 4 orientations possibles (tous les 90°).

Il existe 4 parties :

- *board* permet de créer la grille de jeu, la remplir ou lui enlever 
des éléments ainsi que placer la date. Le placement de la date est fait en utilisant *util* 
qui attribue à chaque jour ou mois un numéro.

- *piece* permet de créer les pièces ainsi que leur différentes positions possibles. Comme dit précédemment,
nous n'avons pas pris en compte le fait que les pièces pouvaient être retourner.

- *solver* qui permet de résoudre le problème et dont on parlera plus précisemment plus tard.

- *main* qui permet de lancer la résolution du problème et de mesurer le temps passer à le faire.

## Nos choix pour réduire la complexité du code
Afin d'optimiser la complexité de notre solveur, nous avons décidé de modéliser la grille comme 
un tableau de 8 char, ce qui permet de stocker 8x8 bits d'information, chaque bit correspondant à 
une case. 

Une case non recouverte est représentée par un O et une case inaccessible/recouverte par 
un 1. Nous pouvons alors travailler avec des masques et des comparateurs logiques binaires 
afin de réaliser les différentes fonctions qui permettent de résoudre le problème.


## L'algorithme de résolution
Notre solveur fonctionne avec la logique suivante : 

Tant que la liste des pièces non posées n'est pas vide, on pose une pièce à l'aide des fonctions suivantes :

- *canPlacePiece* : cette fonction vérifie s'il est possible de placer la pièce à l'endroit renseigné, 
i.e vérifier qu'elle ne se superpose pas à une autre pièce ou qu'elle reste bien dans l'espace 
de la grille. Si une pièce peut être placé la fonction renvoie True sinon False.

- *placePiece* : cette fonction permet comme son nom l'indique à placer une pièce sur la zone de jeu. 

- *removePiece* : cette fonction permet comme son nom l'indique à retirer une pièce sur la zone de jeu. 

- *solve* : Cette fonction est celle qui est appelée pour lancer solvePiece afin de résoudre le problème.

- *solvePiece* : Cette fonction est celle qui place les pièces sur la grille 

## Difficultés rencontrées


## Résultats