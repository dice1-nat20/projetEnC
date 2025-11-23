#include <string.h>
#include "tarjan.h"


/* Crée et initialise le tableau des sommets (structure tergent) à partir du graphe. */
l_tergent_vertex* createL_tergent(list_adjac* Graph) {
    l_tergent_vertex* Tab = malloc(Graph->taille * sizeof(d_tergent_vertex*));
    for (int i = 0; i < Graph->taille; i++) {
        Tab[i] = malloc(sizeof(d_tergent_vertex));
        Tab[i]->identifiant = i;
        Tab[i]->numeroTemp = -1;
        Tab[i]->numAcces = -1;
        Tab[i]->boolTraitement = 0;
    }
    return Tab;
}

/* Libère en mémoire le tableau de sommets tergent et met le pointeur à NULL. */
void freeL_tergent(l_tergent_vertex* listeTergent, int taille){
    for (int i = 0; i<taille; i++) {
        free(listeTergent[i]);
    }
    free(listeTergent);
    listeTergent = NULL;
}

/* Empile un sommet (vertex) dans la pile utilisée par l’algorithme de Tarjan. */
void push_tergent(stack_tergent* stack, d_tergent_vertex* vertex) {
    cellD_tergent* cell = malloc(sizeof *cell);
    cell->value = vertex;
    cell->next = stack->top;
    stack->top = cell;
}

/* Crée et initialise une pile vide pour l’algorithme de Tarjan. */
stack_tergent* create_tergent_stack() {
    stack_tergent* stack = malloc(sizeof *stack);
    if (!stack) return NULL;
    stack->top = NULL;
    return stack;
}

/* Dépile et renvoie le sommet en haut de la pile de Tarjan (ou NULL si pile vide). */
d_tergent_vertex* pop_tergent(stack_tergent* stack) {
    if (!stack->top) return NULL;
    cellD_tergent* cell = stack->top;
    d_tergent_vertex* vertex = cell->value;
    stack->top = cell->next;
    free(cell);
    return vertex;
}

/* Crée une nouvelle classe de composante fortement connexe identifiée par un numéro. */
t_classe* create_classe(int numero) {
    t_classe* classe = malloc(sizeof *classe);
    if (!classe) return NULL;
    classe->head = NULL;
    classe->idClasse = numero;
    classe->nom = malloc(16);
    snprintf(classe->nom, sizeof(classe->nom), "%c%d", 'C', numero);;
    return classe;
}

/* Ajoute un sommet à la classe (composante fortement connexe) donnée. */
void add_to_classe(t_classe* classe, d_tergent_vertex* v) {
    cellD_tergent* cell = malloc(sizeof *cell);
    if (!cell) return;
    cell->value = v;
    cell->next = classe->head;
    classe->head = cell;
}

/* Libère en mémoire une classe et tous les sommets qu’elle contient. */
void free_classe(t_classe* classe) {
    cellD_tergent* temporaryCell = classe->head;
    while (temporaryCell != NULL) {
        cellD_tergent* next = temporaryCell->next;
        free(temporaryCell->value);

        free(temporaryCell);
        temporaryCell = next;
    }
    free(classe->nom);
    free(classe);
}

/* Crée une partition vide (liste de classes de composantes fortement connexes). */
t_partition* create_partition() {
    t_partition* p = malloc(sizeof *p);
    if (!p) return NULL;
    p->head = NULL;
    return p;
}

/* Ajoute une classe à la partition (en tête de la liste chaînée). */
void add_classe_to_partition(t_partition* p, t_classe* c) {
    cellClasse* cell = malloc(sizeof *cell);
    if (!cell) return;
    cell->value = c;
    cell->next = p->head;
    p->head = cell;
}

/* Libère toute la partition et l’ensemble des classes qu’elle contient. */
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
/* Parcours récursif de Tarjan sur un sommet : calcule numéros temporels, numéros d’accès et forme les composantes fortement connexes. */
void parcours(d_tergent_vertex* vertex, l_tergent_vertex* listeVertex, int *num, stack_tergent* stack, list_adjac* Graph, t_partition* partition, int* nomClasse) {
    vertex->numeroTemp = *num;
    vertex->numAcces = *num;
    (*num)++;
    push_tergent(stack, vertex);
    vertex->boolTraitement =1;

    t_cell* temporaryCell = Graph->adjac_sommets[vertex->identifiant].head;
    while (temporaryCell != NULL) {
        if (listeVertex[temporaryCell->sommet-1]->numeroTemp == -1) {
            parcours(listeVertex[temporaryCell->sommet-1],listeVertex,num,stack,Graph,partition, nomClasse);

            if (listeVertex[temporaryCell->sommet-1]->numAcces  <  vertex->numAcces) {
                vertex->numAcces = listeVertex[temporaryCell->sommet-1]->numAcces;
            }
        }
        else {
            if (listeVertex[temporaryCell->sommet-1]->boolTraitement == 1) {
                if (listeVertex[temporaryCell->sommet-1]->numeroTemp  <  vertex->numAcces) {
                    vertex->numAcces = listeVertex[temporaryCell->sommet-1]->numeroTemp;
                }
            }
        }
        temporaryCell = temporaryCell->next;
    }

    if (vertex->numeroTemp == vertex->numAcces) {
        t_classe* classe = create_classe(*nomClasse);
        (*nomClasse)++;
        d_tergent_vertex * temporaryvertex;
        do {
            temporaryvertex = pop_tergent(stack);
            temporaryvertex->boolTraitement = 0;
            add_to_classe(classe, temporaryvertex);
        } while (vertex != temporaryvertex);
        add_classe_to_partition(partition, classe);
    }
}

/* Applique l’algorithme de Tarjan sur le graphe pour calculer la partition en composantes fortement connexes. */
t_partition* tarjan(list_adjac* Graph) {
    l_tergent_vertex *listeVertex = createL_tergent(Graph);
    int num =0;
    int nomClasse = 1;
    stack_tergent* stack= create_tergent_stack();
    t_partition * partition = create_partition();
    partition->taille = Graph->taille;
    for (int i = 0; i<Graph->taille; i++){
        if (listeVertex[i]->numeroTemp == -1) {
            parcours(listeVertex[i],listeVertex,&num,stack,Graph,partition,&nomClasse);
        }
    }
    free(stack);
    free(listeVertex); // Attention ici il ne faut pas liberer les cellules, juste la liste (je crois)
    return partition;
}

/* Affiche le contenu d’une classe (ensemble des sommets) au format {1,2,...}. */
void displayClasse(t_classe* classe) {
    printf("{");
    cellD_tergent * temporaryVertex = classe->head;
    while (temporaryVertex != NULL) {
        printf("%d",temporaryVertex->value->identifiant+1);
        if (temporaryVertex->next != NULL) {
            printf(",");
        }
        temporaryVertex = temporaryVertex->next;
    }
    printf("}\n");
}

/* Affiche l’ensemble de la partition : nom de la classe puis ses sommets. */
void displayPartition(t_partition* partition) {
    cellClasse * temporaryClass = partition->head;
    while (temporaryClass != NULL) {
        printf(temporaryClass->value->nom);
        displayClasse(temporaryClass->value);
        temporaryClass = temporaryClass->next;
    }
}

/* Recherche et renvoie une classe de la partition par son identifiant logique. */
t_classe * searchClasse(t_partition * partition, int compo_index) {
    cellClasse* temporaryClasse = partition->head;
    while (temporaryClasse != NULL) {
        if (temporaryClasse->value->idClasse == compo_index) {
            return temporaryClasse->value;
        }
        temporaryClasse = temporaryClasse->next;
    }
    printf("La classe spécifiée n'a pas été trouvée.");
    return NULL;
}

/* Calcule et renvoie la taille (nombre de sommets) d’une classe. */
int classeSize(t_classe* classe) {
    int size = 0;
    cellD_tergent* temporaryVertex = classe->head;
    while (temporaryVertex != NULL) {
        size ++;
        temporaryVertex = temporaryVertex->next;
    }
    return size;
}

/* Indique si un sommet (idVertex) appartient à la classe donnée (1 si oui, 0 sinon). */
int isInClasse(t_classe* classe, int idVertex) {
    cellD_tergent * temporaryCell = classe->head;
    while (temporaryCell != NULL) {
        if (idVertex == temporaryCell->value->identifiant) {
            return 1;
        }
        temporaryCell = temporaryCell->next;
    }
    return 0;
}