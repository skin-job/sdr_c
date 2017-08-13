/**
	MIT License

	Copyright (c) 2017 Skin-Job (https://github.com/skin-job)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
**/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>


#define BUFFSIZE 1024 

int main(int argc, char* argv[])
{
	unsigned int   mu, mask, nshifts, i, j, nbytes;
	double complex *const_ptr=NULL; 	

	double complex   QPSK_CONST_MAP[] = 
		{(+1+I)/sqrt(2), (+1-I)/sqrt(2), (-1+I)/sqrt(2), (-1-I)/sqrt(2)};

	double complex   PSK8_CONST_MAP[] = 
		{cexp(I*M_PI_4), cexp(I*0.00)   , -cexp(I*0.00),   -cexp(I*M_PI_4),
		 cexp(I*M_PI_2), cexp(-I*M_PI_4), -cexp(-I*M_PI_4),-cexp(I*M_PI_2)};
	
	double R1 = 1.0;
	double R2 = 2.5;	
	double complex APSK16_CONST_MAP[] = 
		{R2*cexp(I*M_PI_4  ), R2*cexp(-I*M_PI_4  ), -R2*cexp(-I*M_PI_4  ), -R2*cexp(I*M_PI_4  ),
		 R2*cexp(I*M_PI_4/3), R2*cexp(-I*M_PI_4/3), -R2*cexp(-I*M_PI_4/3), -R2*cexp(I*M_PI_4/3),
                 R2*cexp(I*M_PI_2/3), R2*cexp(-I*M_PI_2/3), -R2*cexp(-I*M_PI_2/3), -R2*cexp(I*M_PI_2/3),
                 R1*cexp(I*M_PI_4  ), R1*cexp(-I*M_PI_4  ), -R1*cexp(-I*M_PI_4  ), -R1*cexp(I*M_PI_4  )};

	mu      = 2;
	const_ptr = QPSK_CONST_MAP;	
	mask    = (1 << mu)-1;
	nshifts = 8/mu;
	
	unsigned char  ibuf[BUFFSIZE];
        double complex obuf[BUFFSIZE*nshifts];	
	
	while(1){
		nbytes=read(STDIN_FILENO, ibuf, BUFFSIZE);
		for (i=0;i<nbytes;i++){
			for (j=0;j<nshifts;j++){
				obuf[i*nshifts+j] = const_ptr[(ibuf[i]&mask)];		
				ibuf[i]   = (ibuf[i] >> mu);
			} 
		}
		nbytes=write(STDOUT_FILENO,(unsigned char *) obuf, sizeof(double complex)*nbytes*nshifts);
	}	
	return 0;
}
