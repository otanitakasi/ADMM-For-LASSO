#include <stdio.h>

#define   LAMBDA  1     // Hyper parameter λ
#define   RHO     1     // Hyper parameter ρ
#define   ITER    1000  // Iteraton count

void StandardScaler(double **X, int n, int p);      // 学習データの標準化
double*  gen_vector(int p);                         // ベクトル変数用メモリ確保
double** gen_matrix(int n, int p);                  // 行列変数用メモリ確保

void admmForLasso(double lambda, double rho, int iter, int p, int n, double **X, double *y);

int main() {

    double lambda = LAMBDA ;              // Hyperparamter λ
    double rho = RHO;                     // Hyperparamter ρ
    int iter = ITER;                      // Iteraton count
    int p = 13;                           // Number of parameters
    int n = 506;                          // Number of samples
    char filename[] = "./boston.txt";     // Filename of training data

    FILE * fp = NULL;
    double **X;                           // Explanatory matrix data
    double  *y;                           // Response vector data

    // Initializing(allocate memory)
    X = gen_matrix(n, p);
    y = gen_vector(n);

    //	Reading training data from file
	  fp = fopen(filename, "r");
    for(int i=0; i<n; i++){
      for(int j=0; j<p; j++){
        fscanf(fp, "%lf", &(X[i][j]));
      }
        fscanf(fp, "%lf", &(y[i]));
    }

    // Standardizing leaning data
    StandardScaler(X, n, p);

    // ADMM for lass
    admmForLasso(lambda, rho, iter, p, n, X, y);
}
