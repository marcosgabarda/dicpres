#!/bin/bash

for file in $(ls *.txt *.jpg *.pdf *.bmp); do
    ./test_lzw $file
    ./test_lz78 $file
done;