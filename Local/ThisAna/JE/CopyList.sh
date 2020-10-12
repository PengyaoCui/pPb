#!/bin/bash
#
for i in \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Kshort/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitInvMrd.root"','"./Kshort/AnalysisOutputs_FitInvMrd.root"','"listFitInvMrd_Kshort_Default_40100"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Kshort/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitCbinRD.root"','"./Kshort/AnalysisOutputs_FitCbinRD.root"','"listFitCbinRD_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Kshort/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Kshort/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Kshort/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Kshort_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Kshort/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Kshort_Default_40100"' \
'"./AnalysisOutputs_FitCbinMC.root"','"./Kshort/AnalysisOutputs_FitCbinMC.root"','"listFitCbinMC_Kshort_Default_40100"' \
'"./AnalysisOutputs_EffInclMC.root"','"./Kshort/AnalysisOutputs_EffInclMC.root"','"listEffInclMC_Kshort_Default_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Kshort/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Kshort/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCL_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Kshort/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Kshort/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Kshort/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Kshort/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_PCU_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Kshort/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Kshort/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Kshort/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_NJ_40100"' \
'"./AnalysisOutputs_Results.root"','"./Kshort/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_40100"' \
'"./AnalysisOutputs_Results.root"','"./Kshort/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_JC_40100"' \
'"./AnalysisOutputs_Results.root"','"./Kshort/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_PCL_40100"' \
'"./AnalysisOutputs_Results.root"','"./Kshort/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_PCU_40100"' \
'"./AnalysisOutputs_Results.root"','"./Kshort/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_NJ_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Xi/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Xi_Default_40100"' \
'"./AnalysisOutputs_FitInvMrd.root"','"./Xi/AnalysisOutputs_FitInvMrd.root"','"listFitInvMrd_Xi_Default_40100"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Xi/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Xi_Default_40100"' \
'"./AnalysisOutputs_FitCbinRD.root"','"./Xi/AnalysisOutputs_FitCbinRD.root"','"listFitCbinRD_Xi_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Xi/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Xi_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Xi/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Xi_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Xi/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Xi_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Xi/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Xi_Default_40100"' \
'"./AnalysisOutputs_FitCbinMC.root"','"./Xi/AnalysisOutputs_FitCbinMC.root"','"listFitCbinMC_Xi_Default_40100"' \
'"./AnalysisOutputs_EffInclMC.root"','"./Xi/AnalysisOutputs_EffInclMC.root"','"listEffInclMC_Xi_Default_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Xi/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Xi/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCL_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Xi/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Xi/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Xi/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Xi/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_PCU_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Xi/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Xi/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Xi/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_NJ_40100"' \
'"./AnalysisOutputs_Results.root"','"./Xi/AnalysisOutputs_Results.root"','"listResults_Xi_Default_40100"' \
'"./AnalysisOutputs_Results.root"','"./Xi/AnalysisOutputs_Results.root"','"listResults_Xi_Default_JC_40100"' \
'"./AnalysisOutputs_Results.root"','"./Xi/AnalysisOutputs_Results.root"','"listResults_Xi_Default_PCL_40100"' \
'"./AnalysisOutputs_Results.root"','"./Xi/AnalysisOutputs_Results.root"','"listResults_Xi_Default_PCU_40100"' \
'"./AnalysisOutputs_Results.root"','"./Xi/AnalysisOutputs_Results.root"','"listResults_Xi_Default_NJ_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./Lambda/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitInvMrd.root"','"./Lambda/AnalysisOutputs_FitInvMrd.root"','"listFitInvMrd_Lambda_Default_40100"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./Lambda/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitCbinRD.root"','"./Lambda/AnalysisOutputs_FitCbinRD.root"','"listFitCbinRD_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Lambda/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Lambda/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./Lambda/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_Lambda_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./Lambda/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_Lambda_Default_40100"' \
'"./AnalysisOutputs_FitCbinMC.root"','"./Lambda/AnalysisOutputs_FitCbinMC.root"','"listFitCbinMC_Lambda_Default_40100"' \
'"./AnalysisOutputs_EffInclMC.root"','"./Lambda/AnalysisOutputs_EffInclMC.root"','"listEffInclMC_Lambda_Default_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Lambda/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Lambda/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCL_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Lambda/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Lambda/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Lambda/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Lambda/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_PCU_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./Lambda/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./Lambda/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./Lambda/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_NJ_40100"' \
'"./AnalysisOutputs_Results.root"','"./Lambda/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_40100"' \
'"./AnalysisOutputs_Results.root"','"./Lambda/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_Results.root"','"./Lambda/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_PCL_40100"' \
'"./AnalysisOutputs_Results.root"','"./Lambda/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_PCU_40100"' \
'"./AnalysisOutputs_Results.root"','"./Lambda/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_NJ_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./Lambda/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_Lambda_Default_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./Lambda/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_Lambda_Default_JC_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./Lambda/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_Lambda_Default_PCL_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./Lambda/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_Lambda_Default_PCU_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./Lambda/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_Lambda_Default_NJ_40100"' \
'"./AnalysisOutputs_Loop1ndRD.root"','"./AntiLa/AnalysisOutputs_Loop1ndRD.root"','"listLoop1ndRD_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitInvMrd.root"','"./AntiLa/AnalysisOutputs_FitInvMrd.root"','"listFitInvMrd_AntiLa_Default_40100"' \
'"./AnalysisOutputs_Loop2ndRD.root"','"./AntiLa/AnalysisOutputs_Loop2ndRD.root"','"listLoop2ndRD_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitCbinRD.root"','"./AntiLa/AnalysisOutputs_FitCbinRD.root"','"listFitCbinRD_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./AntiLa/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./AntiLa/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitCbinJE.root"','"./AntiLa/AnalysisOutputs_FitCbinJE.root"','"listFitCbinJE_AntiLa_Default_40100"' \
'"./AnalysisOutputs_LoopIncMC.root"','"./AntiLa/AnalysisOutputs_LoopIncMC.root"','"listLoopIncMC_AntiLa_Default_40100"' \
'"./AnalysisOutputs_FitCbinMC.root"','"./AntiLa/AnalysisOutputs_FitCbinMC.root"','"listFitCbinMC_AntiLa_Default_40100"' \
'"./AnalysisOutputs_EffInclMC.root"','"./AntiLa/AnalysisOutputs_EffInclMC.root"','"listEffInclMC_AntiLa_Default_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./AntiLa/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./AntiLa/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCL_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./AntiLa/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./AntiLa/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_PCU_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./AntiLa/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_PCL_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./AntiLa/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_PCU_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"./AntiLa/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"./AntiLa/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_NJ_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"./AntiLa/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_NJ_40100"' \
'"./AnalysisOutputs_Results.root"','"./AntiLa/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_40100"' \
'"./AnalysisOutputs_Results.root"','"./AntiLa/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_Results.root"','"./AntiLa/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_PCL_40100"' \
'"./AnalysisOutputs_Results.root"','"./AntiLa/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_PCU_40100"' \
'"./AnalysisOutputs_Results.root"','"./AntiLa/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_NJ_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./AntiLa/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_AntiLa_Default_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./AntiLa/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_AntiLa_Default_JC_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./AntiLa/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_AntiLa_Default_PCL_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./AntiLa/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_AntiLa_Default_PCU_40100"' \
'"./AnalysisOutputs_MakeLaFdR.root"','"./AntiLa/AnalysisOutputs_MakeLaFdR.root"','"listMakeLaFdR_AntiLa_Default_NJ_40100"' \
'"./AnalysisOutputs_Results.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root"','"listResults_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root"','"listResults_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root"','"listResults_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_Results.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root"','"listResults_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Xi_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Kshort_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_Lambda_Default_OC_40100"' \
'"./AnalysisOutputs_LoopJetRD.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_LoopJetRD.root"','"listLoopJetRD_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrMC.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrMC.root"','"listEffCorrMC_AntiLa_Default_OC_40100"' \
'"./AnalysisOutputs_EffCorrJE.root"','"/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_EffCorrJE.root"','"listEffCorrJE_AntiLa_Default_OC_40100"' \
                                     
do
root -l -b -q CopyList.C\(${i}\)
done
#
exit 0
