CC=gcc
CFLAGS=-O2 -fPIC -Wno-unused-result
CFLAGSSO=-shared
LFLAGS=-lm
TAYLOR=taylor
all: lib.so

lib.so: src/wrapper-rpb_sun_earth.o src/taylor-rpb_sun_earth.o
	$(CC) $(CFLAGS) $(CFLAGSSO) src/wrapper-rpb_sun_earth.o src/taylor-rpb_sun_earth.o -o lib.so $(LFLAGS)

src/wrapper-rpb_sun_earth.o: src/wrapper-rpb_sun_earth.c src/wrapper-rpb_sun_earth.h src/taylor-rpb_sun_earth.c src/taylor-rpb_sun_earth.h
	$(CC) $(CFLAGS) -c src/wrapper-rpb_sun_earth.c -o src/wrapper-rpb_sun_earth.o

src/taylor-rpb_sun_earth.o: src/taylor-rpb_sun_earth.c src/taylor-rpb_sun_earth.h
	$(CC) $(CFLAGS) -c src/taylor-rpb_sun_earth.c -o src/taylor-rpb_sun_earth.o $(LFLAGS)

src/taylor-rpb_sun_earth.c: rpb_sun_earth.eqs
	$(TAYLOR) -name auto -headername taylor-rpb_sun_earth.h -o src/taylor-rpb_sun_earth.c -jet -step -jlib jet_1 -jet_helper rpb_sun_earth.eqs

src/taylor-rpb_sun_earth.h: rpb_sun_earth.eqs
	$(TAYLOR) -name auto -o src/taylor-rpb_sun_earth.h -jlib jet_1 -header rpb_sun_earth.eqs

clean:
	rm lib.so src/taylor-* src/*.o
