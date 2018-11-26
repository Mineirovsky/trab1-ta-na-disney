CC=gcc

IDIR=../include
ODIR=../obj

CFLAGS=-I$(IDIR) -std=c11 -g

LIBS=-lm

# Todos os cabeçalhos da pasta include devem estar listados aqui
_DEPS = trab1.h distancia.h csv.h knn.h knn_dataset.h knn_batch.h confusion_matrix.h config_file.h result.h
DEPS = $(addprefix $(IDIR)/,$(_DEPS))

# Todos os objetos correspondentes a cada arquivo .c devem estar listados aqui
_OBJ = trab1.o distancia.o csv.o knn.o knn_dataset.o knn_batch.o confusion_matrix.o config_file.o result.o
OBJ = $(addprefix $(ODIR)/,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trab: $(OBJ)
	@echo $(OBJ)
	$(CC) -o ../$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
