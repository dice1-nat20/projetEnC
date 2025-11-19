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

typedef struct {
    int idClasseDepart;
    int idClasseArrivee;
}t_lien;

typedef struct lienCell {
    t_lien* value;
    struct lienCell* next;
}cellLien;

typedef struct {
    cellLien* head;
}t_hasse;

t_hasse* hasse(t_partition* partition, list_adjac* Graph);

#endif