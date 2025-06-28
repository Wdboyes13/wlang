CC ?= cc
SUBDIRS = comp lang frontend
OUTS = comp/wlang-toc lang/wlang-irgen frontend/wlang
DESTDIR ?= /opt/will/bin/
VERSION = 1.0.0
all:
	echo "#define TOC \"$(DESTDIR)/wlang-toc\"" > frontend/config.h
	echo "#define IRGEN \"$(DESTDIR)/wlang-irgen\"" >> frontend/config.h
	echo "#define CC \"$(CC)\"" >> frontend/config.h
	echo "#define VER \"$(VERSION)\"" >> frontend/config.h
	@for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir || exit 1; \
    done

clean:
	@for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir clean || exit 1; \
    done
	rm -f frontend/config.h

install:
	mkdir -p $(DESTDIR)
	cp $(OUTS) $(DESTDIR)

.PHONY: clean all install