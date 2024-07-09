CC=gcc
CFLAGS=-O2 -fPIC -Wno-unused-result
CFLAGSSO=-shared
LFLAGS=-lm
TAYLOR=taylor
all: lib.so

lib.so: src/wrapper-rpb_SE_nojet.o src/taylor-rpb_SE_nojet.o
	$(CC) $(CFLAGS) $(CFLAGSSO) src/wrapper-rpb_SE_nojet.o src/taylor-rpb_SE_nojet.o -o lib.so $(LFLAGS)

src/wrapper-rpb_SE_nojet.o: src/wrapper-rpb_SE_nojet.c src/wrapper-rpb_SE_nojet.h src/taylor-rpb_SE_nojet.c src/taylor-rpb_SE_nojet.h
	$(CC) $(CFLAGS) -c src/wrapper-rpb_SE_nojet.c -o src/wrapper-rpb_SE_nojet.o

src/taylor-rpb_SE_nojet.o: src/taylor-rpb_SE_nojet.c src/taylor-rpb_SE_nojet.h
	$(CC) $(CFLAGS) -c src/taylor-rpb_SE_nojet.c -o src/taylor-rpb_SE_nojet.o $(LFLAGS)

src/taylor-rpb_SE_nojet.c: rpb_SE_nojet.eqs
	$(TAYLOR) -name auto -headername taylor-rpb_SE_nojet.h -o src/taylor-rpb_SE_nojet.c -jet -step  -jet_helper rpb_SE_nojet.eqs

src/taylor-rpb_SE_nojet.h: rpb_SE_nojet.eqs
	$(TAYLOR) -name auto -o src/taylor-rpb_SE_nojet.h  -header rpb_SE_nojet.eqs

clean:
	rm lib.so src/taylor-* src/*.o
