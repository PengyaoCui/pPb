#!/bin/bash
#
for i in \
"\"Omega\"","\"0\"","\"100\"" \
"\"Xi\"","\"0\"","\"100\"" \
"\"Xi\"","\"0\"","\"10\"" \
"\"Xi\"","\"10\"","\"40\"" \
"\"Xi\"","\"40\"","\"100\"" \
"\"Lambda_sum\"","\"0\"","\"100\"" \
"\"Lambda_sum\"","\"0\"","\"10\"" \
"\"Lambda_sum\"","\"10\"","\"40\"" \
"\"Lambda_sum\"","\"40\"","\"100\"" \

do

#root -l UnctSource.C\{${i}\)
#root -l MakeRatio.C\(${i}\)
echo .q | sleep 0 | root -l UncerRatio.C\(${i}\)
done
#
exit 0

