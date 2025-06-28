CC ?= wclang 
SRCS = transpiler.c 
TARG = wlang-toc
$(TARG): $(SRCS)
	$(CC) -O2 -o $(TARG) $^

clean:
	rm -f $(TARG)