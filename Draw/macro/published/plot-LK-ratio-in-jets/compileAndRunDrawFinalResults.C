void compileAndRunDrawFinalResults(Int_t iSwitchMacro = 0, TString sNameFileIn, TString sNameFileSysJets, TString sNameFileSysBulk = "", Int_t V0Type = 0, TString sNameFileSysJetsFD = "")
{
  TString sPathMacros = ".";
  TString sPathClasses = ".";
  TString sFunctionName;
  if(iSwitchMacro == 0)
    sFunctionName = "DrawFinalRatios";
  if(iSwitchMacro == 1)
    sFunctionName = "DrawFinalSpectra";
  if(iSwitchMacro == 2)
    sFunctionName = "DrawFD";
  if(iSwitchMacro == 3)
    sFunctionName = "DrawEff";
  if(iSwitchMacro == 4)
    sFunctionName = "DrawUncorrSpectra";

//  gROOT->LoadMacro(Form("%s/LoadLibraries.C", sPathClasses.Data()));
//  if(!LoadLibraries(sPathClasses.Data()))
//  {
//    printf("Error in LoadLibraries\n");
//    return;
//  }
//  printf("Libraries are OK.\n");
//  return;

  Bool_t bCheckObjects = 0;
  Bool_t bRun = 1;

  if(gROOT->LoadMacro(Form("%s/%s.C+", sPathMacros.Data(), sFunctionName.Data())) < 0)
    return;

  printf("%s compiled.\n", sFunctionName.Data());
  if(gSystem->Load(Form("%s/%s_C.so", sPathMacros.Data(), sFunctionName.Data())) < 0)
    return;

  if(bRun)
  {
    if(iSwitchMacro == 0)
      gROOT->ProcessLine(Form("%s\(\"%s\",\"%s\",\"%s\",\"%s\"\);", sFunctionName.Data(), sNameFileIn.Data(), sNameFileSysJets.Data(), sNameFileSysBulk.Data(), sNameFileSysJetsFD.Data()));
    if(iSwitchMacro == 1)
      gROOT->ProcessLine(Form("%s\(\"%s\",\"%s\",\"%s\",%d\);", sFunctionName.Data(), sNameFileIn.Data(), sNameFileSysJets.Data(), sNameFileSysBulk.Data(), V0Type));
    if(iSwitchMacro == 2)
      gROOT->ProcessLine(Form("%s\(\"%s\",\"%s\",\"%s\"\);", sFunctionName.Data(), sNameFileIn.Data(), sNameFileSysJets.Data(), sNameFileSysBulk.Data()));
    if(iSwitchMacro == 3)
      gROOT->ProcessLine(Form("%s\(\"%s\",\"%s\",\"%s\"\);", sFunctionName.Data(), sNameFileIn.Data(), sNameFileSysJets.Data(), sNameFileSysBulk.Data()));
    if(iSwitchMacro == 4)
      gROOT->ProcessLine(Form("%s\(\"%s\",\"%s\"\);", sFunctionName.Data(), sNameFileIn.Data(), sNameFileSysJets.Data()));
  }
}
