#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

#define N 2048
#define ZERO (double)(0.0)
#define THREE (double)(3.0)

double getrusage_sec(){

  struct rusage t;
  struct timeval tv;
  getrusage(RUSAGE_SELF, &t);
  tv = t.ru_utime;
  return tv.tv_sec + (double)tv.tv_usec * 1e-6;

}

int main(){

  static int i, j, k;
  static double a[N][N], b[N][N], c[N][N], s;
  static double t1, t2;

  srand(1);

  for (i = 0; i < N; i++){
    for (j = 0; j < N; j++){
      a[i][j] = rand() / (double)RAND_MAX;
      b[i][j] = rand() / (double)RAND_MAX;
    }
  }

  t1 = getrusage_sec();

  // double ONE_THIRD = 1.0 / THREE;
  // for (i = 0; i < N; i++){
  //   for (k=0; k < N; k++) {
  //     for (j=0; j < N; j++) {
  //       if (i == 0) {
  //         b[k][j] *= ONE_THIRD;
  //       }
  //       if (k == 0) {
  //         c[i][j] = ZERO;
  //       }
  //       c[i][j] = c[i][j] + a[i][k] * b[k][j];
  //     }
  //   }
  // } 

  int n = N;
  double alpha = 1.0 / THREE;
  double beta = 0;
  dgemm_("N", "N", &n, &n, &n, &alpha, b, &n, a, &n, &beta, c, &n);

  t2 = getrusage_sec();

  printf("time = %10.5f\n", t2 - t1);

  s = ZERO;

  for (i = 0; i < N; i+=10){
    for (j = 0; j < N; j+=10){
      if (a[i][j] > s){
          s = a[i][j];
      }
      if (b[i][j] > s){
          s = b[i][j];
      }
      if (c[i][j] > s){
          s = c[i][j];
      }
    }
  }

  printf("%f\n", s);

  return 0;
}
