Pour cette phase, notre fichier .out est composé des motifs ayant une fréquence
> 500.
Notre algorithme place chaque motif et chaque fréquence dans deux tableaux différents.
Pour ce qui concerne l'ensemble vide, nous lui avons attribué la valeur 0 afin
d'obtenir deux tableaux de même taille.
Par la suite, nous avons commencé à mettre en place la partie principale de l'algorithme
qui est de relevé le 1er motif de chaque association et de le retrouver dans le tableau
des motifs.
Dû à l'ajout de la valeur 0 dans notre tableau, chaque motif est placé à la même case
que sa fréquence.
Exemple : le motif 1 se trouve à la case 1 du tableau des motifs.
Sa fréquence, 2008, est placée à la case 1 du tableau des fréquences.
Nous pouvons ainsi relevé plus rapidement la fréquence du 1er motif pour calculer
la confiance et vérifier si elle est >= à MinConf. Les motifs de Conf = 1 ne sont
pas prix en compte car il n'y a aucun intérêt à calculer la confiance qu'un motif
a sur lui-même.

La confiance que nous avons ensuite choisie a été de 0.5 .
MAJ :
Les dix règles d'associations que nous retenons sont :
20 37  -- 1.16537
2301 2302  -- 0.999146
5 8  -- 0.967717
3 8  -- 0.962766
628 630  -- 0.962291
628 646  -- 0.960894
628 630 646  -- 0.960894
630 646  -- 0.956885
1 8  -- 0.912351
1172 2301  -- 0.842333

Pour tester l'algorithme, il faut executer l'exécutable de notre programme de la manière suivante :
[./a.out] [fichier.out] [MinConf]
