# About _mbed-lib_ #

The _mbed-lib_ project provides development libraries for the mbed (http://mbed.org). In particular, it provides a C-library _libmbed_, which can be used in _gcc_ based toolchains for _mbed_ development: _libmbed_ provides the LPC17xx CMSIS Library interface and a custom interface to the _mbed_ hardware.

# Functionality #

The _mbed-lib_ project provides two main features:
  * Makefiles and patches for the [CMSIS 2.0](http://ics.nxp.com/support/documents/microcontrollers/?search=LPC176x+CMSIS) library for the LPC1768, the core component of the _mbed_;
  * Easy to use interfaces for the _mbed_ specific hardware, such as the USB interface, the CAN bus, etc.

In addition, examples are provided to learn how the interface works. Also, a compilation of useful documentation material is provided.

# Requirements #

To use the CMSIS libraries, you need the _mbed_ device with the LPC1768 microprocessor. The version with the LPC2378 is not suitable. Furthermore, you need a _gcc_ based toolchain for the ARM processors. I recommend the [toolchain build provided by James Snyder](https://github.com/jsnyder/arm-eabi-toolchain).

# Related Projects #

More information about cross-compiling for the mbed can be found in [this tutorial](http://dev.frozeneskimo.com/notes/compiling_your_own_cmsis_code_for_the_mbed) and on [this page](http://www-users.cs.york.ac.uk/~pcc/MCP/index.html).

If you like to use Eclipse, take a look [here](http://mbed.org/cookbook/Using-mbed-with-gcc-and-eclipse?action=view&revision=2118).