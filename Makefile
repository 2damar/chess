MAKE = make
SUBDIRS = src/qt5

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

clean: 
	$(MAKE) clean -C $(SUBDIRS)
