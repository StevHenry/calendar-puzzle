Hugo Martin
# Projet complexité et récursivité
*

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

## Nos choix pour réduire la complexité du code
Afin d'optimiser la complexité de notre solveur, nous avons décidé de modéliser la grille comme 
un tableau de 8 char, ce qui permet de stocker 8x8 bits d'information, chaque bit correspondant à 
une case. 

Une case non recouverte est représentée par un O et une case inaccessible/recouverte par 
un 1. Pour vérifier si on peut poser une pièce, puis pour effectivement la poser le cas échéant, on
peut ainsi travailler avec des masques et les comparateurs logiques binaires.


## L'algorithme de résolution

Notre solveur fonctionne avec la logique suivante : 

Tant que la liste des pièces non posées n'est pas vide, on pose une pièce à l'aide des fonctions suivantes :

*canPlacePiece* : cette fonction vérifie dans un premier temps s'il est possible de placer la pièce
à l'endroit renseigné, i.e vérifier qu'elle ne se superpose pas à une autre pièce ou qu'elle reste
dans l'espace de la grille

*placePiece* : cette fonction utilise d'abord la fonction *canPlacePiece*. Puis comme son nom l'indique elle sert à placer une pièce sur la zone de jeu.




## Difficultés rencontrées


## Résultats