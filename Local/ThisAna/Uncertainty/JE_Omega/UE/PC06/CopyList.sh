#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_1040"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_4090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Kshort_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_1040"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_4090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_1040"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_4090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_1040"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_4090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Xi_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_0100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_010"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_1040"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_4090"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AnalysisOutputs_LoopJetRD_back.root"','"listLoopJetRD_Omega_Default_JC_40100"' \


do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
