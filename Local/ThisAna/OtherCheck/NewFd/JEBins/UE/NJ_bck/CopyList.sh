#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_NJ_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_NJ_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_NJ_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_NJ_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_NJ_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_NJ_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_NJ_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_NJ_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_NJ_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_NJ_010"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
