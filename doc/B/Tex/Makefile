TARGET=b08_2_fin_report
TEX=$(TARGET).tex
PDF=$(TARGET).pdf
all: $(PDF)
$(PDF): $(TEX) title/* files/*
		xelatex -shell-escape $<
spell:
		aspell -l el_gr --ignore-case=true -c $(TEX)
