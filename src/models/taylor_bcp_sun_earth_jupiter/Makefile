CC=gcc
CFLAGS=-O2 -fPIC -Wno-unused-result
CFLAGSSO=-shared
LFLAGS=-lm
TAYLOR=taylor
all: lib.so

lib.so: src/wrapper-bcp_sun_earth_jupiter.o src/taylor-bcp_sun_earth_jupiter.o
	$(CC) $(CFLAGS) $(CFLAGSSO) src/wrapper-bcp_sun_earth_jupiter.o src/taylor-bcp_sun_earth_jupiter.o -o lib.so $(LFLAGS)

src/wrapper-bcp_sun_earth_jupiter.o: src/wrapper-bcp_sun_earth_jupiter.c src/wrapper-bcp_sun_earth_jupiter.h src/taylor-bcp_sun_earth_jupiter.c src/taylor-bcp_sun_earth_jupiter.h
	$(CC) $(CFLAGS) -c src/wrapper-bcp_sun_earth_jupiter.c -o src/wrapper-bcp_sun_earth_jupiter.o

src/taylor-bcp_sun_earth_jupiter.o: src/taylor-bcp_sun_earth_jupiter.c src/taylor-bcp_sun_earth_jupiter.h
	$(CC) $(CFLAGS) -c src/taylor-bcp_sun_earth_jupiter.c -o src/taylor-bcp_sun_earth_jupiter.o $(LFLAGS)

src/taylor-bcp_sun_earth_jupiter.c: bcp_sun_earth_jupiter.eqs
	$(TAYLOR) -name auto -headername taylor-bcp_sun_earth_jupiter.h -o src/taylor-bcp_sun_earth_jupiter.c -jet -step -jlib jet_1 -jet_helper bcp_sun_earth_jupiter.eqs

src/taylor-bcp_sun_earth_jupiter.h: bcp_sun_earth_jupiter.eqs
	$(TAYLOR) -name auto -o src/taylor-bcp_sun_earth_jupiter.h -jlib jet_1 -header bcp_sun_earth_jupiter.eqs

clean:
	rm lib.so src/taylor-* src/*.o
