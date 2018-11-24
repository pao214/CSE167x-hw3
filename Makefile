CC = g++

BDIR = bin
IDIR = include
LDIR = lib
ODIR = obj
SDIR = src
TDIR = test

CFLAGS = -I$(IDIR) -g -std=c++14 -Wall -Werror
LDFLAGS = -L$(LDIR) -lfreeimage

_DEPS = FreeImage.h Vector.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

BIN = $(BDIR)/main
TBIN = $(BDIR)/test

all: $(BIN) $(TBIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(TBIN): $(TDIR)/Raytrace.t.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -lgtest -lgtest_main

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/* $(BDIR)/*
