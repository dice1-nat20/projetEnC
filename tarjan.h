#ifndef TARJAN_H
#define TARJAN_H
#include "t_cell.h"
#include "stdio.h"


/* Structure d’un sommet pour l’algorithme de Tarjan : identifiant, indice temporel, plus petit indice accessible et marque de présence dans la pile. */
typedef struct {
    int identifiant;
    int numeroTemp;
    int numAcces;
    int boolTraitement;
}d_tergent_vertex, *l_tergent_vertex;

/* Cellule de liste chaînée contenant un pointeur vers un sommet (d_tergent_vertex) et vers la cellule suivante. */
typedef struct tergentCell{
    d_tergent_vertex* value;
    struct tergentCell *next;
}cellD_tergent;

/* Représentation d’une classe de composante fortement connexe : identifiant, nom symbolique et liste des sommets appartenant à la classe. */
typedef struct {
    int idClasse;
    char* nom;
    cellD_tergent * head;
}t_classe;

/* Pile de sommets utilisée par l’algorithme de Tarjan (chaînage par cellD_tergent). */
typedef struct {
    cellD_tergent * top;
}stack_tergent;

/* Cellule de liste chaînée pour stocker une classe dans une partition. */
typedef struct classCell {
    t_classe * value;
    struct classCell* next;
}cellClasse;

/* Partition du graphe en composantes fortement connexes : nombre total de sommets et liste chaînée des classes. */
typedef struct {
    int taille;
    cellClasse * head;
}t_partition;


d_tergent_vertex * createD_tergent(int id);
l_tergent_vertex * createL_tergent(list_adjac* Graph);
void freeL_tergent(l_tergent_vertex* listeTergent, int taille);
void displayPartition(t_partition* partition);
t_partition* tarjan(list_adjac* Graph);
t_classe * searchClasse(t_partition * partition, int compo_index);
int classeSize(t_classe* classe);
#endif //TARJAN_H
