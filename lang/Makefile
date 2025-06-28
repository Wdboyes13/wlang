FX    = flex
BS    = bison
CC    ?= wclang

BSSRC = parser.y
FXSRC = lex.l

BSOUT_C = parser.tab.c
BSOUT_H = parser.tab.h
BSOUT = $(BSOUT_C) $(BSOUT_H)
FXOUT = lex.yy.c

CFLAGS = -O2

OBJS = parser.tab.o lex.yy.o

TARG  = wlang-irgen

LDFLAGS = -L/opt/will/lib -lfl

all: $(TARG)

$(TARG): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

$(BSOUT): $(BSSRC)
	$(BS) -d $<

parser.tab.o: $(BSOUT_C)
	$(CC) -c $< -o $@ $(CFLAGS)

$(FXOUT): $(FXSRC) $(BSOUT_H)
	$(FX) $<

lex.yy.o: $(FXOUT) $(BSOUT_H)
	$(CC) -c $(FXOUT) -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(BSOUT_C) $(BSOUT_H) $(FXOUT) $(TARG)