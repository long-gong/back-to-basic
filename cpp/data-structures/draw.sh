#!/usr/bin/env bash

set -e 

for f in $(ls ./build | grep .dot) 
do
    fwo="${f%%.*}"
    dot ./build/$f -Tpng -o ./images/${fwo}.png
done