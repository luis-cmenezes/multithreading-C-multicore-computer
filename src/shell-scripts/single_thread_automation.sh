#!/bin/bash

gcc codes/single_thread.c -o execs/single_thread.o

for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15; do
  ./execs/single_thread.o $i
done