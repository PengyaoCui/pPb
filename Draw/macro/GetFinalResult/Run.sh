#!/bin/bash
#
sh runCentVal.sh
sh runStrangeRecUncer.sh
sh runInclUncer.sh
sh runJetPtUncer.sh
sh runUEUncer.sh
sh runTotUncer.sh
sh runFinalSpect.sh
sh runFinalRatio.sh
cp result/pPb.root /home/cuipengyao/study/pythia/NewModes/dPySjets_20200909_UpdateOmegabin/data/Data
cp result/pPb.root /home/cuipengyao/study/dPaperPlot/data 
