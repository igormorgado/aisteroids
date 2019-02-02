#!/bin/bash

rm -rf aisteroids phys.o gameobj.o control.o ship.o main.o
gcc -g -fms-extensions -O -c phys.c -lm
gcc -g -fms-extensions -O -c gameobj.c
gcc -g -fms-extensions -O -c control.c
gcc -g -fms-extensions -O -c ship.c 
gcc -g -fms-extensions -O -c main.c 

gcc -fms-extensions -o aisteroids phys.o gameobj.o control.o ship.o main.o -lm
