//
// Created by manon on 14/11/2025.
//

#ifndef TARJAN_H
#define TARJAN_H
#include "t_cell.h"
#include "stdio.h"

typedef struct {
    int identifiant;
    int numeroTemp;
    int numAcces;
    int boolTraitement;
}d_tergent_vertex, *l_tergent_vertex;

typedef struct tergentCell{
    d_tergent_vertex* value;
    struct tergentCell *next;
}cellD_tergent;

typedef struct {
    char* nom;
    cellD_tergent * head;
}t_classe;

typedef struct {
    cellD_tergent * top;
}stack_tergent;

typedef struct classCell {
    t_classe * value;
    struct classCell* next;
}cellClasse;

typedef struct {
    cellClasse * head;
}t_partition;

d_tergent_vertex * createD_tergent(int id);
l_tergent_vertex * createL_tergent(list_adjac* Graph);
void freeL_tergent(l_tergent_vertex* listeTergent, int taille);
void displayPartition(t_partition* partition);
t_partition* tarjan(list_adjac* Graph);
#endif //TARJAN_H
