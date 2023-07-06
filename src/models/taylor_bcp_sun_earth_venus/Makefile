CC=gcc
CFLAGS=-O2 -fPIC -Wno-unused-result
CFLAGSSO=-shared
LFLAGS=-lm
TAYLOR=taylor
all: lib.so

lib.so: src/wrapper-bcp_sun_earth_venus.o src/taylor-bcp_sun_earth_venus.o
	$(CC) $(CFLAGS) $(CFLAGSSO) src/wrapper-bcp_sun_earth_venus.o src/taylor-bcp_sun_earth_venus.o -o lib.so $(LFLAGS)

src/wrapper-bcp_sun_earth_venus.o: src/wrapper-bcp_sun_earth_venus.c src/wrapper-bcp_sun_earth_venus.h src/taylor-bcp_sun_earth_venus.c src/taylor-bcp_sun_earth_venus.h
	$(CC) $(CFLAGS) -c src/wrapper-bcp_sun_earth_venus.c -o src/wrapper-bcp_sun_earth_venus.o

src/taylor-bcp_sun_earth_venus.o: src/taylor-bcp_sun_earth_venus.c src/taylor-bcp_sun_earth_venus.h
	$(CC) $(CFLAGS) -c src/taylor-bcp_sun_earth_venus.c -o src/taylor-bcp_sun_earth_venus.o $(LFLAGS)

src/taylor-bcp_sun_earth_venus.c: bcp_sun_earth_venus.eqs
	$(TAYLOR) -name auto -headername taylor-bcp_sun_earth_venus.h -o src/taylor-bcp_sun_earth_venus.c -jet -step -jlib jet_1 -jet_helper bcp_sun_earth_venus.eqs

src/taylor-bcp_sun_earth_venus.h: bcp_sun_earth_venus.eqs
	$(TAYLOR) -name auto -o src/taylor-bcp_sun_earth_venus.h -jlib jet_1 -header bcp_sun_earth_venus.eqs

clean:
	rm lib.so src/taylor-* src/*.o
