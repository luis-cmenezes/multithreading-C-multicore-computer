#!/bin/bash

gcc codes/quad_thread.c -o execs/quad_thread.o -pthread
echo "" > results/resultado_quad_thread.txt

for i in 1 2 3 4 5; do
  ./execs/quad_thread.o $i 0
done

sync; sync; sync;

for i in 1 2 3 4 5; do
  taskset -c 0,1,2,3 ./execs/quad_thread.o $i 1
done