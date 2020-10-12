#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Kshort_Default_2040"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Kshort_Default_4060"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Kshort_Default_6080"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AnalysisOutputs_Loop2ndRD_back.root"','"listLoop2ndRD_Kshort_Default_80100"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0



