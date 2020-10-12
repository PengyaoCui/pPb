#!/bin/bash
#
for i in \
"\"Kshort\"","\"Incl\"" \
"\"Kshort\"","\"JE\"" \
"\"Kshort\"","\"UE\"" \
"\"Lambda_sum\"","\"Incl\"" \
"\"Lambda_sum\"","\"JE\"" \
"\"Lambda_sum\"","\"UE\"" \
"\"Xi\"","\"Incl\"" \
"\"Xi\"","\"JE\"" \
"\"Xi\"","\"UE\"" \
"\"Omega\"","\"Incl\"" \
"\"Omega\"","\"JE\"" \
"\"Omega\"","\"UE\"" \

do

echo .q | sleep 2 | root -l SpectwCent.C\(${i}\)
done
#
exit 0

