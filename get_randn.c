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

	This program generates approximately gaussian distributed random numbers by
	adding up twelve uniform distributed ramdom numbers in the range (-1,1). The
	generated random samples have unitary variance and zero mean.

**/



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <complex.h>

#define BUFFSIZE  256*2  // input buffer size  (double) 
#define N_UNIFORM 12     // Number of uniform random distributed numbers to sum up

int main(int argc, char *argv[]){

	int  nbytes, ndoubles;
	unsigned int  i,j,k;
	double normfactor = (1.0/pow(2,64)); 

	long int ibuf[BUFFSIZE*N_UNIFORM];
	double   obuf[BUFFSIZE];
	double   normrnd;


	//TODO: Not complete, have to test number of nbytes read;
	while(1){
		nbytes=read(STDIN_FILENO, (unsigned char *)ibuf, BUFFSIZE*N_UNIFORM*sizeof(double));
		if (nbytes>0){
			nbytes  = (nbytes-nbytes%(2*N_UNIFORM*sizeof(double)));
			ndoubles= (nbytes/sizeof(double));
			k=0;
			for (i=0;i<ndoubles;i+=N_UNIFORM){
				normrnd = 0.0;
				for (j=0;j<N_UNIFORM;j++){
					normrnd += (double)(ibuf[i+j]);
				}	
				obuf[k]=(1.0*normrnd*normfactor);
				k++;
			}
                        nbytes=write(STDOUT_FILENO, (unsigned char *)obuf, nbytes/N_UNIFORM);

		}
	}
}
