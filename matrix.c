//
// Created by manon on 20/11/2025.
//

#include "matrix.h"
#include "tarjan.h"


t_matrix * create_empty_matrix(int nb_ligne, int nb_col) {
    t_matrix *mat = malloc(sizeof(t_matrix));
    float **tab = malloc(nb_ligne * sizeof(float*));
    for (int i = 0; i < nb_ligne; i++) {
        tab[i] = malloc(nb_col * sizeof(float));
    }
    mat->nbLigne = nb_ligne;
    mat->nbColone = nb_col;
    mat->matrix = tab;
    return mat;
}

void free_matrix(t_matrix *mat) {
    if (mat != NULL) {
        for (int i = 0; i < mat->nbLigne; i++) {
            free(mat->matrix[i]);
        }
        free(mat->matrix);
        free(mat);
    }
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

t_matrix *create_matrix_zero(int ligne, int col) {
    t_matrix *mat = create_empty_matrix(ligne, col);
    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < col; j++) {
            mat->matrix[i][j] = 0;
        }
    }
    return mat;
}

t_matrix *matrix_copy(t_matrix *mat) {
    t_matrix *copy = create_empty_matrix(mat->nbLigne, mat->nbColone);
    for (int i = 0; i < mat->nbLigne; i++) {
        for (int j = 0; j < mat->nbColone; j++) {
            copy->matrix[i][j] = mat->matrix[i][j];
        }
    }
    return copy;
}

t_matrix *multiple_matrix(t_matrix *mat_un, t_matrix *mat_deux) {
    t_matrix *mat = create_empty_matrix(mat_un->nbLigne, mat_deux->nbColone);
    float x;
    for (int i = 0; i < mat_un->nbLigne; i++) {
        for (int j = 0; j < mat_deux->nbColone; j++) {
            x = 0;
            for (int k = 0; k < mat_un->nbColone; k++) {
                x += mat_un->matrix[i][k] * mat_deux->matrix[k][j];
            }
            mat->matrix[i][j] = x;
        }
    }
    return mat;
}

t_matrix *diff_matrix(t_matrix *mat_un, t_matrix *mat_deux) {
    t_matrix *matrix = create_empty_matrix(mat_un->nbLigne, mat_un->nbColone);
    for (int i = 0; i < mat_un->nbLigne; i++) {
        for (int j = 0; j < mat_un->nbColone; j++) {
            float x = mat_un->matrix[i][j] - mat_deux->matrix[i][j];
            matrix->matrix[i][j] = x < 0 ? -x : x;
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
    printf("\n");
}

t_matrix * matrixPuissanceN(t_matrix * matBase, int puissance) {
    t_matrix * matMultiple = matrix_copy(matBase);
    for (int i = 0; i<puissance; i++) {
        t_matrix * tempMatrix = matMultiple;
        matMultiple = multiple_matrix(matBase, matMultiple);
        free_matrix(tempMatrix);
    }
    return matMultiple;
}

int verifDifférence(t_matrix * mat_un, t_matrix * mat_deux) {
    if (mat_un != NULL && mat_deux !=NULL) {
        t_matrix* matDifference = diff_matrix(mat_un, mat_deux);
        for (int i = 0; i < mat_un->nbLigne; i++) {
            for (int j = 0; j < mat_un->nbColone; j++) {
                if (matDifference->matrix[i][j]> 0.01) {
                    free_matrix(matDifference);
                    return 0;
                }
            }
        }
        free_matrix(matDifference);
        return 1;
    }
    return 0;
}

int critèreDeDifférence(t_matrix* matBase) {
    t_matrix * matMultiple = matrix_copy(matBase);
    t_matrix * matPrecedente = NULL;
    int i = 1;
    while (i<50 && !verifDifférence(matMultiple, matPrecedente)){
        t_matrix * tempMatrix = matPrecedente;
        matPrecedente = matMultiple;
        matMultiple = multiple_matrix(matBase, matMultiple);
        free_matrix(tempMatrix);
        i++;
    }
    if (i>=50) {
        printf("Cette Matrice ne remplie pas le critère de différence à n = 50;");
    }
    printf("Matrice obtenue à n = %d : \n",i);
    displayMatrix(matMultiple);
    free_matrix(matMultiple);
    return i;
}



t_matrix * subMatrix(t_matrix * matrix, t_partition * partition, int compo_index) {
    t_classe * classeExtracted = searchClasse(partition, compo_index);
    int classeLength = classeSize(classeExtracted);
    t_matrix * newMartix = create_matrix_zero(classeLength,classeLength);
    return newMartix;
}