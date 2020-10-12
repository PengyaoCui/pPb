#!/bin/bash
#
for i in \
"\"Kshort\"" \
"\"Xi\"" \
"\"Omega\"" \
"\"Lambda\"" \
"\"AntiLa\"" \

do

echo .q | sleep 10 | root -l PtSpect.C\(${i}\)
done
#
exit 0

