Tout les motifs ici présents sont après nettoyage.
//Liste des associations >= MinConf=0.5
20 37  -- 1.16537
2301 2303  -- 0.571307
2302 2303  -- 0.572161
628 646  -- 0.960894
630 646  -- 0.956885
628 630  -- 0.962291
3 8  -- 0.962766
2301 2302  -- 0.999146
1172 2301  -- 0.842333
1172 2302  -- 0.842333
628 630 646  -- 0.960894
1172 2301 2302  -- 0.842333

//Fréquences des motifs dépendants (Freq(Y))
8 (9668)
37 (1249)
2303 (670)
646 (689)
630 (719)
2301 (1171)
2302 (1171)
630 646 (688)
2301 2303 (669)

//Correlation de chaque motif
20 37  -- 9.33 x 10^-4		retenu
2301 2303  -- 8.51 x 10^-4	retenu
2302 2303  -- 8.51 x 10^-4	retenu
628 646  -- 13.9 x 10^-4	retenu
630 646  -- 13.8 x 10^-4	retenu
628 630  -- 13.4 x 10^-4	retenu
3 8  -- 0.99 x 10^-4		retenu
2301 2302  -- 8.54 x 10^-4	retenu
1172 2301  -- 7.17 x 10^-4
1172 2302  -- 7.17 x 10^-4
628 630 646  -- 14.0 x 10^-4	retenu
1172 2301 2302  -- 12.6 x 10^-4	retenu

//Utilisation des fichiers sources
Nettoyage.cpp : à compiler avec g++ et mettre le ressources.out en argument
Utiliser à nouveau ExtractRegle.cpp avec compilation g++ et le ressources.out en argument ainsi que la MinConf de 0.5 pour récupérer les associations indiquées en début de fichier.
