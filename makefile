CC=gcc
CFLAGS=-c
LDFLAGS=-lpthread
SOURCES=ini.c shell.c parse_config.c server.c serial.c kt15.c main.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=badger

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS)  $< -o $@

clean:
	rm $(EXECUTABLE) $(OBJECTS)