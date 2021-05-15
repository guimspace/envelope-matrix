#!/bin/bash

octave-cli sampler.m

echo "$(tail -n +6 A.mat)" > A.mat
echo "$(tail -n +6 b.mat)" > b.mat
echo "$(tail -n +6 x.mat)" > x.mat

sed -i "s/^ //g" A.mat b.mat x.mat

make
time ./envelope A.mat b.mat
