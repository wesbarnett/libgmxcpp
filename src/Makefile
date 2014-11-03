#  2014 (C) James W. Barnett

# Installation directories
LIBDIR=/usr/local/lib
INCDIR=/usr/local/include
XDRFILELOC=/usr/local/include/xdrfile

LIBNAME=libgmxcpp.a
ODIR=obj
IDIR=../include
LDIR=../lib

CPP=g++
LIBS=-lxdrfile
CFLAGS=-I$(XDRFILELOC) -I$(IDIR)

_DEPS=CommandLine.h Utils.h Trajectory.h Frame.h Index.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=CommandLine.o Utils.o Trajectory.o Frame.o Index.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

default: $(OBJ)
	ar cr ../$(LIBNAME) $(ODIR)/*.o
	chmod +x ../$(LIBNAME)
	@echo "Now run 'make install' to install to $(LIBDIR) and $(INCDIR)"

all: default

$(ODIR)/%.o: %.cpp $(DEPS)
	mkdir -p obj
	$(CPP) -c -o $@ $< $(CFLAGS) $(LIBS)

install:
	cp -v ../$(LIBNAME) $(LIBDIR)
	cp -v $(IDIR)/*.h $(INCDIR)

clean:
	rm -rfv $(ODIR)
	rm -rfv ../$(LIBNAME)

.PHONY: clean default install
.PRECIOUS: $(OBJECTS) $(LIBFILES)
