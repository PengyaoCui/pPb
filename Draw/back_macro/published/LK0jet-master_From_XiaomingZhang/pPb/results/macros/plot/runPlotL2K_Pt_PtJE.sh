#!/bin/bash
#
#
for kCje in 0 2
do
#
  for kAct in 0 1 2 3 4 5
  do
    root -b -q -l PlotL2K_Pt_PtJE.C\(${kCje},${kAct},1\)
  done
#
done
#
exit 0
