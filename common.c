#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// -------------------------------------------
// 入力データ標準化変換
// -------------------------------------------
void StandardScaler(double **X, int n, int p) {

  double sum[p], mean[p], var[p], std[p];

  for (int i=0; i<p; i++) {
    sum[i] = 0;
    for (int j=0; j<n; j++) {
      sum[i] += X[j][i];
    }
    mean[i] = sum[i] / n;

    var[i] = 0;
    for (int j=0; j<n; j++) {
      var[i] += (X[j][i] - mean[i]) * (X[j][i] - mean[i]);
    }
    var[i] = var[i] / n;
    std[i] = sqrt(var[i]);

    for (int j=0; j<n; j++) {
      X[j][i] = (X[j][i] - mean[i]) / std[i];
    }
  }
}

// -------------------------------------------
// ベクトル変数メモリ割り当て
// -------------------------------------------
double* gen_vector(int p) {
    double *vec;

    vec =  (double*)malloc(p * sizeof(double));
    for (int i=0; i<p; i++) {
      vec[i] = 0;    // initialize 0
    }

    return vec;
}

// -------------------------------------------
// 行列(n:p)変数メモリ割り当て
// -------------------------------------------
double** gen_matrix(int n, int p) {
    double **mat;

    mat = (double**)malloc(n * sizeof(double*));
    for(int i=0; i<n; i++){
      mat[i] = (double*)malloc(p * sizeof(double));
      for (int j=0; j<p; j++) {
        mat[i][j] = 0;    // initialize 0
      }
    }

    return mat;
}

// -------------------------------------------
// Standard output vector for debug
// -------------------------------------------
void print_vector(int a, double *dat) {

    for(int i=0; i<a; i++){
        printf("%f  ", dat[i]);
    }
    printf("\n");
}

// -------------------------------------------
// Standard output matrix for debug
// -------------------------------------------
void print_matrix(int a, int b, double **dat) {

    for(int i=0; i<a; i++){
      for(int j=0; j<b; j++){
        printf("%f  ", dat[i][j]);
      }
      printf("\n");
    }
}
