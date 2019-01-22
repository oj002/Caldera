# Caldera game engine
.POSIX:

include config.mk

SRC = $(shell find Caldera/ -name '*.c')
OBJ = $(SRC:.c=.o)
OLD_LLP = $(LD_LIBRARY_PATH)

options:
	@echo "Caldera $(VERSION) build options:"
	@echo "CFLAGS  = $(STCFLAGS)"
	@echo "LDFLAGS = $(STLDFLAGS)"
	@echo "CC      = $(CC)"

run:
	make -s clean all exec

debug:
	make -s clean all gdb

exec:
	export LD_LIBRARY_PATH=build/Caldera/:$LD_LIBRARY_PATH; \
	./a.out $(ARGS) \
	export LD_LIBRARY_PATH=$$OLD_LLP;

gdb:
	export LD_LIBRARY_PATH=build/Caldera/:$LD_LIBRARY_PATH; \
	gdb ./a.out $(ARGS) \
	export LD_LIBRARY_PATH=$$OLD_LLP;


all:
	make build/Caldera build/Sandbox

build/Caldera:
	mkdir build/Caldera
	cd Caldera/; \
	$(CC) $(STLDFLAGS) -fPIC -c `find . -name '*.c'` -I./; \
	cd -; \
	mv `find Caldera/ -name '*.o'` build/Caldera/; \
	$(CC) $(STLDFLAGS) -shared -o build/Caldera/libCaldera.so \
		`find ./build/Caldera/ -name '*.o'`;

build/Sandbox:
	mkdir build/Sandbox/
	$(CC) $(STLDFLAGS) -Lbuild/Caldera -I Caldera/ \
		`find Sandbox -name '*.c'` -lCaldera;

clean:
	rm -rf build/Caldera/
	rm -rf build/Sandbox/
	rm -f a.out

.PHONY: options run exec all install clean debug gdb #uninstall
