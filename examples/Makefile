# Toolchain
MAKE = make
RM = rm -f

# List of exampels to be built
EXAMPLES = irq mini-usb-serial led types

# Examples targets
EXDIRS = $(EXAMPLES:%=ex-%)
CLEANDIRS = $(EXAMPLES:%=clean-%)

# Build rules
.PHONY: all clean

all: $(EXDIRS)

clean: $(CLEANDIRS)

$(EXDIRS):
	$(MAKE) -C $(@:ex-%=%)

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean
