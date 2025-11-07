#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

static char *getID(int i)
{
    // translate from 1,2,3, .. ,500+ to A,B,C,..,Z,AA,AB,...
    static char buffer[10];
    char temp[10];
    int index = 0;

    i--; // Adjust to 0-based index
    while (i >= 0)
    {
        temp[index++] = 'A' + (i % 26);
        i = (i / 26) - 1;
    }

    // Reverse the string to get the correct order
    for (int j = 0; j < index; j++)
    {
        buffer[j] = temp[index - j - 1];
    }
    buffer[index] = '\0';

    return buffer;
}

void CreateMermaidGraph(list_adjac* listeAdjacence) {
        FILE *f = fopen("exemple_valid_step3.txt", "w");
    if (f == NULL) {
        printf("Erreur de creation du fichier");
        return;
    }

    fprintf(f, "---\nconfig:\nlayout: elk\ntheme: neo\nlook: neo\n---\n\nflowchart LR\n");
    for (int i = 0; i < listeAdjacence->taille ; i++) {
        fprintf(f,"%s((%d))\n",getID(i+1),i+1);
    }
    for (int i = 0; i < listeAdjacence->taille ; i++) {
        t_cell* temporaryCell = listeAdjacence->adjac_sommets->head;
        while (temporaryCell != NULL) {
            fprintf(f,"\n%s -->|%f|%s",getID(i+1),temporaryCell->proba,getID(temporaryCell->sommet+1));
            temporaryCell = temporaryCell->next;
        }
    }
    fclose(f);
    printf("Fichier \"exemple_valid_step3.txt\" cree avec succes \n");
    return;
}