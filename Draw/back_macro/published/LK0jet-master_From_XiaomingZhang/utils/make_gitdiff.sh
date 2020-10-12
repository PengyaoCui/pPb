#!/bin/bash

function usage()
{
	echo "$0 [-a <hash>] [-b <another hash>] [-n <remote branch for a>] [-m <main>] [-h]"
	echo "    -n: remote branch for a is master by default"
	echo "    -a: no argument with -a will result in comparison to the *local* HEAD; -a RHEAD will diff against the *remote* HEAD on a branch specified by -n"
	echo "    -b: no argument [default is 'this'] with -b will result in comparison to the working copy - no git calls; if arg is HEAD *local* head will be used (discarding the uncommitted changes)"
	echo "    -f: fetch from the remote - enables getting things from the server rather than relying on the local .git repository state"
	echo "    -m: main tex file defaults to main"
	echo "    note: short commit hashes are used by default"
	exit 1
}

function exit_if_no_git()
{
	git rev-parse --git-dir > /dev/null 2>&1
	retv=$?
	[ ! $retv == "0" ] && echo "[e] this $PWD is not under git ... bailing out." && exit 1
}

function clone_and_make()
{
	echo
	local revision=$1
	local wdir=$draft_dir
	cd $draft_dir
	local git_subdir=`git rev-parse --show-prefix`
	local git_topdir=`git rev-parse --show-toplevel`
	local git_topbasedir=`basename ${git_topdir}`
	local remote_addr=`git remote -v | grep fetch | cut -f 2 | cut -d " " -f 1`

	if [ ${revision} == "this" ]; then
		echo "[i] making in the local dir..."
	else
		wdir=`mktemp -d -t ${revision}`
		tmp_dirs="$tmp_dirs $wdir"
		echo "[i] working dir ${wdir}"
		cd $wdir
		if [ ${git_fetch} == "yes" ];
		then
			echo "[i] fetch enabled... will clone..."
			git clone $remote_addr
		else
			echo "[i] no fetch stay local..."
			cp -r ${git_topdir} .
		fi
		echo "[i] current dir: ${PWD}"
		echo "[i] git top basedir ${git_topbasedir}"
		echo "[i] git subdir ${git_subdir}"
		wdir=$PWD/${git_topbasedir}/${git_subdir}
		cd $wdir
		echo "[i] current dir: ${PWD}"
		#git checkout $revision
		echo "[i] resetting to $revision"
		git reset --hard $revision
		git rev-parse --short HEAD
		git status
	fi
	echo "[i] running latexmk..."
	latexmk -pdf $main_file
	revision_dir=$wdir
	echo "[i] latexmk done."
}

exit_if_no_git

tmp_dirs=""
commit_a="HEAD"
commit_b="this"
is_a_head=false
is_a_rhead=false
is_b_head=false
remote_branch="master"
main_file="main"
git_fetch="no"
while getopts ":a:b:n:m:h" opt; do
	case $opt in
		a)
			commit_a=$OPTARG
			[ -z ${commit_a} ] && commit_a="HEAD"
			;;
		b)
			commit_b=$OPTARG
			[ -z ${commit_b} ] && commit_b="this"
			;;
		n)
			remote_branch=$OPTARG
			;;
		m)
			main_file=$OPTARG
			;;
		f)
			git_fetch="yes"
			;;
		h)
			usage
			;;
		\?)
			echo "[e] Invalid option: -$OPTARG" >&2
			exit 1
			;;
		:)
			echo "[e] Option -$OPTARG requires an argument." >&2
			exit 1
			;;
	esac
done

[ -z $commit_a ] && usage

[ ${commit_a} == ${commit_b} ] && echo "[e] comparison to the same commits? bailing out." && exit 1

remote_addr=`git remote -v | grep fetch | cut -f 2 | cut -d " " -f 1`
## [ ${commit_a} == "HEAD" ] && commit_a=`git ls-remote ${remote_addr} | grep HEAD | cut -f 1` && is_a_head=true
[ ${commit_a} == "RHEAD" ] && commit_a=`git ls-remote ${remote_addr} ${remote_branch} | cut -f 1 ` && is_a_rhead=true
[ ${commit_a} == "HEAD" ] && commit_a=`git rev-parse --short HEAD` && is_a_head=true
[ ${commit_b} == "HEAD" ] && commit_b=`git rev-parse --short HEAD` && is_b_head=true

[ ${commit_a} == ${commit_b} ] && echo "[e] comparison to the same commits? bailing out." && exit 1

[ ! -f ${main_file}.tex ] && echo "[e] no file ${main_file}.tex found... " && usage

draft_dir=`pwd`

# git_subdir=`git rev-parse --show-prefix`
# git_topdir=`git rev-parse --show-toplevel`
# git_topbasedir=`basename ${git_topdir}`
# tmp_dir_a=`mktemp -d -t ${commit_a} 2> /dev/null`
# tmp_dir_b=`mktemp -d -t ${commit_b} 2> /dev/null`
# git_src_a=${tmp_dir_a}/${git_topbasedir}/${git_subdir}
# git_src_b=${tmp_dir_b}/${git_topbasedir}/${git_subdir}

# echo "[i] git temp dir: $tmp_dir_a $tmp_dir_b"
echo "[i] will compare hash $commit_a [*local* HEAD ? $is_a_head *remote* HEAD ? $is_a_rhead] with $commit_b [*local* HEAD ? $is_b_head]"

clone_and_make $commit_a
cd ${revision_dir}
rev_a_dir=${revision_dir}
commit_a=`git rev-parse --short HEAD`
echo "[i] $commit_a dir is ${rev_a_dir}"

clone_and_make $commit_b
cd ${revision_dir}
rev_b_dir=${revision_dir}
[ ! ${commit_b} == "this" ] && commit_b=`git rev-parse --short HEAD`
echo "[i] $commit_b dir is ${rev_b_dir}"

cd ${rev_b_dir}
opts="--disable-citation-markup"
if [[ ! -z `grep -Ewe '\\\(include|input)' ${main_file}.tex` ]]; then
	opts="${opts} --flatten"
fi
echo "[i] running latex diff..."
diff_file=${main_file}_diff
rm ${diff_file}*.*
latexdiff $opts ${rev_a_dir}/${main_file}.tex ${rev_b_dir}/${main_file}.tex > ${rev_b_dir}/${diff_file}.tex
echo "[i] running pdflatex..."
cp ${rev_b_dir}/${main_file}.bib ${diff_file}.bib
pdflatex -interaction nonstopmode ${diff_file}
#bibtex ${diff_file}
#pdflatex -interaction nonstopmode ${diff_file}
#pdflatex -interaction nonstopmode ${diff_file}
if [[ ! -z `cat *.aux */*.aux 2>&1 /dev/null | grep citation` ]]; then
    bibtex -terse ${diff_file}.aux
    pdflatex -interaction nonstopmode ${diff_file}.tex
    pdflatex -interaction nonstopmode ${diff_file}.tex
fi
echo "[i] copying files..."
output_file=${draft_dir}/diff_${commit_a}_${commit_b}.pdf
cp -v ${rev_b_dir}/${diff_file}.pdf ${output_file}
cp -v ${rev_a_dir}/${main_file}.pdf ${main_file}_${commit_a}.pdf
cp -v ${rev_b_dir}/${main_file}.pdf ${main_file}_${commit_b}.pdf

echo "[i] dir a: ${rev_a_dir}"
echo "[i] dir b: ${rev_b_dir}"

for tdir in $tmp_dirs
do
	echo "[i] removing $tdir"
	rm -rf $tdir
done

if [ -f ${output_file} ];
then
	echo "[i] commit ${commit_a} pdf: ${main_file}_${commit_a}.pdf"
	echo "[i] commit ${commit_b} pdf: ${main_file}_${commit_b}.pdf"
	echo "[i] diff output in ${output_file}"
else
	echo "[e] unable to produce output."
	echo "[i] hint: try to fix problems by running:"
	echo "    $ pdflatex ${rev_b_dir}/${diff_file}.tex"
fi
