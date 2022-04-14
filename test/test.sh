#!/bin/zsh

make clean
make
time ./a.out $1
time tar caf __test_out.tar.xz __test_in.txt
ls -alF
