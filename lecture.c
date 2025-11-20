//
// Created by manon on 24/10/2025.
//

#include "lecture.h"

#include <stdio.h>

list_adjac* readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt");
    if (!file) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    int nbvert, depart, arrivee;
    float proba;
    if (fscanf(file, "%d", &nbvert) != 1) {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }

    list_adjac* liste_sommet = createListAdjac(nbvert);

    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3) {
        addCellHead(arrivee, proba, &liste_sommet->adjac_sommets[depart-1]);
    }

    fclose(file);
    return liste_sommet;
}