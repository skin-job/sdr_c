#!/usr/bin/python3.5 -u
import sys
import struct

BUFFSIZE = 16
#QPSK
mu = 2
const  = [(1.0+1j), (1.0-1j), (-1.0+1j), (-1.0-1j)] 
mask   = (2**mu)-1

while True: 
	data_bytes = sys.stdin.buffer.read(BUFFSIZE)
	for r in data_bytes:
		m = (r & mask)
		s = struct.pack('dd',const[m] .real, const[m].imag)
		sys.stdout.buffer.write(s)
		
