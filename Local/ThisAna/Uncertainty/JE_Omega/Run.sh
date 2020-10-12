#!/bin/bash


cd /afs/cern.ch/work/p/pcui/private/pPb/Local/Uncertainty/JE/UE/OC08/ 
root -l -b -q runLocalStrangeJets.C
cd /afs/cern.ch/work/p/pcui/private/pPb/Local/Uncertainty/JE/UE/OC06/ 
root -l -b -q runLocalStrangeJets.C
cd /afs/cern.ch/work/p/pcui/private/pPb/Local/Uncertainty/JE/JetPt/Loose/ 
root -l -b -q runLocalStrangeJets.C
cd /afs/cern.ch/work/p/pcui/private/pPb/Local/Uncertainty/JE/JetPt/Tight/ 
root -l -b -q runLocalStrangeJets.C
