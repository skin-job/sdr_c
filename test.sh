#!/bin/bash
gcc do_dvbs2map.c -O3 -march=native -Wall -o do_dvbs2map
cat /dev/zero | pv -r | ./do_dvbs2map > /dev/null
