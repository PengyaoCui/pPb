# Discussions

## 2016/11/28

### Description
- Discussion based on git commit:
  - 5cad7f1b2114048081887a8ef8c69b7077d5e3c3

### Mail
- (**Todo**) Provide data to plot fig 1 in pp with exactly the same conditions?

> I need more time to figure it out.


- (DONE) Check in fig2, whether the system in pp is the final version?


> No, you can find the new version, in AnaSystematic_1.root


- (**To be done**) Check in fig3, whether it is the final version
 - Also provide the data to for the uncertainty sources

> 1. yes, this is the final version, you can find the datapoint in
>
> AnaL2K_Pt_PtJE.Root
>
> within list name
>
> pplistHD_JC04_JR04_PtJ10
>
> hKshort_Syst
>
> hLamnda_Syst
>
> hAntiLa_Syst.
>
>
> 2. The uncertainty sources are stored in AnaSystematic.root within different lists
>
> list_UE_Uncert
>
>is Underlying source, for different V0 and ratio
>
> list_Inclusive_Uncert for V0 reconstruction
>
> list_JetPt_Uncert jet Pt scale
>
> list_FD_Uncert FD correction
>
>
> example:
>
> for kshort, in the list_UE_Uncert, “hKshort” is the Underlying source for kshort
>
> for lambda, in the list_UE_Uncert, “hlambda” is the Underlying source for Lambda


- (**Todo**) Check fig5, whether it is the final version
 - In the new p-Pb result, the uncertainty on V0 reconstruction (by varying the invariant mass fit region) now is taken from the inclusive V0s. For V0s in jets, only the extra uncertainties on jet pT scale and UE subtraction are considered. Have it been updated in pp?

> 1. No, it is an old version, the data point used in the preliminary, can be found in the AnaSystematic.root with list name
>
> list_Detail_HD_R4_Uncert
>
>the InclLKRatio is v0 reconstruction
>
> FDLKRatio is the FD subtraction
>
> JetLKratio is the Jet Pt scale
>
> UELKRatio is the UE subtraction
>
> For the total Uncert, I recalculate the four components I mention before.
> please, do not use hLKRatio as total uncertainty in the root file.
>
>
> 2. I consider the four components I mentioned.
> we can discuss about this point. maybe i miss some information.


- (**DONE**) Check uncertainty on fig6
  - is uncertainty the final version
  - or where I can find the final uncertainty.
  - Is it in file of AnaSystematic.root? But there is no illustration for this file...

> No, this is an old version, you can find the new datapoint in AnaL2K_Pt_PtJE.root file.



- (**DONE**) Fig 7 in pp, see my comment on file of ThreePTBin.root, how I can get the systematic uncertainty? Better to provide a macro to plot the result out.

> Actually, only statistic uncertainties included, since, I don’t know how to deal with the systematic uncertainties.



- Fig8, the pp (right) result different from preliminary, again, where is / how to get the final version

> This is an old version of datapoint, please check  AnaL2K_Pt_PtJE.root


- Check fig9: correct or not?

> pp data point store at AnaL2K_Pt_PtJE.root, compared to the preliminary, the pPb results have been changed.
