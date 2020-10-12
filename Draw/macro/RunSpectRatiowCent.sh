#!/bin/bash
#
for i in \
"\"Kshort\"" \
"\"Lambda_sum\"" \
"\"Xi\"" \
"\"Omega\"" \

do

echo .q | sleep 2 | root -l SpectRatiowCent.C\(${i}\)
done
#
exit 0

