#ifndef MATRIX_H
#define MATRIX_H
#include "t_cell.h"
#include "tarjan.h"

/* Structure de matrice de flottants : dimensions (lignes, colonnes) et tableau 2D de coefficients de type float. */
typedef struct {
    int nbLigne;
    int nbColone;
    float** matrix;
}t_matrix;
t_matrix * create_empty_matrix(int,int);

void free_matrix(t_matrix *);

t_matrix *create_matrix_adjac(list_adjac *);

t_matrix *create_matrix_zero(int,int);

t_matrix *matrix_copy(t_matrix *);

t_matrix *multiply_matrix(t_matrix * mat_un,t_matrix * mat_deux);

void displayMatrix(t_matrix * matrix);

t_matrix * matrixPuissanceN(t_matrix * matBase, int puissance);

int critèreDeDifférence(t_matrix* matBase);

t_matrix * subMatrix(t_matrix * matrix, t_partition * partition, int compo_index);

int gcd(int *vals, int nbvals);

int getPeriod(t_matrix sub_matrix);
#endif //MATRIX_H
