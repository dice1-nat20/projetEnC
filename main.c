#include <windows.h>
#include "lecture.h"
#include "utils.h"
#include "hasse.h"
#include "utils.h"
#include "matrix.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    list_adjac * list1 = readGraph("data/exemple_meteo.txt");
    displayListAdjac(list1);
    //CreateMermaidGraph(list1);
    verifMarkovGraph(list1);
    t_partition* graphTarjan = tarjan(list1);
    displayPartition(graphTarjan);
    t_hasse * graphHasse = hasse(graphTarjan,list1);
    displayHasseCarac(graphHasse, graphTarjan);
    //CreateMermaidPartition(graphTarjan, graphHasse);
    t_matrix *matrix1 = create_matrix_adjac(list1);
    //printf("M^3 : \n");
    //displayMatrix(matrixPuissanceN(matrix1,3));
    //printf("M^7 : \n");
    //displayMatrix(matrixPuissanceN(matrix1,7)); // correcte à des erreurs d'arrondi près.
    printf("La différence entre M^n et M^n+1 devient inférieur à 0.01 à partir de n = %d",critèreDeDifférence(matrix1));
    cellClasse * currentClassCell = graphTarjan->head;
    while (currentClassCell != NULL) {
        t_classe * classeActuelle = currentClassCell->value;
        int id = classeActuelle->idClasse;

        printf("\n--- Classe %s (ID: %d) ---\n", classeActuelle->nom, id);

        t_matrix * subMat = subMatrix(matrix1, graphTarjan, id);
        if (subMat != NULL) {
            displayMatrix(subMat);
            critèreDeDifférence(subMat);
            free_matrix(subMat);
        }
        currentClassCell = currentClassCell->next;
    }
    return 0;

}
