# Toolchain
MAKE = make
RM = rm -f

# List of exampels to be built
EXAMPLES = mini-usb-serial led types

# Example dependency
EXDIRS = $(EXAMPLES:%=ex-%)
CLEANDIRS = $(EXAMPLES:%=clean-%)

# Targets
.PHONY: all clean

all: $(EXDIRS)

clean: $(CLEANDIRS)

$(EXDIRS):
	$(MAKE) -C $(@:ex-%=%)

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean
