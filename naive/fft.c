#include "fft.h"

#include <assert.h>
#include <math.h>

void fft(size_t len, float complex arr[len], float complex out[len])
{
  // Fourier naive algorithm 
	// https://en.wikipedia.org/wiki/DFT
  // Eq. 1 
  
	for (size_t k = 0; k < len; ++k) {
    out[k] = 0; 
		for (size_t n = 0; n < len; ++n) {
      out[k] += arr[n] * cexp((-1.0)* I * 2 * M_PI * k * n / len  );
		}
	}
}

void ifft(size_t len, float complex in[len], float complex out[len])
{
  // Fourier naive algorithm 
	// https://en.wikipedia.org/wiki/DFT
  // Eq. 3 

  for(size_t n = 0; n < len; ++n){
    for(size_t k = 0; k < len; ++k){
      out[n] += in[k]*cexp(I*2*M_PI*k*n/len); 
    }
    out[n] /= len;
  }
}
