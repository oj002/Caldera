# Caldera version
VERSION = 0.0.0

#======================================#
#  Customize below to fit your system  #
#======================================#

# libs
LIBS = -lm -lglfw

# flags
CWARNGING = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith \
			-Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 \
			-Wwrite-strings -Wcast-qual -Wswitch-default -Wswitch-enum \
			-Wconversion -Wunreachable-code -Winit-self
CFLAGS = -g $(CWARNINGS)
CPPFLAGS = -DVERSION=\"$(VERSION)\" -DCA_ENABLE_ASSERTS
STCFLAGS = $(CPPFLAGS) $(CFLAGS)
STLDFLAGS = $(LIBS) $(LDFLAGS)

# compiler and linker
CC = c89
