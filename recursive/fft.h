#ifndef ITERATIVE_FFT_MIR_H
#define ITERATIVE_FFT_MIR_H 

#include <stdlib.h>
#include <complex.h>

#define Re(x)   (_Generic((x), \
    complex float       : ((float *)       &(x)), \
    complex double      : ((double *)      &(x)), \
    complex long double : ((long double *) &(x)))[0])

#define Im(x)   (_Generic((x), \
    complex float       : ((float *)       &(x)), \
    complex double      : ((double *)      &(x)), \
    complex long double : ((long double *) &(x)))[1])

void fft(size_t len, float complex in[len], float complex out[len]);

void ifft(size_t len, float complex in[len], float complex out[len]);

#endif

