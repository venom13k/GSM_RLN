CC = gcc

CFLAGS  = `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs   gtk+-3.0`
#CFLAGS+="-DGDK_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGSEAL_ENABLE"
CFLAGS+=-g
OBJECTS = gsm.o
PROG    = gsm

$(PROG): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	 rm -f *.o $(PROG) 
