#!/bin/bash

gcc codes/single_thread.c -o execs/single_thread.o
echo "" > results/resultado_single_thread.txt

for i in 1 2 3 4 5; do
  ./execs/single_thread.o $i 0
done

sync; sync; sync;

for i in 1 2 3 4 5; do
  taskset -c 0 ./execs/single_thread.o $i 1
done