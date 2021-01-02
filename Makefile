CFLAGS  = `fltk-config --cxxflags`
LFLAGS   = `fltk-config --ldflags`

default: build

build: pow.o
	g++ pow.o -o pow -std=c++0x ${LFLAGS}

pow.o:
	g++ -std=c++0x ${CFLAGS} -c pow.c

clean:
	rm -f pow.o

install:
	chmod 775 pow
	cp pow /usr/local/bin

uninstall:
	rm -f /usr/local/bin/pow
