#!bin/bash



cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/MLoverP/Loose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/MLoverP/Tight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/MLoverP/VLoose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/MLoverP/VvLoose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/SigExtrac/Loose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/SigExtrac/Tight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/TPCPID/Loose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/TPCPID/Tight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/Topological/Loose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/Topological/Tight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/Topological/VLoose
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/Topological/VTight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/TrackQuality/Tight
root -l -b -q runLocalStrangeJets.C

cd /afs/cern.ch/work/p/pcui/private/pPb/FullStatistic/ThisAna/Uncertainty/Incl/Omega/TrackQuality/VTight
root -l -b -q runLocalStrangeJets.C
