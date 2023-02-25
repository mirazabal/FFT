#include <stdlib.h>
#include <stdio.h>

#include "fft.h"

#define LENGTH 8

int main()
{
  float complex in[LENGTH] = {0};
  for(int i = 0; i < LENGTH; ++i){
    in[i] = i;
  }

  float complex out[LENGTH] = {0};
  fft( LENGTH, in, out);

  for(int i = 0; i <  LENGTH; ++i){
      printf("i %d Re %lf Im %lf \n ",i,  Re(out[i]), Im(out[i]) );
  }

  return EXIT_SUCCESS;
}
