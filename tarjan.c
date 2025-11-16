//
// Created by manon on 14/11/2025.
//
#include <string.h>
#include "tarjan.h"

d_tergent_vertex * createD_tergent(int id) {
    d_tergent_vertex* nouvSommet = malloc(sizeof(d_tergent_vertex));
    nouvSommet->identifiant = id;
    nouvSommet->numeroTemp = -1;
    nouvSommet->numAcces = -1;
    nouvSommet->boolTraitement = 0;
    return nouvSommet;
}

l_tergent_vertex * createL_tergent(list_adjac* Graph) {
    l_tergent_vertex* Tab = (l_tergent_vertex*)malloc(Graph->taille * sizeof(d_tergent_vertex*));
    for (int i = 0; i<Graph->taille; i++) {
        Tab[i] = createD_tergent(i);
    }
    return Tab;
}

void freeL_tergent(l_tergent_vertex* listeTergent, int taille){
    for (int i = 0; i<taille; i++) {
        free(listeTergent[i]);
    }
    free(listeTergent);
    listeTergent = NULL;
}

void push_tergent(stack_tergent* stack, d_tergent_vertex* vertex) {
    cellD_tergent* cell = malloc(sizeof *cell);
    cell->value = vertex;
    cell->next = stack->top;
    stack->top = cell;
}

stack_tergent* create_tergent_stack() {
    stack_tergent* stack = malloc(sizeof *stack);
    if (!stack) return NULL;
    stack->top = NULL;
    return stack;
}

d_tergent_vertex* pop_tergent(stack_tergent* stack) {
    if (!stack->top) return NULL;
    cellD_tergent* cell = stack->top;
    d_tergent_vertex* vertex = cell->value;
    stack->top = cell->next;
    free(cell);
    return vertex;
}

t_classe* create_classe(const char* nom) {
    t_classe* classe = malloc(sizeof *classe);
    if (!classe) return NULL;
    classe->head = NULL;
    classe->nom = strdup(nom);
    return classe;
}

void add_to_classe(t_classe* classe, d_tergent_vertex* v) {
    cellD_tergent* cell = malloc(sizeof *cell);
    if (!cell) return;
    cell->value = v;
    cell->next = classe->head;
    classe->head = cell;
}

void free_classe(t_classe* classe) {
    cellD_tergent* temporaryCell = classe->head;
    while (temporaryCell != NULL) {
        cellD_tergent* next = temporaryCell->next;
        free(temporaryCell);
        temporaryCell = next;
    }
    free(classe->nom);
    free(classe);
}

t_partition* create_partition() {
    t_partition* p = malloc(sizeof *p);
    if (!p) return NULL;
    p->head = NULL;
    return p;
}

void add_classe_to_partition(t_partition* p, t_classe* c) {
    cellClasse* cell = malloc(sizeof *cell);
    if (!cell) return;
    cell->value = c;
    cell->next = p->head;
    p->head = cell;
}

void free_partition(t_partition* p) {
    cellClasse* cur = p->head;
    while (cur) {
        cellClasse* next = cur->next;
        free_classe(cur->value);
        free(cur);
        cur = next;
    }
    free(p);
}

void parcours(d_tergent_vertex* vertex,l_tergent_vertex listeVertex, int *num, stack_tergent* stack, list_adjac* Graph, t_partition* partition) {
    vertex->numeroTemp = *num;
    vertex->numAcces = *num;
    num+=1;
    push_tergent(stack, vertex);
    vertex->boolTraitement =1;

    t_cell* temporaryCell = Graph->adjac_sommets[vertex->identifiant].head;
    while (temporaryCell != NULL) {
        if (listeVertex[temporaryCell->sommet].numeroTemp == -1) {
            parcours(&listeVertex[temporaryCell->sommet],listeVertex,num,stack,Graph,partition);
            if (listeVertex[temporaryCell->sommet].numAcces  <  vertex->numAcces) {
                vertex->numAcces = listeVertex[temporaryCell->sommet].numAcces;
            }
        }
        else {
            if (listeVertex[temporaryCell->sommet].boolTraitement == 1) {
                if (listeVertex[temporaryCell->sommet].numeroTemp  <  vertex->numAcces) {
                    vertex->numAcces = listeVertex[temporaryCell->sommet].numeroTemp;
                }
            }
        }
        temporaryCell = temporaryCell->next;
    }
    if (vertex->numeroTemp == vertex->numAcces) {
        t_classe* classe = create_classe("test");
        d_tergent_vertex * temporaryvertex;
        do {
            temporaryvertex = pop_tergent(stack);
            temporaryvertex->boolTraitement = 0;
            add_to_classe(classe, temporaryvertex);
        } while (vertex != temporaryvertex);
        add_classe_to_partition(partition, classe);
    }
}


t_partition* tarjan(list_adjac* Graph) {
    l_tergent_vertex *listeVertex = createL_tergent(Graph);
    int num =0;
    stack_tergent* stack= create_tergent_stack();
    t_partition * partition = create_partition();
    for (int i = 0; i<Graph->taille; i++){
        if (listeVertex[i]->numeroTemp == -1) {
            parcours(listeVertex[i],listeVertex,&num,stack,Graph,partition);
        }
    }
}
