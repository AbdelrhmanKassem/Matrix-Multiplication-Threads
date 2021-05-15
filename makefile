IDIR = headers
CC=gcc
CFLAGS=-pthread
TARGET = matmult.out
ODIR= obj
LIBS= -lpthread

_DEPS = first_method.h second_method.h third_method.h read_files.h write_output.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = first_method.o second_method.o third_method.o read_files.o write_output.o matMultp.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -f $(TARGET)
