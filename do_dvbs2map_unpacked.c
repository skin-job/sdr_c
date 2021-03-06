#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>


#define BUFFSIZE 1024 

int main(int argc, char* argv[])
{
	unsigned int   mu, mask, i,  nbytes;
	double complex *const_ptr=NULL; 
        double complex qpsk_const_map[] = {(+1+I)/sqrt(2), (+1-I)/sqrt(2), (-1+I)/sqrt(2), (-1-I)/sqrt(2)};
		
	mu      = 2;
	const_ptr = qpsk_const_map;	
	mask    = (1 << mu)-1;

	
	unsigned char  ibuf[BUFFSIZE];
        double complex obuf[BUFFSIZE];	
	
	while(1){
		nbytes=read(STDIN_FILENO, ibuf, BUFFSIZE);
		for (i=0;i<nbytes;i++){
			obuf[i] = const_ptr[(ibuf[i]&mask)];		 
		}
		write(STDOUT_FILENO,(unsigned char *) obuf, sizeof(double complex)*nbytes);
	}	
	return 0;
}
