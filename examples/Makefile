# Toolchain
MAKE = make
RM = rm -f

# List of examples to be built
EXAMPLES = irq led mini-usb-serial serial types

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
