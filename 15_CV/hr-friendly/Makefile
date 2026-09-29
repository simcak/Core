LATEXMK = latexmk -pdf -interaction=nonstopmode -halt-on-error
CVS     = simcak_cs.pdf simcak_en.pdf

all: $(CVS)

%.pdf: %.tex cvstyle.sty me.jpg
	$(LATEXMK) $<

clean:
	latexmk -c

fclean:
	latexmk -C

re: fclean all

.PHONY: all clean fclean re
