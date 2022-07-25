#!/bin/bash
./generator --$1 > $1$2.txt
ARG=$(./lem-in < $1$2.txt)
echo $ARG > output_$1$2.txt
cat output_$1$2.txt