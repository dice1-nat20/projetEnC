//
// Created by manon on 20/11/2025.
//

#include "matrix.h"


t_matrix * create_empty_matrix(int nb_ligne, int nb_col) {
    t_matrix * mat = malloc(sizeof(t_matrix));
    float **tab=malloc(nb_col*sizeof(float**));
    for (int i=0;i<=nb_col;i++) {
        tab[i]=malloc(nb_ligne*sizeof(float*));
    }
    mat->nbColone = nb_col;
    mat->nbLigne = nb_ligne;
    mat->matrix= tab;
    return mat;
}

void free_matrix(t_matrix *mat) {
    for (int i=0;i<=mat->nbColone;i++) free(mat->matrix[i]);
    free(mat);
}

t_matrix * create_matrix_adjac(list_adjac * liste) {
    t_matrix * mat=create_matrix_zero(liste->taille,liste->taille);
    for (int i=0;i<liste->taille;i++) {
        for (int j=0;j<liste->taille;j++) {
            t_cell* temporaryCell = liste->adjac_sommets[i].head;
            while (temporaryCell!=NULL) {
                if (temporaryCell->sommet == j+1) {
                    mat->matrix[i][j] = temporaryCell->proba;
                }
                temporaryCell = temporaryCell->next;
            }

        }
    }
    return mat;
}

t_matrix *create_matrix_zero(int ligne,int col) {
    t_matrix * mat=create_empty_matrix(ligne,col);
    for (int i=0;i<=col;i++) {
        for (int j=0;j<=ligne;j++) {
            mat->matrix[i][j]=0;
        }
    }
    return mat;
}

t_matrix *matrix_copy(t_matrix * mat) {
    t_matrix *matrix=create_empty_matrix(mat->nbLigne,mat->nbColone);
    for (int i=0;i<=mat->nbLigne;i++) {
        for (int j=0;j<=mat->nbColone;j++) {
            matrix->matrix[i][j]=mat->matrix[i][j];
        }
    }
    return matrix;
}

t_matrix *multiple_matrix(t_matrix *mat_un,t_matrix *mat_deux) {
    t_matrix * mat=create_empty_matrix(mat_un->nbLigne,mat_un->nbColone);
    float x=0;
    for (int i=0;i<=mat_un->nbLigne;i++) {
        for (int j=0;j<=mat_un->nbColone;j++) {
            x=0;
            for (int k=0;k<=mat_deux->nbLigne;k++) {
                x=x+mat_un->matrix[j][k]*mat_deux->matrix[k][j];
            }
            mat->matrix[i][j]=x;
        }
    }
    return mat;
}

t_matrix *diff_matrix(t_matrix * mat_un,t_matrix *mat_deux,int n) {
    t_matrix * matrix=create_empty_matrix(n,n);
    for (int i=0;i<=n;i++) {
        for (int j=0;j<=n;j++) {
            matrix->matrix[i][j]=mat_un->matrix[i][j]-mat_deux->matrix[i][j];
            if (matrix->matrix[i][j]<0) matrix->matrix[i][j]=-matrix->matrix [i][j];
        }
    }
    return matrix;
}


void displayMatrix(t_matrix * matrix) {
    for (int i=0;i<matrix->nbLigne;i++) {
        printf("(");
        for (int j=0;j<matrix->nbColone;j++) {
            printf("%5.2f",matrix->matrix[i][j]);
            if (j<matrix->nbColone-1) {
                printf(",");
            }
        }
        printf(")\n");
    }
}