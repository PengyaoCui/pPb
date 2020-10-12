#!/bin/bash
#
for i in \
  "\"Kshort\"","\"0\"","\"100\"","\"Topological\"" \

do
  root -l UnctSource.C\(${i}\)
  #echo .q | sleep 2 | root -l UnctSource.C\(${i}\)

done
#
exit 0

