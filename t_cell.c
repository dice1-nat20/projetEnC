//
// Created by manon on 24/10/2025.
//

#include "t_cell.h"
#include <stdio.h>


t_cell* createCell(int sommet,float proba) {
    t_cell* newCell = (t_cell*) malloc(sizeof(t_cell));
    newCell->sommet = sommet;
    newCell->proba = proba;
    return newCell;
}

t_list createEmptyList() {
    t_list myList;
    myList.head = NULL;
    return myList;
}

void addCellHead(int sommet,float proba,t_list* l) {
    t_cell* newCell = createCell(sommet,proba);
    newCell->next = l->head;
    l->head = newCell;
}

void displayList(t_list* l) {
    printf("[head @] ");

    t_cell* temporaryCell = l->head;
    while (temporaryCell->next != NULL) {
        printf("@-> (%d, %f) ", temporaryCell->sommet, temporaryCell->proba);
        temporaryCell = temporaryCell->next;
    }
    printf("\n");
}

void displayListAdjac(list_adjac* la) {
    printf("[");
    for (int i = 0; i < la->taille ; i++) {
        printf("Liste pour le sommet %d:", i);
        displayList(la->adjac_sommets+i);
    }
    printf("]");
}

list_adjac* createListAdjac(int taille) {
    list_adjac* myAdjacList = (list_adjac*) malloc(sizeof(list_adjac));
    myAdjacList->taille = taille;
    myAdjacList->adjac_sommets = malloc(sizeof(t_list)*taille);
    return myAdjacList;
}