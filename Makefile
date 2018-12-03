CC = g++

BDIR = bin
IDIR = include
LDIR = lib
ODIR = obj
SDIR = src
TDIR = test

CFLAGS = -Iglm-0.9.7.1 -I$(IDIR) -g -std=c++14 -Wall -Werror
LDFLAGS = -L$(LDIR) -lfreeimage

_DEPS = FreeImage.h Sampler.h Camera.h Sphere.h Triangle.h Raytracer.h Film.h Parser.h Scene.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

BIN = $(BDIR)/main
TBIN = $(BDIR)/test

all: $(TBIN) $(BIN)

$(TBIN): $(TDIR)/Raytrace.t.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) -lgtest -lgtest_main

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -fr $(BDIR)/test.dSYM
	rm -f $(ODIR)/* $(BDIR)/*
