#  Project Name
PROJECT = mbed_mini-usb-serial

# Directory structure
SOURCEDIRS = src
INCLUDEDIRS = include
BUILDDIR = build
OUTDIR = bin

#  Compiler/Assembler/Linker/etc.
GCC = arm-none-eabi-gcc
LDSCRIPT = ../../lpc17xx/ldscript_rom_gnu.ld
OBJCOPY = arm-none-eabi-objcopy
MKDIR = mkdir
RM = rm -f

#  Compiler and linker flags
CFLAGS = -Wall -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -O2
CFLAGS += -ffunction-sections -fdata-sections -D__RAM_MODE__=0
CFLAGS += -I../../include/device -I../../include/drivers -I../../include/mbed
CFLAGS += $(foreach DIR, $(INCLUDEDIRS), -I$(DIR))
LDFLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -O2 -nostartfiles
LDFLAGS += -Wl,--gc-sections,-Map=$(BUILDDIR)/$(PROJECT).map -T$(LDSCRIPT) -u _sbrk
LDLIBS = -L../../lib -lc -lgcc -lm -lmbed 

# Source and object files
CFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.c))
OBJS = $(foreach CFILE, $(CFILES), $(BUILDDIR)/$(basename $(notdir $(CFILE))).o) 

# Search path
VPATH = $(foreach DIR, $(SOURCEDIRS), $(strip $(DIR)):)

# Build rules
.PHONY: all clean 

all: $(BUILDDIR)/$(PROJECT).hex $(OUTDIR)/$(PROJECT).bin

clean:
	$(RM) $(OBJS)
	$(RM) $(BUILDDIR)/$(PROJECT).*
	$(RM) $(OUTDIR)/$(PROJECT).*
	
$(OUTDIR)/$(PROJECT).bin: $(BUILDDIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary -j .text -j .data $(BUILDDIR)/$(PROJECT).elf $(OUTDIR)/$(PROJECT).bin

$(BUILDDIR)/$(PROJECT).hex: $(BUILDDIR)/$(PROJECT).elf
	$(OBJCOPY) -R .stack -O ihex $(BUILDDIR)/$(PROJECT).elf $(BUILDDIR)/$(PROJECT).hex

$(BUILDDIR)/$(PROJECT).elf: $(OBJS)
	$(GCC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(OBJS): | $(BUILDDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(BUILDDIR): | $(OUTDIR)
	$(MKDIR) $(BUILDDIR)
