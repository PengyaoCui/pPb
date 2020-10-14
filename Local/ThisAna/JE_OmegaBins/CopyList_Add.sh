#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Results.root"','"./back/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./back/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./back/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"./back/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./back/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./back/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"./back/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./back/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./back/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"./back/AnalysisOutputs_Results.root"','"listResults_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./back/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./back/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./back/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_OC_40100"' \
                                     
do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
