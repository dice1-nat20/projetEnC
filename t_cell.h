//
// Created by manon on 24/10/2025.
//

#ifndef T_CELL_H
#define T_CELL_H

#define MAX_SIZE 4
#include <stdlib.h>

typedef struct t_cell {
    int sommet;
    float proba;
    struct t_cell *next;
}t_cell;

typedef struct t_list {
    t_cell *head;
    t_cell arretes[MAX_SIZE];
}t_list;

typedef struct list_adjac {
    int taille;
    t_list *adjac_sommets = (t_list*) malloc(taille*sizeof(t_list));
}list_adjac;
#endif //T_CELL_H
