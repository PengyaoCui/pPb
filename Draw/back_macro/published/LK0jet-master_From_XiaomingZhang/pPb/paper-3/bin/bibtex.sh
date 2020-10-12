#!/bin/bash

fname=$1

if test -z "$fname"; then
    exit 123
fi

lfile=`basename $fname .tex`.aux

if test -n "`fgrep -i %\\bibtextrue ${fname}.tex`"; then
    echo "*** bibtex not run since it is disabled in ${fname}.tex ***"
    exit 0
fi

if test -n "`fgrep -i citation $lfile`"; then
    bibtex $fname
fi

