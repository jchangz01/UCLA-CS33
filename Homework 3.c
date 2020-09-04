/* Determine how the throughput and latency limits of your machine limit
the minimum CPE you can achieve for prefix-sum operation 

Typically a modern processor possesses multiple functional units meaning 
we are able to hide latency by exploiting parallelism. To specify, we can 
perform more operations in a single iteration loop to increase throughput (max rate
at which functional units can produce results) and execute multiple instructions 
simultaneously. However, because registers and functional units are finite, 
it means we are only able to perform effective loop unrolling to a certain factor
which ultimately limits the minimum CPE we can achieve.
In this problem, pipelining is tricky because the function psum uses the values
of the sums of the previous index. To work around this, I declared variables to
store values from array 'a' to minimize the times we have to access memory. These 
assignments are independent of each other so the processor can compute these in
any order. Finally, we add up these values and assign them to their corresponding 
elements in the array. Because, we have stored the array values in variables, we do not
have to access memory thus reducing latency. Furthermore, all these operations are independent
of each other which means we can exploit ILP and increase the overall speed.
*/
    
void psum1b(float a[], float p[], double n)
{
  long i;
  float val1, val2, val3, val4, val5, val6;
  float val, last_val;
  last_val = p[0] = a[0];T

  /* Loop unrolling by factor of k = 6 */
  for (i = 1; i < n; i+=6) {
    val1 = last_val + a[i];
    val2 = a[i+1];
    val3 = a[i+2];
    val4 = a[i+3];
    val5 = a[i+4];
    val6 = a[i+5];

    p[i] = val1;
    p[i+1] = val1 + val2;
    p[i+2] = (val1 + val2) + val3;
    p[i+3] = (val1 + val2 + val3) + val4;
    p[i+4] = (val1 + val2 + val3 + val4) + val5;
    p[i+5] = (val1 + val2 + val3 + val4 + val5) + val6;
   
    last_val = val1 + val2 + val3 + val4 + val5 + val6;
  }

  /* For even n, finish remaining element (clean-up)*/
  for ( ; i < n; i++) {
    val = last_val + a[i];
    p[i] = val;
    last_val = val;
  }
}

int main ()
{
  float array1 [9] = { 1, 2, 3, 4, 7, 8, 9, 10, 1 };
  float array2 [9] = { 5, 6, 7, 8, 9, 10, 11, 12, 1 };
  float array3 [9];
  psum1b(array2, array1, 9);

  int i = 0;
  for (i = 0; i < 9; i++) {
    printf ("%f \n", array1[i]);
  }
  return 1;
}
