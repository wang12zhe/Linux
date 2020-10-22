SUBDIRS = $(shell find . * -type d | grep -v "\.")

.PHONY:all clean

all:
	@for subdir in $(SUBDIRS); do $(MAKE) -C $$subdir; done

clean:
	@for subdir in $(SUBDIRS); do $(MAKE) -C $$subdir clean;done
