#  2014 (C) James W. Barnett

LIBNAME=libgmxcpp.a

ODIR=obj
IDIR=../include
LDIR=../lib

CPP=g++
LIBS=-lxdrfile
CFLAGS=-L/usr/local/lib -I/usr/local/include/xdrfile -I$(IDIR)

_DEPS=CommandLine.h Utils.h Trajectory.h Frame.h Index.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=CommandLine.o Utils.o Trajectory.o Frame.o Index.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

default: $(OBJ)
	ar cr ../$(LIBNAME) $(ODIR)/*.o
	chmod +x ../$(LIBNAME)

all: default

$(ODIR)/%.o: %.cpp $(DEPS)
	mkdir -p obj
	$(CPP) -c -o $@ $< $(CFLAGS) $(LIBS)

install:
	cp -v ../$(LIBNAME) /usr/local/lib/
	cp -v $(IDIR)/*.h /usr/local/include/

clean:
	rm -rfv $(ODIR)
	rm -rfv ../$(LIBNAME)

.PHONY: clean default install
.PRECIOUS: $(OBJECTS) $(LIBFILES)
