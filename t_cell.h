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
}t_list;

typedef struct list_adjac {
    int taille;
    t_list *adjac_sommets;
}list_adjac;


t_cell* createCell(int sommet,float proba);

t_list createEmptyList();

void addCellHead(int sommet,float proba,t_list* l);

void displayList(t_list* l);

void displayListAdjac(list_adjac* la);

list_adjac* createListAdjac(int taille);


#endif //T_CELL_H
