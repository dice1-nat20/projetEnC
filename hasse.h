#ifndef __HASSE_H__
#define __HASSE_H__
#include "tarjan.h"


//void removeTransitiveLinks(t_link_array *p_link_array);

/**
 * @brief Creates a link array from the given partition and graph.
 *
 * @param part The partition of the graph.
 * @param graph The adjacency list representation of the graph.
 * @return The created link array.
 */
// Ici c'est pour la partie Hasse

/* Lien entre deux classes de la partition : identifiants de la classe de départ et de la classe d’arrivée. */
typedef struct {
    int idClasseDepart;
    int idClasseArrivee;
}t_lien;

/* Cellule de liste chaînée pour le diagramme de Hasse, contenant un pointeur vers un lien et vers la cellule suivante. */
typedef struct lienCell {
    t_lien* value;
    struct lienCell* next;
}cellLien;

/* Diagramme de Hasse : liste chaînée de liens entre classes de la partition. */
typedef struct {
    cellLien* head;
}t_hasse;

t_hasse* hasse(t_partition* partition, list_adjac* Graph);
void displayHasse(t_hasse * hasseGraph);
void displayHasseCarac(t_hasse* hasseGraph, t_partition * partition);
#endif