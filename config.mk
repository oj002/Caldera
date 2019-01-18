# Caldera version
VERSION = 0.0.0

#======================================#
#  Customize below to fit your system  #
#======================================#

# paths
PREFIX = /usr/

# includes and libs
INCS = -I. -I/usr/include
LIBS = -L/usr/lib -lm -lglfw

# flags
CFLAGS = -g
CPPFLAGS = -DVERSION=\"$(VERSION)\"
STCFLAGS = $(INCS) $(CPPFLAGS) $(CFLAGS)
STLDFLAGS = $(LIBS) $(LDFLAGS)

# compiler and linker
CC = gcc
