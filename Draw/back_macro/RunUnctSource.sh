#!/bin/bash
#
for i in \
  "\"Kshort\"","\"0\"","\"100\"","\"CompetMass\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"CompetMass\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"CompetMass\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"CompetMass\"" \
  "\"Kshort\"","\"0\"","\"100\"","\"MLoverP\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"MLoverP\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"MLoverP\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"MLoverP\"" \
  "\"Kshort\"","\"0\"","\"100\"","\"SigExtrac\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"SigExtrac\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"SigExtrac\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"SigExtrac\"" \
  "\"Kshort\"","\"0\"","\"100\"","\"Topological\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"Topological\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"Topological\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"Topological\"" \
  "\"Kshort\"","\"0\"","\"100\"","\"TPCPID\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"TPCPID\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"TPCPID\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"TPCPID\"" \
  "\"Kshort\"","\"0\"","\"100\"","\"TrackQuality\"" \
  "\"Kshort\"","\"0\"","\"10\"","\"TrackQuality\"" \
  "\"Kshort\"","\"10\"","\"40\"","\"TrackQuality\"" \
  "\"Kshort\"","\"40\"","\"100\"","\"TrackQuality\"" \
  "\"Lambda\"","\"0\"","\"100\"","\"MLoverP\"" \
  "\"Lambda\"","\"0\"","\"10\"","\"MLoverP\"" \
  "\"Lambda\"","\"10\"","\"40\"","\"MLoverP\"" \
  "\"Lambda\"","\"40\"","\"100\"","\"MLoverP\"" \
  "\"Lambda\"","\"0\"","\"100\"","\"SigExtrac\"" \
  "\"Lambda\"","\"0\"","\"10\"","\"SigExtrac\"" \
  "\"Lambda\"","\"10\"","\"40\"","\"SigExtrac\"" \
  "\"Lambda\"","\"40\"","\"100\"","\"SigExtrac\"" \
  "\"Lambda\"","\"0\"","\"100\"","\"Topological\"" \
  "\"Lambda\"","\"0\"","\"10\"","\"Topological\"" \
  "\"Lambda\"","\"10\"","\"40\"","\"Topological\"" \
  "\"Lambda\"","\"40\"","\"100\"","\"Topological\"" \
  "\"Lambda\"","\"0\"","\"100\"","\"TPCPID\"" \
  "\"Lambda\"","\"0\"","\"10\"","\"TPCPID\"" \
  "\"Lambda\"","\"10\"","\"40\"","\"TPCPID\"" \
  "\"Lambda\"","\"40\"","\"100\"","\"TPCPID\"" \
  "\"Lambda\"","\"0\"","\"100\"","\"TrackQuality\"" \
  "\"Lambda\"","\"0\"","\"10\"","\"TrackQuality\"" \
  "\"Lambda\"","\"10\"","\"40\"","\"TrackQuality\"" \
  "\"Lambda\"","\"40\"","\"100\"","\"TrackQuality\"" \
  "\"AntiLa\"","\"0\"","\"100\"","\"MLoverP\"" \
  "\"AntiLa\"","\"0\"","\"10\"","\"MLoverP\"" \
  "\"AntiLa\"","\"10\"","\"40\"","\"MLoverP\"" \
  "\"AntiLa\"","\"40\"","\"100\"","\"MLoverP\"" \
  "\"AntiLa\"","\"0\"","\"100\"","\"SigExtrac\"" \
  "\"AntiLa\"","\"0\"","\"10\"","\"SigExtrac\"" \
  "\"AntiLa\"","\"10\"","\"40\"","\"SigExtrac\"" \
  "\"AntiLa\"","\"40\"","\"100\"","\"SigExtrac\"" \
  "\"AntiLa\"","\"0\"","\"100\"","\"Topological\"" \
  "\"AntiLa\"","\"0\"","\"10\"","\"Topological\"" \
  "\"AntiLa\"","\"10\"","\"40\"","\"Topological\"" \
  "\"AntiLa\"","\"40\"","\"100\"","\"Topological\"" \
  "\"AntiLa\"","\"0\"","\"100\"","\"TPCPID\"" \
  "\"AntiLa\"","\"0\"","\"10\"","\"TPCPID\"" \
  "\"AntiLa\"","\"10\"","\"40\"","\"TPCPID\"" \
  "\"AntiLa\"","\"40\"","\"100\"","\"TPCPID\"" \
  "\"AntiLa\"","\"0\"","\"100\"","\"TrackQuality\"" \
  "\"AntiLa\"","\"0\"","\"10\"","\"TrackQuality\"" \
  "\"AntiLa\"","\"10\"","\"40\"","\"TrackQuality\"" \
  "\"AntiLa\"","\"40\"","\"100\"","\"TrackQuality\"" \
  "\"Xi\"","\"0\"","\"100\"","\"MLoverP\"" \
  "\"Xi\"","\"0\"","\"10\"","\"MLoverP\"" \
  "\"Xi\"","\"10\"","\"40\"","\"MLoverP\"" \
  "\"Xi\"","\"40\"","\"100\"","\"MLoverP\"" \
  "\"Xi\"","\"0\"","\"100\"","\"SigExtrac\"" \
  "\"Xi\"","\"0\"","\"10\"","\"SigExtrac\"" \
  "\"Xi\"","\"10\"","\"40\"","\"SigExtrac\"" \
  "\"Xi\"","\"40\"","\"100\"","\"SigExtrac\"" \
  "\"Xi\"","\"0\"","\"100\"","\"Topological\"" \
  "\"Xi\"","\"0\"","\"10\"","\"Topological\"" \
  "\"Xi\"","\"10\"","\"40\"","\"Topological\"" \
  "\"Xi\"","\"40\"","\"100\"","\"Topological\"" \
  "\"Xi\"","\"0\"","\"100\"","\"TPCPID\"" \
  "\"Xi\"","\"0\"","\"10\"","\"TPCPID\"" \
  "\"Xi\"","\"10\"","\"40\"","\"TPCPID\"" \
  "\"Xi\"","\"40\"","\"100\"","\"TPCPID\"" \
  "\"Xi\"","\"0\"","\"100\"","\"TrackQuality\"" \
  "\"Xi\"","\"0\"","\"10\"","\"TrackQuality\"" \
  "\"Xi\"","\"10\"","\"40\"","\"TrackQuality\"" \
  "\"Xi\"","\"40\"","\"100\"","\"TrackQuality\"" \
  "\"Omega\"","\"0\"","\"100\"","\"MLoverP\"" \
  "\"Omega\"","\"0\"","\"10\"","\"MLoverP\"" \
  "\"Omega\"","\"10\"","\"40\"","\"MLoverP\"" \
  "\"Omega\"","\"40\"","\"100\"","\"MLoverP\"" \
  "\"Omega\"","\"0\"","\"100\"","\"TrackQuality\"" \
  "\"Omega\"","\"0\"","\"10\"","\"TrackQuality\"" \
  "\"Omega\"","\"10\"","\"40\"","\"TrackQuality\"" \
  "\"Omega\"","\"40\"","\"100\"","\"TrackQuality\"" \
  "\"Omega\"","\"0\"","\"100\"","\"TPCPID\"" \
  "\"Omega\"","\"0\"","\"10\"","\"TPCPID\"" \
  "\"Omega\"","\"10\"","\"40\"","\"TPCPID\"" \
  "\"Omega\"","\"40\"","\"100\"","\"TPCPID\"" \
  "\"Omega\"","\"0\"","\"100\"","\"SigExtrac\"" \
  "\"Omega\"","\"0\"","\"10\"","\"SigExtrac\"" \
  "\"Omega\"","\"10\"","\"40\"","\"SigExtrac\"" \
  "\"Omega\"","\"40\"","\"100\"","\"SigExtrac\"" \
  "\"Omega\"","\"0\"","\"100\"","\"Topological\"" \
  "\"Omega\"","\"0\"","\"10\"","\"Topological\"" \
  "\"Omega\"","\"10\"","\"40\"","\"Topological\"" \
  "\"Omega\"","\"40\"","\"100\"","\"Topological\"" \

do
  #root -l UnctSource.C\(${i}\)
  echo .q | sleep 0 | root -l UnctSource.C\(${i}\)

done
#
exit 0

