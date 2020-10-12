#!/bin/bash
#
for i in \
0,5 5,10 10,20 20,40 40,60 60,80 80,100 0,100 
do
root -l -b -q runLocalStrangeJets.C\(${i}\)
done
#
exit 0
