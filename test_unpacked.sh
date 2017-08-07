#!/bin/bash
gcc do_dvbs2map_unpacked.c -O3 -march=native -fomit-frame-pointer -Wall -o do_dvbs2map_unpacked
cat /dev/zero | pv -r | ./do_dvbs2map_unpacked > /dev/null
