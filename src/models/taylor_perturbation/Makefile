CC=gcc
CFLAGS=-O2 -fPIC -Wno-unused-result
CFLAGSSO=-shared
LFLAGS=-lm
TAYLOR=taylor
all: lib.so

lib.so: src/wrapper-perturbation.o src/taylor-perturbation.o
	$(CC) $(CFLAGS) $(CFLAGSSO) src/wrapper-perturbation.o src/taylor-perturbation.o -o lib.so $(LFLAGS)

src/wrapper-perturbation.o: src/wrapper-perturbation.c src/wrapper-perturbation.h src/taylor-perturbation.c src/taylor-perturbation.h
	$(CC) $(CFLAGS) -c src/wrapper-perturbation.c -o src/wrapper-perturbation.o

src/taylor-perturbation.o: src/taylor-perturbation.c src/taylor-perturbation.h
	$(CC) $(CFLAGS) -c src/taylor-perturbation.c -o src/taylor-perturbation.o $(LFLAGS)

src/taylor-perturbation.c: perturbation.eq
	$(TAYLOR) -name auto -headername taylor-perturbation.h -o src/taylor-perturbation.c -jet -step  -jet_helper perturbation.eq

src/taylor-perturbation.h: perturbation.eq
	$(TAYLOR) -name auto -o src/taylor-perturbation.h  -header perturbation.eq

clean:
	rm lib.so src/taylor-* src/*.o
