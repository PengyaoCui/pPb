#!/bin/bash
for i in MC Incl JC PC JE OC NJ
do 
root -l -b -q ratio.C\(\"${i}\"\)
done
