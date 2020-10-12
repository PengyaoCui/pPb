#!/bin/bash
#
for i in \
'"./AnalysisOutputs_LoopIncMC.root"','"./Kshort/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/OtherCheck/NewFd/JEBins/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/OtherCheck/NewFd/JEBins/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Kshort/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Xi_Default_0100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Kshort/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Omega_Default_0100"' \

do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
