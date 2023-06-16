#!/bin/bash

gcc codes/double_thread.c -o execs/double_thread.o -pthread
echo "" > results/resultado_double_thread.txt

for i in 1 2 3 4 5; do
  ./execs/double_thread.o $i 0
done

sync; sync; sync;

for i in 1 2 3 4 5; do
  taskset -c 0,1 ./execs/double_thread.o $i 1
done