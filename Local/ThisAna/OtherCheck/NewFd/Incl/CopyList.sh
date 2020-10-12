#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_0100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_010"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_1040"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_4090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Kshort_Default_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_0100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_010"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_1040"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_4090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Lambda_Default_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_0100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_1040"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_4090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_0100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_010"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_1040"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_4090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Xi_Default_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_0100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_010"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_1040"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_4090"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_Omega_Default_40100"' \
#'"./AnalysisOutputs_Loop1ndRD.root"','"./AnalysisOutputs_Loop1ndRD_back.root"','"listLoop1ndRD_AntiLa_Default_010"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
