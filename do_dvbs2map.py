#!/usr/bin/python3.5 -u
import sys
import struct

BUFFSIZE = 16
#QPSK
mu = 2
const  = [(1.0+1j), (1.0-1j), (-1.0+1j), (-1.0-1j)] 
mask   = (2**mu)-1
nshift = int(8/mu)

while True: 
	data_bytes = sys.stdin.buffer.read(BUFFSIZE)
	for r in data_bytes:
		for i in range(nshift):
			m = (r & mask)
			s = struct.pack('dd',const[m] .real, const[m].imag)
			r = (r >> mu)
			sys.stdout.buffer.write(s)
		
