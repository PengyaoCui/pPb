#!/bin/bash


######################################################################
echo ==========================================
echo run UEUncer

rm result/UEUncer.root
for i in \
"\"Kshort\"","\"0\"","\"100\"" \
"\"Kshort\"","\"0\"","\"10\"" \
"\"Kshort\"","\"10\"","\"40\"" \
"\"Kshort\"","\"40\"","\"100\"" \
"\"Lambda\"","\"0\"","\"100\"" \
"\"Lambda\"","\"0\"","\"10\"" \
"\"Lambda\"","\"10\"","\"40\"" \
"\"Lambda\"","\"40\"","\"100\"" \
"\"AntiLa\"","\"0\"","\"100\"" \
"\"AntiLa\"","\"0\"","\"10\"" \
"\"AntiLa\"","\"10\"","\"40\"" \
"\"AntiLa\"","\"40\"","\"100\"" \
"\"Xi\"","\"0\"","\"100\"" \
"\"Xi\"","\"0\"","\"10\"" \
"\"Xi\"","\"10\"","\"40\"" \
"\"Xi\"","\"40\"","\"100\"" \
"\"Omega\"","\"0\"","\"100\"" \
"\"Omega\"","\"0\"","\"10\"" \
"\"Omega\"","\"10\"","\"40\"" \
"\"Omega\"","\"40\"","\"100\"" \

do

echo .q | sleep 0 | root -l UEUncer.C\(${i}\)
done

exit