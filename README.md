# Rover Run 🚀

Simulation d’un rover se déplaçant sur une grille (type planète Mars) en suivant une suite de commandes.  
Le projet inclut également une logique de **Min-Cost Path** pour calculer automatiquement un chemin optimal (au coût minimal) entre deux points.

## Fonctionnalités
- Déplacement du rover sur une **grille 2D**
- Gestion de l’**orientation** (N, E, S, W)
- Exécution de commandes (ex. `L` = gauche, `R` = droite, `M` = avancer)
- Gestion des **obstacles** *(si implémenté)*
- **Min-Cost Path** : recherche d’un chemin au **coût total minimal** entre départ et destination

## Min-Cost Path

### Modélisation
- Grille 2D avec :
  - cases “normales”
  - cases à **coût plus élevé** (terrain difficile, zone pénalisante, etc.) *(selon ton modèle)*
  - cases **interdites** (obstacles)
- Déplacements autorisés : **4 directions** (haut/bas/gauche/droite) *(ou 8 si diagonales)*


### Sortie
- Chemin optimal (liste de positions / étapes)
- Coût minimal total
- Optionnel : visualisation du chemin (console)

## Pile & File (structures de données)

Le projet exploite / illustre des structures de données classiques :

- **Pile (Stack)** : structure **LIFO** (*Last In, First Out*)  
  Exemple d’usage : mémoriser des actions

- **File (Queue)** : structure **FIFO** (*First In, First Out*)  
  Exemple d’usage : traiter des éléments dans l’ordre d’arrivée 
