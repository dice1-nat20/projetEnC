//
// Created by manon on 20/11/2025.
//

#include "matrix.h"

float** create_empty_matrix(int nb_ligne, int nb_col) {
    float **mat=malloc(nb_col*sizeof(float**));
    for (int i=0;i<=nb_col;i++) {
        mat[i]=malloc(nb_ligne*sizeof(float*));
    }
    return mat;
}

void free_matrix(float **mat,int nb_col) {
    for (int i=0;i<=nb_col;i++) free(mat[i]);
    free(mat);
}

float **create_matrix_adjac(list_adjac liste) {
    float **mat=create_empty_matrix(liste.taille,liste.taille);
    for (int i=0;i<=liste.taille;i++) {
        for (int j=0;j<=liste.taille;j++) {
            if (liste.adjac_sommets->head->next!=NULL) {
                if (liste.adjac_sommets->head->next->sommet==j) {
                    mat[i][j]=liste.adjac_sommets->head->proba;
                }
                else {
                    mat[i][j]=0;
                }
                liste.adjac_sommets->head=liste.adjac_sommets->head->next;
            }
            else {
                mat[i][j]=0;
            }
        }
    }
    return mat;
}

float **create_matrix_zero(int ligne,int col) {
    float **mat=create_empty_matrix(ligne,col);
    for (int i=0;i<=col;i++) {
        for (int j=0;j<=ligne;j++) {
            mat[i][j]=0;
        }
    }
    return mat;
}

float **matrix_copy(float **mat,int ligne,int col) {
    float **matrix=create_empty_matrix(ligne,col);
    for (int i=0;i<=col;i++) {
        for (int j=0;j<=ligne;j++) {
            matrix[i][j]=mat[i][j];
        }
    }
    return matrix;
}

float **multiple_matrix(float**mat_un,float**mat_deux,int n) {
    float** mat=create_empty_matrix(n,n);
    float x=0;
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=n;j++) {
            x=0;
            for (int k=0;k<=n;k++) {
                x=x+mat_un[j][k]*mat_deux[k][j];
            }
            mat[i][j]=x;
        }
    }
    return mat;
}

float **diff_matrix(float**mat_un,float**mat_deux,int n) {
    float **matrix=create_empty_matrix(n,n);
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=n;j++) {
            matrix[i][j]=mat_un[i][j]-mat_deux[i][j];
            if (matrix[i][j]<0) matrix[i][j]=-matrix[i][j];
        }
    }
    return matrix;
}
