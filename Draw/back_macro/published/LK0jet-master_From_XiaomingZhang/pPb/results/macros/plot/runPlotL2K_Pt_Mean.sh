#!/bin/bash
#
for kAct in 0 1 2 3 4 5
do
#
  for kPtj in 0 1
  do
    root -b -q -l PlotL2K_Pt_Mean.C\(${kAct},${kPtj},1\)
  done
#
done
#
exit 0
