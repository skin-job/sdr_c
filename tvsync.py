#!/usr/bin/python3.5

import sys, matplotlib
matplotlib.use('Qt5Agg')
import matplotlib.pyplot as plt
import numpy as np
from optparse  import OptionParser
from fractions import Fraction

# Parsing input options
parser = OptionParser()
parser.add_option( # NFFT
	"-f", "--fft-size",
	type="int", dest="nfft",
	default=8192,
	help="OFDM FFT size")
parser.add_option( # CP Size
	"-r", "--cp-ratio",
	type="string", dest="cpratio",
	default="1/8",
	help="Cyclic-Prefix ratio to FFT Size eg. 1/4, 1/8 ...")
parser.add_option( # Buffer Size
	"-l", "--correlation-length",
	type="int", dest="nsamples",
	default=16384,
	help="number od samples on the autocorrelation")
(options, args) = parser.parse_args()

# initializing  variables
nfft=options.nfft
cpratio=options.cpratio
ncp=int(np.ceil(float(Fraction(cpratio))*nfft))
NSAMPLES=options.nsamples

Baseband = np.zeros((NSAMPLES+nfft), dtype=complex)
xx       = np.zeros((NSAMPLES+ncp ), dtype=complex)
lastval=0;

# Plot initialization
fig, ax = plt.subplots()
lineRxx, = ax.plot(np.zeros(NSAMPLES))
ax.set_ylim([0,1e6])
ax.set_xlim([0, NSAMPLES])
plt.show(block=False)
plt.ylabel('Autocorrelation')
fig.canvas.draw()

n=0;
while True: # Worker
	# Reading data from stdin
	rawIQ = np.frombuffer(sys.stdin.buffer.read(2*NSAMPLES),dtype=np.uint8)
	Baseband[nfft:] = (rawIQ[0::2]-127.5) +1j*(rawIQ[1::2]-127.5)
	# Calculating correlation
	xx[ncp:] = Baseband[:-nfft] * np.conj(Baseband[nfft:])
	Rxx = np.cumsum(xx[ncp:]-xx[:-ncp])+lastval
	# Saving state for next batch
	Baseband[:nfft]=Baseband[-nfft:]
	xx[:ncp]=xx[-ncp:]
	lastval=Rxx[-1:]

	# generate plot every 64 batches
	if (n%64==0):
		lineRxx.set_ydata(np.absolute(Rxx))
		ax.draw_artist(ax.patch)
		ax.draw_artist(lineRxx)
		fig.canvas.update()
		fig.canvas.flush_events()
	n+=1
