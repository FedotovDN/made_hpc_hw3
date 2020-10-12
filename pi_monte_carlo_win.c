#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
 
int main() 
{
  int n1 = 100000000, n2 = 0;
  int i;
  float a, b, m;
  float pi;
  double start, end;
  int my_thread_id;
  unsigned int seed;

  start = omp_get_wtime();
  omp_set_num_threads(12);
#pragma omp parallel for private(i, seed, my_thread_id, a, b, m) shared(n1) reduction(+:n2)
  for (i = 1; i <= n1; i++) {
      my_thread_id = omp_get_thread_num();
      unsigned int seed = (unsigned) 123456789 * my_thread_id + i;
      a = (float)rand() / RAND_MAX;
      b = (float)rand() / RAND_MAX;
      m = a*a + b*b;
      //printf ("%f %f %f %d %d \n", a, b, m, n2, my_thread_id);
      if (m <= 1) {
      	n2++;
      }
  }
 
  pi = (float)4 * n2 / n1;
  end = omp_get_wtime();
  printf("Time elapsed - %f\n", (end - start));
  printf("Pi = %f\n", pi);
  printf("Points = %d\n", n1);
  printf("Hits = %d\n", n2);
  
  return 0;
}
