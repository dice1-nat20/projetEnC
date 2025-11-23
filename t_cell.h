#ifndef T_CELL_H
#define T_CELL_H
#define MAX_SIZE 4
#include <stdlib.h>


/* Cellule d’une liste chaînée d’adjacence : stocke un sommet cible, la probabilité de la transition et un pointeur vers la cellule suivante. */
typedef struct t_cell {
    int sommet;
    float proba;
    struct t_cell *next;
}t_cell;

/* Liste chaînée représentant les arcs sortants d’un sommet (tête de liste de t_cell). */
typedef struct t_list {
    t_cell *head;
}t_list;

/* Structure globale d’adjacence : nombre de sommets et tableau de listes d’adjacence (une liste de successeurs par sommet du graphe de Markov). */
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

void verifMarkovGraph(list_adjac* listeAdjacence);

#endif //T_CELL_H
