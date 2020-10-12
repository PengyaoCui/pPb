#!/bin/bash
#

hadd AnalysisOutputs_Loop1ndRD.root AnalysisOutputs_Loop1ndRD_*.root
hadd AnalysisOutputs_FitInvMrd.root AnalysisOutputs_FitInvMrd_*.root
hadd AnalysisOutputs_Loop2ndRD.root AnalysisOutputs_Loop2ndRD_*.root
hadd AnalysisOutputs_FitCbinRD.root AnalysisOutputs_FitCbinRD_*.root
hadd AnalysisOutputs_LoopJetRD.root AnalysisOutputs_LoopJetRD_*.root
hadd AnalysisOutputs_FitCbinJE.root AnalysisOutputs_FitCbinJE_*.root

#
exit 0

