//
// Created by manon on 20/11/2025.
//

#ifndef MATRIX_H
#define MATRIX_H
#include "t_cell.h"

float** create_empty_matrix(int,int);

void free_matrix(float**,int);

float **create_matrix_adjac(list_adjac);

float **create_matrix_zero(int,int);

float **matrix_copy(float**,int,int);

float **multiple_matrix(float**mat_un,float**mat_deux,int n);
#endif //MATRIX_H
