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
	double complex qpsk_const_map[] = {1+I, 1-I, -1+I, -1-I};
		
	mu      = 2;
	const_ptr = qpsk_const_map;	
	mask    = (1 << mu)-1;
	nshifts = 8/mu;
	
	unsigned char  ibuf[BUFFSIZE];
        double complex obuf[BUFFSIZE*nshifts];	
	
	while(1){
		nbytes=read(STDIN_FILENO, ibuf, BUFFSIZE);
		for (i=0;i<nbytes;i++){
			for (j=0;j<nshifts;j++){
				obuf[i*nshifts+j] = const_ptr[(ibuf[i]&mask)];		
		//		putchar(ibuf[i]&mask);
				ibuf[i]   = (ibuf[i] >> mu);
			} 
		}
		write(STDOUT_FILENO,(unsigned char *) obuf, sizeof(double complex)*nbytes*nshifts);
	}	
	return 0;
}
