//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Justin Kyle Chang
 * UCLA ID : 205388820
 * Email : jchangz01@g.ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u; //, v, w;
  int ton = 0;
  long compute_it, moving_average;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;


  /*for(i=0; i<DIM-1;i++)
  {
    super[i] += simple[i];
  }*/

  //#pragma omp for nowait
  for(i=0; i<DIM-1;i++)
  {
    super[i] += simple[i];
    dot_product += super[i]*simple[i];
    
    /*moving_average = 0;
    for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
    {
      moving_average += simple[ton];
    }*/
  }
  
  moving_average = 0;

  fibonacci[0] = 1;
  fibonacci[1] = 1;
  for(i=2; i<DIM-1;i++)
  {
    fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
  }
  if (DIM > 4) 
  {
    printf("\n A secret is: %d", obfuscate_obfuscate_obfuscate(5));
  }

  step = 1.0 / NUM_STEPS;
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  } 

  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  int r2 = r * r;
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= r2) {
      nCirc++;
    }
  }  

  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 

  int DIMi, DIMj;
  long need = we_need_the_func();
  long gimmie = gimmie_the_func();
  #pragma omp parallel for private (compute_it, j, k, DIMi, DIMj) reduction (+:aggregate)
  for (i=1; i<DIM-1; i++) {
    DIMi = DIM * DIM * i;
    for (j=1; j<DIM-1; j++) {
      DIMj = DIM * j;
      for (k=1; k<DIM-1; k++) {
        compute_it = old[DIMi+DIMj+k] * need;
        aggregate+= compute_it / gimmie;
      }
    }
  }

  printf("AGGR:%ld\n",aggregate);

 
  #pragma omp parallel for private (j, k, DIMi, DIMj)
  for (i=1; i<DIM-1; i++) {
    DIMi = DIM * DIM * i;
    for (j=1; j<DIM-1; j++) {
      DIMj = DIM * j;
      for (k=1; k<DIM-1; k++) {
        new[DIMi+DIMj+k]=0;
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j-1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j-1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j-1)*DIM+(k+1)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(DIMj)+(k-1)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(DIMj)+(k)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(DIMj)+(k+1)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j+1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j+1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(i-1)*DIM*DIM+(j+1)*DIM+(k+1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j-1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j-1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j-1)*DIM+(k+1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(DIMj)+(k-1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(DIMj)+(k)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(DIMj)+(k+1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j+1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j+1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(DIMi)+(j+1)*DIM+(k+1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j-1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j-1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j-1)*DIM+(k+1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(DIMj)+(k-1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(DIMj)+(k)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(DIMj)+(k+1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j+1)*DIM+(k-1)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j+1)*DIM+(k)];
        new[DIMi+DIMj+k]+=old[(i+1)*DIM*DIM+(j+1)*DIM+(k+1)];
        new[DIMi+DIMj+k]/=27;
      }
    }
  }

  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
  }
  return (double) (dot_product+moving_average+pi+pi2);


}
