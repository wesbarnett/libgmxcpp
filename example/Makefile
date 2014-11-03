CPP=g++
LIBS=-lgmxcpp -lxdrfile
#CFLAGS=-I/usr/local/include/xdrfile
TARGET=example

OBJ=$(patsubst %.cpp, %.o, $(wildcard *.cpp))

default: $(TARGET)

all: default

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $< 

$(TARGET): $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -rfv $(TARGET)
	rm -rfv *.o

.PHONY: clean default install
.PRECIOUS: $(OBJECTS) $(LIBFILES)
