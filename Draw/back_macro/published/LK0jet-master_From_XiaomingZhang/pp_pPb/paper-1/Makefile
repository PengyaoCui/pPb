SHELL = /bin/bash

SRC := $(wildcard *.tex)
TAGBASE := alicepreprint_CDS
TAG := $(TAGBASE).pdf
last_commit_hash=$(shell git rev-parse HEAD)
last_commit_date=$(shell git log -n 1 | grep Date)
is_clean=$(shell git diff --shortstat)
arg_for_diff := $(shell echo $(wordlist 2, 2, $(MAKECMDGOALS)) | sed 's|diff||g')
ifneq ($(arg_for_diff),)
	arg_for_diff := $(shell echo -a $(arg_for_diff))
else
	arg_for_diff := $(shell echo -a HEAD)
endif

all : $(TAG)
.PHONY : all

## 	sed -e "s/\\PHnumber{.*}/\\PHnumber{ Commited hash: $(last_commit_hash)}/g" -i "" alicepreprint_CDS.tex; \

%.pdf : %.tex %.sty %.bib $(SRC) Makefile
	mkdir -p ./.build
	cp -r * ./.build
	cd ./.build; \
	sed -e "s/\\PHnumber{.*}/\\PHnumber{ Commit hash: $(last_commit_hash)}/g" -i "" alicepreprint_CDS.tex; \
	sed -e "s/\\PHdate{.*}/\\PHdate{Committed $(last_commit_date) $(is_clean)}/g" -i "" alicepreprint_CDS.tex; \
	sed -e "s/\\PHyear{.*}/\\PHyear{}/g" -i "" alicepreprint_CDS.tex; \
	sed -e "s/\\\def\\\revision{.*}/\\\def\\\revision{$(last_commit_hash)}/g" -i "" userdefs.tex; \
	latexmk -pdf $<
	cp ./.build/$(TAG) .
	rm -rf ./.build

view : all
	@open $(TAG)
.PHONY : view

clean :
	latexmk -c
	rm $(TAG)
	rm -rf .build
.PHONY : clean

dist-clean :
	latexmk -C
	$(RM) *.bbl
.PHONY : dist-clean

open:
	@open $(TAG)

diff:
	../../utils/make_gitdiff.sh -m $(TAGBASE) $(arg_for_diff) 2>&1 | tee diff.log
	@echo [i] diff generation logged in diff.log

%:
	@:
