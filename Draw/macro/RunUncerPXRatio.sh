#!/bin/bash
#
for i in \
"\"Omega\"","\"0\"","\"100\"" \
"\"Omega\"","\"0\"","\"10\"" \
"\"Omega\"","\"10\"","\"40\"" \
"\"Omega\"","\"40\"","\"100\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 5 | root -l UncerPXRatio.C\(${i}\)
done
#
exit 0

