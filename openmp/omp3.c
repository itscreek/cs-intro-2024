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

  int chunk_size = 1000;
  #pragma omp parallel
  {
    long long local_min = min;
    long long local_min_idx = min_idx;
    #pragma omp for private(j) schedule(dynamic, chunk_size)
    for(i = L; i <= R; i++){
      t = i;
      for(j = 2; j*j <= i; j++){
        if(i%j == 0){
          t = j;
          break;
        }
      }
    
      if (local_min > t){
        local_min = t;
        local_min_idx = i;
      }
    }

    #pragma omp critical
    {
      if (local_min < min){
        min = local_min;
        min_idx = local_min_idx;
      }
    }
  }

  t2 = omp_get_wtime();

  printf("minimum value %lld\n", min);
  printf("index %lld\n", min_idx);
  printf("time %f\n", t2-t1);
  
  return 0;
}
