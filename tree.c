//
// Created by Sidney (Ingénieur) on 12/11/2024.
//
#include "tree.h"

// Libère la mémoire allouée pour un nœud et ses enfants
void free_node(t_node* node);
//à compléter

// Ajoute un enfant à un nœud parent
void add_child(t_node* parent, t_node* child);
//à compléter

// Crée un arbre un arbre
t_tree create_tree(int n);
//à compléter

// Recherche la feuille de valeur minimale d'un arbre
t_node find_min_node(t_tree);
//à compléter

// Recherche le chemin depuis la racine vers la feuille de valeur minimale d'un arbre
t_node* find_min_path(t_tree,t_node);
//à compléter
