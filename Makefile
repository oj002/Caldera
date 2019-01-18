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
	make -s clean all exec #&& ./a.out $(ARGS)

exec:
	export LD_LIBRARY_PATH=build/Caldera/:$LD_LIBRARY_PATH; \
	./a.out $(ARGS) \
	export LD_LIBRARY_PATH=$$OLD_LLP;


all:
	make build/Caldera build/Sandbox

build/Caldera:
	mkdir build/Caldera
	cd Caldera/; \
	$(CC) $(STCFLAGS) -fPIC -c `find . -name '*.c'` -I .; \
	cd -; \
	mv `find Caldera/ -name '*.o'` build/Caldera/; \
	$(CC) $(STCFLAGS) -shared -o build/Caldera/libCaldera.so \
		`find ./build/Caldera/ -name '*.o'`;

build/Sandbox:
	mkdir build/Sandbox/
	$(CC) $(STCFLAGS) -Lbuild/Caldera -I Caldera/ \
		`find Sandbox -name '*.c'` -lCaldera;

clean:
	rm -rf build/Caldera/
	rm -rf build/Sandbox/
	rm -f a.out

.PHONY: options run exec all install clean #uninstall
