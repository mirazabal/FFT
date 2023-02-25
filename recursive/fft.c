#include "fft.h"

#include <assert.h>
#include <math.h>

typedef struct{
  size_t len;
  complex float* buf;
} array_t;

static
array_t alloc_array(size_t len)
{
  array_t dst = {.len = len}; 

  dst.buf = calloc(len, sizeof(complex float) );
  assert(dst.buf != NULL && "Memory exhausted");

  return dst;
}

static
void free_array(array_t src)
{
  free(src.buf);
}


static
array_t get_even(array_t a)
{
  array_t dst = alloc_array(a.len/2);

  for(size_t i = 0; i < dst.len; ++i)
    dst.buf[i] = a.buf[i*2];

  return dst;
}

static
array_t get_odd(array_t a)
{
  array_t dst = alloc_array(a.len/2);

  for(size_t i = 0; i < dst.len; ++i)
    dst.buf[i] = a.buf[i*2 + 1];

  return dst;
}




static
array_t recursive_fft(array_t a)
{
  size_t n = a.len;
  if(n == 1)
    return a;

  complex float w_n = cexp(2*M_PI*I / n);
  complex float w = 1;

  array_t a0 = get_even(a);
  array_t a1 = get_odd(a);
  array_t y0 = recursive_fft(a0);
  array_t y1 = recursive_fft(a1);

  array_t y = alloc_array(n);
  for(size_t k = 0; k < n/2; ++k){
    y.buf[k] = y0.buf[k] + w*y1.buf[k];
    y.buf[k+n/2] = y0.buf[k] - w*y1.buf[k];  
    w = w*w_n;
  }

  free_array(a0);
  free_array(a1);
  

  // Avoid double free
  if(a0.len > 1){
    free_array(y0);
    free_array(y1);
  }

  return y;
}


void fft(size_t len, float complex in[len], float complex out[len])
{
  assert(__builtin_popcount(len) == 1 && "Need exact powers of 2");
  assert(len < (1UL << 32) && "No more than 2^32 supported" );

  array_t in_arr = alloc_array(len);

  for(size_t i = 0; i < len; ++i){
    in_arr.buf[i]= in[i];
  }

  array_t out_arr = recursive_fft(in_arr);

  for(size_t i = 0; i < len; ++i){
    out[i] = out_arr.buf[i];
  }

  free_array(in_arr);
  free_array(out_arr);

}

void ifft(size_t len, float complex in[len], float complex out[len])
{
  assert(0 != 0 && "Not implemented");
}


