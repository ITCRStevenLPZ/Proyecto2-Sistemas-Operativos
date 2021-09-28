#Proyecto2 SO (Ronald Esquivel, Ricardo Murillo y Dylan Gonzalez)
OBJECTS=corrutinas.o
OUTPUT=corrutinas

#CFLAGS=-I/usr/local/Mesa-3.4/include
LDLIBS=-lrt -lm
#LDFLAGS=-L/usr/local/Mesa-3.4/lib -L/usr/X11R6/lib

$(OUTPUT): $(OBJECTS)
	cc $(OBJECTS) -o $(OUTPUT)  $(LDLIBS)

#$(CFLAGS) $(LDFLAGS)
$(OBJECTS):corrutinas.h

clean:
	rm -f *.o
	rm -f corrutinas

#LDLIBS=-lX11 -lglut -lGLU -lGL -lm -lXext -lpthread -lrt