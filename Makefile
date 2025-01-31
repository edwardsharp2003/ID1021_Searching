# Define variables
TEX_FILE = rapport_searching.tex
PDF_FILE = rapport_searching.pdf

# Default target
all: $(PDF_FILE)

# Rule to build PDF with latexmk
$(PDF_FILE): $(TEX_FILE)
	latexmk -pdf -silent $(TEX_FILE)

# Cleanup files
clean:
	latexmk -c
	rm -f *.bbl *.blg

# Clean everything, including the PDF
cleanall:
	latexmk -C