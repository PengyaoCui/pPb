#!/bin/bash
#
for kCje in 0 2
do
#
  for kAct in 0 1 2 3 4 5
  do
#
    for kPtj in 0 1
    do
      root -b -q -l PlotL2K_Pt_Comp.C\(${kCje},${kAct},${kPtj},1\)
    done
#
  done
#
done
#
exit 0
