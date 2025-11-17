//
// Created by manon on 14/11/2025.
//

#include "tarjan.h"

l_tergent create_l_tarjan(list_adjac graphe) {
    int nombre=graphe.taille;
    l_tergent *liste_tergent = (l_tergent*) malloc(sizeof(l_tergent));
    for (int i=0;i<=nombre;i++) {
        liste_tergent[i]->identifiant=graphe.adjac_sommets->head->sommet;
        graphe.adjac_sommets->head=graphe.adjac_sommets->head->next;
        liste_tergent[i]->numeroTemp=-1;
        liste_tergent[i]->numAcces=-1;
        liste_tergent[i]->boolTraitement=0;
    }
    return *liste_tergent;
}