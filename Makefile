SRCS = $(wildcard *.c)
DSTS = $(patsubst %.c, %, $(SRCS))
SUBDIRS = $(shell find -type d -not -path "./include" -not -path "./.git*")
SUBDIRS_CLEAN = $(addsuffix .clean, $(SUBDIRS))

default: $(DSTS)

% : %.c
	gcc -g -Wall -Werror -O3 -o $@ $< -lm

clean: $(SUBDIRS_CLEAN)

..clean:
	rm -rf $(DSTS) a.out

%.clean : %
	rm -f `find -iname cscope.out`
	rm -f `find -iname tags -not -path "./.git*"`
	rm -f `find -iname *.so`
	make -C $< clean
