#include <stdlib.h>
#include "hasse.h"


/*
void removeTransitiveLinks(t_link_array *p_link_array)
{
    int i = 0;
    while (i < p_link_array->log_size)
    {
        t_link link1 = p_link_array->links[i];
        int j = 0;
        int to_remove = 0;
        while (j < p_link_array->log_size && !to_remove)
        {
            if (j != i)
            {
                t_link link2 = p_link_array->links[j];
                if (link1.from == link2.from)
                {
                    // look for a link from link2.to to link1.to
                    int k = 0;
                    while (k < p_link_array->log_size && !to_remove)
                    {
                        if (k != j && k != i)
                        {
                            t_link link3 = p_link_array->links[k];
                            if ((link3.from == link2.to) && (link3.to == link1.to))
                            {
                                to_remove = 1;
                            }
                        }
                        k++;
                    }
                }
            }
            j++;
        }
        if (to_remove)
        {
            // remove link1 by replacing it with the last link
            p_link_array->links[i] = p_link_array->links[p_link_array->log_size - 1];
            p_link_array->log_size--;
        }
        else
        {
            i++;
        }
    }
}
*/

/* Construit un tableau associant à chaque sommet l’identifiant de la classe (composante fortement connexe) à laquelle il appartient. */
int * createListeClasseOfVertex(t_partition* partition) {
    int* tabClasseVertex = malloc(partition->taille * sizeof(int));

    cellClasse * temporaryClass = partition->head;
    while (temporaryClass != NULL) {

        cellD_tergent * temporaryVertex = temporaryClass->value->head;

        while (temporaryVertex != NULL) {
            tabClasseVertex[temporaryVertex->value->identifiant] = temporaryClass->value->idClasse;

            temporaryVertex = temporaryVertex->next;
        }

        temporaryClass = temporaryClass->next;
    }
    /*
    for (int i =0; i<partition->taille; i++) {
        printf("%d : C%d\n",i+1,tabClasseVertex[i]);
    }*/
    return tabClasseVertex;
}

/* Alloue et initialise une nouvelle arête (lien) entre deux classes pour le graphe de Hasse. */
cellLien * createLien(int idClasseDepart, int idClasseArrivee) {
    cellLien* newLien = malloc(sizeof(cellLien));
    newLien->value = malloc(sizeof(t_lien));
    newLien->value->idClasseDepart = idClasseDepart;
    newLien->value->idClasseArrivee = idClasseArrivee;
    newLien->next = NULL;
    return newLien;
}

/* Ajoute à la liste des liens du graphe de Hasse une arête entre deux classes si elle n’existe pas déjà et que ce n’est pas une boucle. */
void AddToHasse(t_hasse* listeLien, int idClasseDepart, int idClasseArrivee) {
    if (idClasseDepart != idClasseArrivee) {
        cellLien* temporaryLien = listeLien->head;
        int isInList = 0;
        while (temporaryLien != NULL && !isInList) {
            if (temporaryLien->value->idClasseDepart == idClasseDepart && temporaryLien->value->idClasseArrivee == idClasseArrivee) {
                isInList = 1;
            }
            temporaryLien = temporaryLien->next;
        }
        if (!isInList) {
            cellLien * newCellLien = createLien( idClasseDepart,  idClasseArrivee);
            newCellLien->next=listeLien->head;
            listeLien->head = newCellLien;
        }
    }
}

/* Construit le graphe de Hasse des classes à partir de la partition et du graphe : relie les classes qui sont voisines via au moins un arc du graphe initial. */
t_hasse* hasse(t_partition* partition, list_adjac* Graph) {
    t_hasse * hasseGraph = malloc(sizeof(t_hasse));
    hasseGraph->head = NULL;
    int * listClasseOfVertex = createListeClasseOfVertex(partition);

    cellClasse * temporaryClass = partition->head;
    while (temporaryClass != NULL) {

        cellD_tergent * temporaryVertex = temporaryClass->value->head;

        while (temporaryVertex != NULL) {

            t_cell* temporaryCell = Graph->adjac_sommets[temporaryVertex->value->identifiant].head;

            while (temporaryCell != NULL) {
                AddToHasse(hasseGraph,temporaryClass->value->idClasse, listClasseOfVertex[temporaryCell->sommet - 1]);
                temporaryCell = temporaryCell->next;

            }

            temporaryVertex = temporaryVertex->next;
        }

        temporaryClass = temporaryClass->next;
    }
    free(listClasseOfVertex);
    return hasseGraph;
}

/* Affiche toutes les arêtes du graphe de Hasse sous la forme “Cdepart -> Carrivee”. */
void displayHasse(t_hasse * hasseGraph) {
    cellLien *tempHasse = hasseGraph->head;
    while (tempHasse != NULL) {
        printf("C%d -> C%d\n", tempHasse->value->idClasseDepart, tempHasse->value->idClasseArrivee);
        tempHasse = tempHasse->next;
    }

}

/* Détermine pour chaque classe (et les états qu’elle contient) si elle est persistante ou transitoire, affiche ces caractéristiques et indique si le graphe est irréductible. */
void displayHasseCarac(t_hasse* hasseGraph, t_partition * partition) {
    cellClasse * temporaryClasse = partition->head;
    int irreductible = 0;
    if (temporaryClasse->next == NULL) {
        irreductible = 1;
    }
    while (temporaryClasse != NULL) {
        int persistante = 1;
        cellLien *tempHasse = hasseGraph->head;
        while (tempHasse != NULL) {
            if (tempHasse->value->idClasseDepart == temporaryClasse->value->idClasse) {
                persistante = 0;
            }
            tempHasse = tempHasse->next;
        }
        printf("\nLa classe C%d est ", temporaryClasse->value->idClasse);
        if (persistante) {
            printf("persistante - ");
        }
        else {
            printf("transitoire - ");
        }
        cellD_tergent * temporaryVertex = temporaryClasse->value->head;
        if (temporaryVertex->next == NULL) {
            printf("l'état %d est ", temporaryVertex->value->identifiant+1);
            if (persistante) {
                printf("persistant – l'état %d est absorbant ;", temporaryVertex->value->identifiant+1);
            }
            else {
                printf("transitoire ;");
            }
        }
        else {
            printf("les états ");
            while (temporaryVertex != NULL) {
                printf("%d",temporaryVertex->value->identifiant+1);
                if (temporaryVertex->next != NULL) {
                    if (temporaryVertex->next->next != NULL) {
                        printf(", ");
                    }
                    else {
                        printf(" et ");
                    }
                }
                temporaryVertex = temporaryVertex->next;
            }
            if (persistante) {
                printf(" sont persistants ;");
            }
            else {
                printf(" sont transitoires ;");
            }
        }
        temporaryClasse = temporaryClasse->next;
    }
    if (irreductible) {
        printf("\nLe graphe de Markov est irréductible ;\n");
    }
    else {
        printf("\nLe graphe de Markov n'est pas irréductible ;\n");
    }
    printf("\n");
}



