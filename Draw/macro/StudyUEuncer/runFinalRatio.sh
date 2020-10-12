#!/bin/bash
#


######################################################################
echo ==========================================
echo run particle ratio uncertainty 

for i in \
"\"0\"","\"100\"" \
"\"0\"","\"10\"" \
"\"10\"","\"40\"" \
"\"40\"","\"100\"" \

do

echo .q | sleep 0 | root -l LKRatioUncer.C\(${i}\)
echo .q | sleep 0 | root -l XKRatioUncer.C\(${i}\)
echo .q | sleep 0 | root -l OKRatioUncer.C\(${i}\)
echo .q | sleep 0 | root -l XLRatioUncer.C\(${i}\)
echo .q | sleep 0 | root -l OLRatioUncer.C\(${i}\)
echo .q | sleep 0 | root -l OXRatioUncer.C\(${i}\)
done

exit 0

