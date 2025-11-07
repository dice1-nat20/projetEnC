//
// Created by manon on 24/10/2025.
//

#include "t_cell.h"
#include <stdio.h>


t_cell* createCell(int sommet,float proba) {
    t_cell* newCell = (t_cell*) malloc(sizeof(t_cell));
    newCell->sommet = sommet;
    newCell->proba = proba;
    newCell->next = NULL;
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
    while (temporaryCell != NULL) {
        printf("@-> (%d, %f) ", temporaryCell->sommet, temporaryCell->proba);
        temporaryCell = temporaryCell->next;
    }
    printf("\n");
}

void displayListAdjac(list_adjac* la) {
    printf("[");
    for (int i = 0; i < la->taille ; i++) {
        printf("Liste pour le sommet %d:", i+1);
        displayList(la->adjac_sommets+i);
    }
    printf("]\n");
}

list_adjac* createListAdjac(int taille) {
    list_adjac* myAdjacList = (list_adjac*) malloc(sizeof(list_adjac));
    myAdjacList->taille = taille;
    myAdjacList->adjac_sommets = malloc(sizeof(t_list)*taille);
    for (int i = 0; i<taille; i++) {
        myAdjacList->adjac_sommets[i].head = NULL;
    }
    return myAdjacList;
}

float verifMarkovList(t_list* listeSommet) {
    float probTotale = 0;
    t_cell* temporaryCell = listeSommet->head;
    while (temporaryCell != NULL) {
        probTotale +=  temporaryCell->proba;
        temporaryCell = temporaryCell->next;
    }
    return probTotale;
}

void verifMarkovGraph(list_adjac* listeAdjacence){
    int isMarkov = 1;
    for (int i = 0; i < listeAdjacence->taille ; i++) {
        float probTotale = verifMarkovList(listeAdjacence->adjac_sommets+i);
        if (!(probTotale>=0.99 && probTotale<= 1)){
            printf("La somme des probabilites du sommet %d est %f.\n",i+1, probTotale);
            isMarkov = 0;
        }
    }
    if (isMarkov) {
        printf("Le graphe est un graphe de Markov. \n");
        return;
    }
    printf("Le graphe n est pas un graphe de Markov.\n");
    return;
}