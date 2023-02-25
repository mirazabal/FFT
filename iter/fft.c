#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "fft.h"

// Knuth algorithm to reverse bits. 
// From Hackster Delight pag. 133
static
uint32_t rev(uint32_t x)
{
  x = (x << 15 | x >> 17 ); // rotate left 15
  uint32_t t = (x ^ (x >> 10)) & 0x003F801F;
  x = (t | (t << 10)) ^ x ;

  t = (x ^ (x >> 4)) & 0x0E038421;
  x = (t | (t << 4)) ^ x ;

  t = (x ^ (x >> 2)) & 0x22488842;
  x = (t | (t << 2)) ^ x ;

  return x;
}

static
void bit_rev(size_t len, float complex const in[len], float complex out[len] )
{
  assert(len < (1UL << 32));

  int const ctz = __builtin_ctz(len);

  for(uint32_t i = 0; i < len; ++i){
    uint32_t tmp = rev(i);
    tmp = tmp >> (32- ctz );
    out[tmp] = in[i];
  }

}

void fft(size_t len, float complex arr[len], float complex out[len])
{
  assert(__builtin_popcount(len) == 1 && "Need exact powers of 2");
  assert(len < (1UL << 32) && "No more than 2^32 supported" );
   
  bit_rev(len, arr, out);
 
  const uint32_t lg_n = __builtin_ctz(len);
  
  for(int s = 1; s <= lg_n ; ++s){
    const uint32_t m = 1 << s;
    const float complex w_m = cexp( 2*M_PI*I/m);
    
    for(int k = 0; k < len; k += m){
      float complex w = 1;
    
      for(int j = 0; j < m/2; j++){
        const float complex t = w*out[k + j + m/2];
        const float complex u = out[k + j]; 

        out[k + j] = u + t; 
        out[k + j + m/2] = u - t; 
        w = w*w_m;
      } 
    }
  }
}

void ifft(size_t len, float complex in[len], float complex out[len])
{
  assert(0 != 0 && "Not implemented");
}

