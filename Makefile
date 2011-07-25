# Library name
LIBNAME = libmbed

# Directory structure
SOURCEDIRS = src/device src/device/asm src/drivers src/mbed
INCLUDEDIRS = include include/lpc17xx include/lpc17xx/device include/lpc17xx/drivers include/mbed
BUILDDIR = build
OUTDIR = lib

# Toolchain
GCC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = ar -rvs
MKDIR = mkdir
RM = rm -f

#  Compiler and linker flags
CFLAGS = -Wall -mcpu=cortex-m3 -mthumb -mfloat-abi=softfp -O2 -ffunction-sections -fdata-sections -D__RAM_MODE__=0
CFLAGS += $(foreach DIR, $(INCLUDEDIRS), -I$(DIR))
ASFLAGS = -mcpu=cortex-m3 --defsym RAM_MODE=0

# Source and object files
CFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.c))
OBJS = $(foreach CFILE, $(CFILES), $(BUILDDIR)/$(basename $(notdir $(CFILE))).o) 

# ASM source and object files
SFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.s))
ASMOBJS = $(foreach SFILE, $(SFILES), $(BUILDDIR)/asm/$(basename $(notdir $(SFILE))).o)

# Search path
VPATH = $(foreach DIR, $(SOURCEDIRS), $(strip $(DIR)):)

# Build rules
$(OUTDIR)/$(LIBNAME).a: $(OBJS) $(ASMOBJS)

$(BUILDDIR)/%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<
	$(AR) $(OUTDIR)/$(LIBNAME).a $@

$(BUILDDIR)/asm/%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<
	$(AR) $(OUTDIR)/$(LIBNAME).a $@

$(OBJS) $(ASMOBJS): | $(BUILDDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(BUILDDIR): | $(OUTDIR)
	$(MKDIR) $(BUILDDIR)
	$(MKDIR) $(BUILDDIR)/asm

.PHONY: all clean

all: $(OUTDIR)/$(LIBNAME).a | $(OUTDIR) $(BUILDDIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(ASMOBJS)
	$(RM) $(OUTDIR)/$(LIBNAME).a
