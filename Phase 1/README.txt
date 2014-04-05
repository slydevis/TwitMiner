Pour la phase 1 :

On s'est réparti les différentes tâches :

Guillaume : Traduction CSV -> Trans
Kévin : Trans -> CSV
Nicolas : Out -> CSV + apriori

Nous avons opté pour que le programme de Guillaume crée un fichier .trad qui donne un id à chaque mot du CSV d'origine.
Ce fichier trad permet par la suite dans le programme de Kévin de pouvoir obtenir le mot correspondant à chaque id du .trans.
Nicolas a ensuite ajouté dans le programme de traduction Trans -> CSV ce qui correspond au out.
Pour les motifs fréquents, nous avons choisi une fréquence de 500 lors de l'utilisation de apriori

MAJ : Nous avons retiré les duplicats que le programme de Guillaume enregistrait.
- Le fichier de traduction est devenir bon
- Les programmes sont plus rapides à l'exécution
- Le fichier .out est plus "logique". Nicolas avait remarqué qu'un motif seul se répétait moins que s'il était accompagné d'autres motifs.

Précision sur l'utilisation des fichiers sources et les repérages des ressources.csv :
ressources.csv : fichier de base des tweets sans la date pour la traduction dans le trans.
trans ressources.csv : fichier de retour avec le programme de traduction de Kévin à partir du .trans
out ressources.csv : fichier de retour avec le programme de Kévin avec le code fourni par Nicolas à partir du .out
old ressources.csv : fichier de base des tweets.

Pour utiliser le CSVToTrans.cpp : le compiler avec g++. Il ne nécessite pas d'arguments.
Pour utiliser le TransToCSV.cpp : le compiler avec g++. Nécessite le fichier à traduire en argument. Vous pouvez donc aussi bien mettre le .trans que le .out
