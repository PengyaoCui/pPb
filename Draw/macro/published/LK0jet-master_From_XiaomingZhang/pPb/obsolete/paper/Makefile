TEXSDIR   = ./
PICSDIR   = ./figures
FILENAME  = AliPubV0JetspPb

###

TEXSRCS   = $(shell find $(TEXSDIR) -maxdepth 2 -iname "*.tex")
PICS      = $(shell find $(PICSDIR) -maxdepth 2 -iname "*.eps")

VERS      = $(shell fgrep dver $(FILENAME).tex | head -n 1 | cut -d{ -f2 | cut -d} -f1)

ADDFILES  = Makefile

BACKFILES = $(PICS) $(TEXSRCS) 

ARCHFILES = $(TEXSRCS) alice.xml

PDFPICS   = $(patsubst %.eps,%.pdf,$(PICS))
EPSPICS   = $(patsubst %.pdf,%.eps,$(PPICS))

LATEX	  = latex
PDFTEX    = pdflatex
DVIPS	  = dvips
PS2PDF    = ps2pdf
EPS2EPS   = eps2eps
EPSTOPDF  = epstopdf
THUMBPDF  = thumbpdf
BIBTEX    = ./bin/bibtex.sh
VPDF	  = evince

ARCHTEX   := $(filter-out ./authors-paper.tex%,$(TEXSRCS)) ./cernphprep.cls 
ARCHTEX   := $(filter-out ./refpaper.tex%,$(ARCHTEX))
PAPTEX    := $(filter-out ./authors-preprint.tex%,$(TEXSRCS))
PAPTEX    := $(filter-out ./refpreprint.tex%,$(PAPTEX))
PAPPICS   := $(filter-out ./figures/c00Logos/alicelogo.eps ./figures/c00Logos/cernlogo.eps%,$(PICS))

default:	$(FILENAME).pdf

re:
	rm -f $(FILENAME).pdf
	$(BIBTEX)   $(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(BIBTEX)   $(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)

open:
	open $(FILENAME).pdf

$(FILENAME):		$(FILENAME).dvi

$(FILENAME).pdf:	$(FILENAME).tex $(TEXSRCS) $(ADDFILES) $(PDFPICS) 	
	$(BIBTEX)   $(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(BIBTEX)   $(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)

$(FILENAME).dvi:	$(FILENAME).tex $(TEXSRCS) $(ADDFILES)
	$(LATEX) 	$(FILENAME)
	$(BIBTEX)       $(FILENAME)
	$(LATEX) 	$(FILENAME)

$(FILENAME).ps:		$(FILENAME).dvi $(PICS)
	$(DVIPS) $(FILENAME).dvi -o $(FILENAME).ps


$(FILENAME).tar.gz:	backup

final:	$(FILENAME).tex $(TEXSRCS) $(ADDFILES) $(PDFPICS) 
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)
	$(PDFTEX) 	$(FILENAME)

dvi:	$(FILENAME).dvi

ps:	$(FILENAME).ps

gzip:	ps
	gzip $(FILENAME).ps

pdf:	$(FILENAME).pdf

ps2pdf:	$(FILENAME).dvi
	$(DVIPS) -Ppdf $(FILENAME).dvi -o $(FILENAME).ps
	$(PS2PDF) $(FILENAME).ps

print:  $(FILENAME).ps
	lpr $(FILENAME).ps

vdvi:	$(FILENAME).dvi
	xdvi $(FILENAME).dvi &

vps:	$(FILENAME).ps
	gv $(FILENAME).ps &

vpdf:	$(FILENAME).pdf
	$(VPDF) $(FILENAME).pdf &

edit:
	emacs $(FILENAME).tex

version: pdf
	mv $(FILENAME).pdf $(FILENAME)_${VERS}.pdf

clean:
	rm -f $(FILENAME).dvi $(FILENAME).toc .tmp.eps	\
	$(FILENAME).aux $(FILENAME).out $(FILENAME).tpt \
	$(FILENAME).bbl $(FILENAME).blg $(FILENAME).log \
	$(FILENAME).lof $(FILENAME).lot $(FILENAME).idx \
	$(FILENAME).ind $(FILENAME).ilg $(FILENAME).glo \
	$(FILENAME).blg $(FILENAME).brf missfont.log \
        texput.log core *.aux *.tmp multPbPbNotes.bib
	find $(TEXSDIR) $(PICSDIR) -name "*~" -type f -exec rm -f "{}" \;
	find $(TEXSDIR) $(PICSDIR) -type d -exec chmod 755 "{}" \;
	find $(TEXSDIR) $(PICSDIR) -type f -exec chmod 644 "{}" \;
	find $(TEXSDIR) -name "*.sh" -type f -exec chmod 755 "{}" \;
	find $(TEXSDIR) -name "*.aux" -type f -exec rm -v "{}" \;

realclean: clean
	rm -f $(FILENAME).ps.gz $(FILENAME).pdf $(PDFPICS) $(FILENAME).ps $(FILENAME).tar.gz archiv.tar.gz

backup:
	tar -cvzf $(FILENAME)_$(VERS).tar.gz $(FILENAME).tex $(BACKFILES) $(ADDFILES)

arxiv:
	tar -chvzf $(FILENAME)_arxiv_$(VERS).tar.gz $(ARCHTEX) $(PPICS) authors.xml ./img/alicelogo.pdf ./img/cernlogo.pdf

paper:    $(EPSPICS)
	tar -chvzf $(FILENAME)_plb_$(VERS).tar.gz $(PAPTEX) $(EPSPICS) authors.xml elsarticle.cls model1-num-names.bst

.phony: print clean backup arxiv

$(PDFPICS): %.pdf: %.eps
	$(EPS2EPS) $< .tmp.eps && $(EPSTOPDF) $(EPSOPTION) .tmp.eps --outfile=$@ && rm -f .tmp.eps

#$(EPSPICS): %.eps: %.pdf
#	pdftops -eps $< $@

