CC ?= cc
SUBDIRS = comp lang frontend
OUTS = comp/wlang-toc lang/wlang-irgen frontend/wlang
DESTDIR ?= /opt/will/bin/
VERSION = 1.0.0
CONFIG_H = frontend/config.h
all:
	echo "#define TOC \"$(DESTDIR)/wlang-toc\"" > $(CONFIG_H)
	echo "#define IRGEN \"$(DESTDIR)/wlang-irgen\"" >> $(CONFIG_H)
	echo "#define CC \"$(CC)\"" >> $(CONFIG_H)
	echo "#define VER \"$(VERSION)\"" >> $(CONFIG_H)
	@for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir || exit 1; \
    done

clean:
	@for dir in $(SUBDIRS); do \
	    $(MAKE) -C $$dir clean || exit 1; \
    done
	rm -f $(CONFIG_H)

install:
	mkdir -p $(DESTDIR)
	cp $(OUTS) $(DESTDIR)

git: clean
	git add .
	git commit -m "Updated: $(shell date)"
	git push

.PHONY: clean all install git