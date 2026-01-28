# Projet_RoverRun

# Rover Run (C) — Minimum Cost Path sur carte

Projet en langage C visant à simuler le déplacement d’un rover sur une carte (type Mars) en **modélisant le terrain comme un graphe pondéré** afin de calculer un **chemin de coût minimal** entre deux positions. Une interface graphique (prototype) permet de visualiser la carte et l’exécution.

## Objectif
- Charger une carte depuis des fichiers (dossier `maps/`)
- Modéliser le terrain en **graphe** (nœuds = cases, arêtes = déplacements possibles)
- Associer un **coût** aux déplacements (selon la nature de la case et les règles du terrain)
- Calculer un **minimum cost path** du point de départ au point d’arrivée
- Exécuter la séquence de mouvements et l’afficher (console + prototype graphique)
- Prototype d’interface graphique pour afficher la carte et les déplacements

- Le calcul et la reconstruction du chemin s’appuient sur des structures de données dédiées : file pour gérer l’exploration/parcours et pile pour reconstruire le trajet final dans le bon ordre avant exécution des mouvements.
