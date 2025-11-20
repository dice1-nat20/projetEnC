#include <stdio.h>
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
    for (int i = 0; i < listeAdjacence->taille; i++) {
        t_cell* temporaryCell = listeAdjacence->adjac_sommets[i].head;
        while (temporaryCell != NULL) {
            fprintf(f, "\n%s -->|%g|", getID(i + 1), temporaryCell->proba);
            fprintf(f, "%s", getID(temporaryCell->sommet));
            temporaryCell = temporaryCell->next;
        }
    }
    fclose(f);
    printf("Fichier \"exemple_valid_step3.txt\" cree avec succes \n");
    return;
}

void CreateMermaidPartition(t_partition * partition, t_hasse * hasse) {
    FILE *f = fopen("exemple_valid_partition_hasse.txt", "w");
    if (f == NULL) {
        printf("Erreur de creation du fichier");
        return;
    }

    fprintf(f, "---\nconfig:\nlayout: elk\ntheme: neo\nlook: neo\n---\n\nflowchart LR\n");
    cellClasse * temporaryClasse = partition->head;
    while (temporaryClasse != NULL) {
        fprintf(f,"%s((",getID(temporaryClasse->value->idClasse));
        cellD_tergent * temporaryVertex = temporaryClasse->value->head;
        fprintf(f,"\"{");
        while (temporaryVertex != NULL) {
            fprintf(f,"%d", temporaryVertex->value->identifiant+1);
            if (temporaryVertex->next != NULL) {
                fprintf(f,", ");
            }
            temporaryVertex = temporaryVertex->next;
        }
        fprintf(f,"}\"))\n");
        temporaryClasse = temporaryClasse->next;
    }
    cellLien * temporaryLien = hasse->head;
    while (temporaryLien != NULL) {
        fprintf(f,"\n%s --> ",getID(temporaryLien->value->idClasseDepart));
        fprintf(f,"%s",getID(temporaryLien->value->idClasseArrivee));
        temporaryLien =temporaryLien->next;
    }
    fclose(f);
    printf("Fichier \"exemple_valid_partition_hasse.txt\" cree avec succes \n");
    return;
}