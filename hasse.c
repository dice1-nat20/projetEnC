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

cellLien * createLien(int idClasseDepart, int idClasseArrivee) {
    cellLien* newLien = malloc(sizeof(cellLien));
    newLien->value = malloc(sizeof(t_lien));
    newLien->value->idClasseDepart = idClasseDepart;
    newLien->value->idClasseArrivee = idClasseArrivee;
    newLien->next = NULL;
    return newLien;
}

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
    cellLien *temphasse = hasseGraph->head;
    while (temphasse != NULL) {
        printf("C%d -> C%d\n", temphasse->value->idClasseDepart, temphasse->value->idClasseArrivee);
        temphasse = temphasse->next;
    }
    return hasseGraph;
}



