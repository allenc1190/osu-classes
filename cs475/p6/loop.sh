#!/bin/bash
for t in 1024 4096 16384 65536 262144 1048576 2097152 4194304 8388608
do
        for b in 8 16 32 128 256 512
        do
                g++ /usr/local/apps/cuda/10.1/lib64/libOpenCL.so.1.1 -DNUM_ELEMENTS=$t -DLOCAL_SIZE=$b -o first  first.cpp -lm -fopenmp
                ./first
        done
done