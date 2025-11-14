//
// Created by manon on 24/10/2025.
//

#include "lecture.h"

#include <stdio.h>

list_adjac readGraph(const char *filename) {
    FILE *file = fopen(filename, "rt"); // read-only, text
    int nbvert, depart, arrivee;
    float proba;
    list_adjac* liste_sommet;
    // declarer la variable pour la liste d’adjacence
    if (file==NULL)
    {
        perror("Could not open file for reading");
        exit(EXIT_FAILURE);
    }
    // first line contains number of vertices
    if (fscanf(file, "%d", &nbvert) != 1)
    {
        perror("Could not read number of vertices");
        exit(EXIT_FAILURE);
    }
    liste_sommet=createListAdjac(nbvert);
   //  Initialiser une liste d’adjacence vide à partir du nombre de
   // sommets
    while (fscanf(file, "%d %d %f", &depart, &arrivee, &proba) == 3)
    {
        // on obtient, pour chaque ligne du fichier les valeurs
        // depart, arrivee, et proba
        addCellHead(arrivee,proba,liste_sommet->adjac_sommets+depart-1);
        // Ajouter l’arête qui va de ‘depart’ à ‘arrivée’ avec la
        // probabilité ‘proba’ dans la liste d’adjacence
        }
    fclose(file);
    return *liste_sommet;
}