#
# Instituto Tecnologico de Costa Rica
# Escuela de Ingenieria en Computacion
# Sistemas Operativos
#
# Segundo proyecto de Sistemas Operativos
# Ronald Esquivel Lopez
# Ricardo Murillo Jimenez
# Dylan Gonzalez
#
# Programa: MAKEFILE proyecto
# Archivo:  makefile
#
OBJECTS=scheduler.o corrutinas.o
OUTPUT=scheduler

CFLAGS=-I/usr/local/Mesa-3.4/include
#LDLIBS=-lX11 -lglut -lMesaGLU -lMesaGL -lm -lXext -lXmu
LDLIBS=-lX11 -lglut -lGLU -lGL -lrt -lm -lXext
LDFLAGS=-L/usr/local/Mesa-3.4/lib -L/usr/X11R6/lib

$(OUTPUT): $(OBJECTS)
	cc $(OBJECTS) -o $(OUTPUT) $(LDLIBS)

#$(CFLAGS) $(LDFLAGS)
$(OBJECTS):scheduler.h corrutinas.h

clean:
	rm -f *.o
	rm -f scheduler

