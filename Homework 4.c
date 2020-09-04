/* Block size is unknown, we will assume B = 10*/

#include <stdlib.h>
#include <stdio.h>

const int B = 10; /*Block size = 10*/

void transpose (int *dst, int *src, int dim)
{
	int i, j, i1, j1, i1lim, j1lim, i1dim;
	for (i = 0; i < dim; i+=B) {
		//if else to check if block size is larger than dim
		if (i + B < dim)
			i1lim = i + B;
		else
			i1lim = dim;
		for (j = 0; j < dim; j+=B){
			//if else to check if block size is larger than dim
			if (j + B < dim)
				j1lim = j + B;
			else
				j1lim = dim;
			/* B x B mini matrix copy */
			for (i1 = i; i1 < i1lim; i1++)
			{
				i1dim = i1 * dim; //notice i1 * dim is always the same in inner loop
				for (j1 = j; j1 < j1lim; j1++)
					dst[j1*dim+i1] = src[i1dim + j1];
			}
		}
	}
}

/*Test with dimensions 10000x10000*/
int main ()
{
	int i,j;
	int n = 10000; //10000x10000
	int *y = (int *) calloc(sizeof(int), n*n);
        int *x = (int *) calloc(sizeof(int), n*n);
        
	for (i = 0; i < 100000000; i++)
        {
        	x[i] = i;
		//printf ("%d\n", x[i]);
	}
	transpose (y, x, n);
	
	//print first 100 values of *y
	for (i = 100; i < 100; i++)
	{
		printf("%d ", y[i]);
	}
}
