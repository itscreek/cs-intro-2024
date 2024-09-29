#include<stdio.h>
#include<omp.h>

#define L 1000LL
#define R 20000000LL

int main(){
  long long i, j, t;
  long long min, min_idx;
  double t1, t2;

  t1 = omp_get_wtime();

  min = 97;
  min_idx = 0;

  for(i = L; i <= R; i++){
    t = i;
    for(j = 2; j*j <= i; j++){
      if(i%j == 0){
        t = j;
        break;
      }
    }
    
    if (min > t){
      min = t;
      min_idx = i;
    }
  }

  t2 = omp_get_wtime();

  printf("minimum value %lld\n", min);
  printf("index %lld\n", min_idx);
  printf("time %f\n", t2-t1);
  
  return 0;
}
