# Library name
LIBNAME = libmbed

# Directory structure
SOURCEDIRS = src/device src/device/asm src/drivers src/mbed
INCLUDEDIRS = include include/lpc17xx include/lpc17xx/device include/lpc17xx/drivers include/mbed
BUILDDIR = build
OUTDIR = lib
DOCROOT = doc
EXROOT = examples

# Toolchain
GCC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = arm-none-eabi-ar
MAKE = make
MKDIR = mkdir
RM = rm -f
CP = cp
DOXYGEN = doxygen

#  Compiler and linker flags
CFLAGS = -Wall -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -O2 -ffunction-sections -fdata-sections -D__RAM_MODE__=0
CFLAGS += $(foreach DIR, $(INCLUDEDIRS), -I$(DIR))
ASFLAGS = -mcpu=cortex-m3 --defsym RAM_MODE=0
ARFLAGS = rcv

# Source and object files
CFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.c))
OBJS = $(foreach CFILE, $(CFILES), $(BUILDDIR)/$(basename $(notdir $(CFILE))).o) 

# ASM source and object files
SFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.s))
ASMOBJS = $(foreach SFILE, $(SFILES), $(BUILDDIR)/asm/$(basename $(notdir $(SFILE))).o)

# Search path
VPATH = $(foreach DIR, $(SOURCEDIRS), $(strip $(DIR)):)

# Build rules
.PHONY: all clean

all: mbed-doc mbed-examples mbed-lib

$(OUTDIR)/$(LIBNAME).a: $(OBJS) $(ASMOBJS)
	$(AR) $(ARFLAGS) $(OUTDIR)/$(LIBNAME).a $(OBJS) $(ASMOBJS)

$(BUILDDIR)/%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/asm/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

$(OBJS) $(ASMOBJS): | $(BUILDDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(BUILDDIR): | $(OUTDIR)
	$(MKDIR) $(BUILDDIR)
	$(MKDIR) $(BUILDDIR)/asm

clean:
	$(RM) $(OBJS)
	$(RM) $(ASMOBJS)
	$(RM) $(OUTDIR)/$(LIBNAME).a
	$(MAKE) -C $(EXROOT) clean

mbed-doc:
	$(DOXYGEN)
	$(MAKE) -C $(DOCROOT)/latex
	$(CP) $(DOCROOT)/latex/refman.pdf $(DOCROOT)/

mbed-examples: mbed-lib
	$(MAKE) -C $(EXROOT)
	
mbed-lib: $(OUTDIR)/$(LIBNAME).a | $(OUTDIR) $(BUILDDIR)

