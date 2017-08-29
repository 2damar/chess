MAKE = make
SUBDIRS = src/board src/qt5

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)


clean: 
	$(MAKE) clean -C src/board
	$(MAKE) clean -C src/qt5
