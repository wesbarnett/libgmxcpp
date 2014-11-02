CPP=g++
LIBS=-lgmxcpp -lxdrfile
CFLAGS=-I/usr/local/include/xdrfile
TARGET=example

default: $(TARGET)

all: default

$(TARGET):
	$(CPP) example.cpp -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -rfv example

.PHONY: clean default install
.PRECIOUS: $(OBJECTS) $(LIBFILES)
