//
// Created by manon on 20/11/2025.
//

#ifndef MATRIX_H
#define MATRIX_H
#include "t_cell.h"
#include <stdio.h>

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

t_matrix *multiple_matrix(t_matrix * mat_un,t_matrix * mat_deux);

void displayMatrix(t_matrix * matrix);

t_matrix * matrixPuissanceN(t_matrix * matBase, int puissance);

int critèreDeDifférence(t_matrix* matBase);
#endif //MATRIX_H
