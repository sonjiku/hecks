OUTDIR=../Bins
IDIR=include
ODIR=obj
LDIR=lib

_DEP= fileops.h util.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))
_OBJ=hecks.o hecksops.o util.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

CC=gcc
CFLAGS=-I$(IDIR)
LIBS=

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

$(OUTDIR)/hecks: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
