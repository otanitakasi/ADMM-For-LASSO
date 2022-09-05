#include <stdio.h>
#include <stdlib.h>

int matInv(double **X, double **Y, int p);          // 逆行列を計算
double*  gen_vector(int p);                         // ベクトル変数用メモリ確保
double** gen_matrix(int n, int p);                  // 行列変数用メモリ確保
void print_vector(int a, double *dat);
void print_matrix(int a, int b, double **dat);

//----------------------------------------------------------
// ADMM for LASSO
//----------------------------------------------------------
// argument
//    lambda  : Hyper parameter  λ
//    rho     : Hyper parameter  ρ
//    iter    : Iteration count
//    p       ; Parameter number of training data
//    n       ; Sample numbe of training data
//    X       : Explanatory data
//    y       : Response data
//
void admmForLasso(double lambda, double rho, int iter, int p, int n, double **X, double *y) {

    // Updated variable
    double  *beta;      // β
    double  *th;        // θ
    double  *mu;        // μ

    // Intemediate variable
    double **XtX;
    double **XtX_add_rho;
    double **XtX_add_rho_inv;
    double  *Xty;
    double  *Xty_add_th_and_mu;

    // ------------------------------------
    // Initializing(allocate memory)
    // ------------------------------------
    XtX = gen_matrix(p, p);
    XtX_add_rho = gen_matrix(p, p);
    XtX_add_rho_inv = gen_matrix(p, p);
    Xty = gen_vector(p);
    Xty_add_th_and_mu = gen_vector(p);
    beta = gen_vector(p);
    th = gen_vector(p);
    mu = gen_vector(p);

    // ------------------------------------
    // Calculating Constant term
    // ------------------------------------
    // (X^t * X + ρI)
    for(int i=0; i<p; i++){
      for(int j=0; j<p; j++){
        for(int k=0; k<n; k++){
          XtX[i][j] += X[k][i] * X[k][j] ;
        }
        XtX_add_rho[i][j] = (i==j) ? (XtX[i][j] / n + rho) : XtX[i][j] / n ;
      }
    }

    // (X^t * X + ρI)^-1
    matInv(XtX_add_rho, XtX_add_rho_inv, p);

    // (X^t * y)
    for(int i=0; i<p; i++){
      for(int k=0; k<n; k++){
        Xty[i] += X[k][i] * y[k];
      }
    }

    // ------------------------------------
    //   Updating paramter
    // ------------------------------------
    double  S_input;
    double  threshold = lambda / rho;

    // Initializing updated paramter
    for(int i=0; i<p; i++){
      beta[i] = Xty[i] / n;
      th[i] = beta[i] ;
      mu[i] = 0 ;
    }

    for (int t=0; t<iter; t++) {
      for(int i=0; i<p; i++){
        // Updating beta
        double tmp = 0;
        for(int j=0; j<p; j++){
          Xty_add_th_and_mu[j] = Xty[j] / n + rho*th[j] - mu[j] ;
          tmp += XtX_add_rho_inv[i][j] * Xty_add_th_and_mu[j] ;
        }
        beta[i] = tmp;

        // Updating theta
        S_input = beta[i] + (mu[i]/rho) ;
        if (S_input > threshold) {
          th[i] = S_input - threshold;
        } else if (S_input < -1*threshold) {
          th[i] = S_input + threshold;
        } else {
          th[i] = 0;
        }

        // Updating mu
        mu[i] += rho*(beta[i] - th[i]);
      }
    }

    printf("***************************\n");
    printf("*          Result         *\n");
    printf("***************************\n");
    printf("β = ");
    print_vector(p, beta);
    printf("\n");

    //
    //  Finalize(release memory)
    //
    for(int i=0; i<p; i++){
      free(X[i]);
      free(XtX[i]);
      free(XtX_add_rho[i]);
      free(XtX_add_rho_inv[i]);
    }
    free(X);
    free(XtX);
    free(XtX_add_rho);
    free(XtX_add_rho_inv);
    free(y);
    free(beta);
    free(th);
    free(mu);
    free(Xty);
    free(Xty_add_th_and_mu);
}


// =====================================================
// 掃き出し法により、逆行列を計算
// X：Input data
// Y :Output data
// =====================================================
int matInv(double **X, double **Y, int p) {

  double buf;

  //単位行列を作る
  for(int i=0; i<p; i++){
    for(int j=0; j<p; j++){
      Y[i][j] = (i==j) ? 1 : 0;
    }
  }
  //掃き出し法
  for(int i=0; i<p; i++){
    buf = 1 / X[i][i];
    for(int j=0; j<p; j++){
      X[i][j] *= buf;
      Y[i][j] *= buf;
    }
    for(int j=0; j<p; j++){
      if(i!=j){
        buf = X[j][i];
        for(int k=0; k<p; k++){
          X[j][k] -= X[i][k] * buf;
          Y[j][k] -= Y[i][k] * buf;
        }
      }
    }
  }

  return(0);
}
