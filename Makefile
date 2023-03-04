CFLAGS = -O3 -std=c++11 -Wall
TARGET = chall
AUXILIARY = chall_aux
STRUCTS = chall_structs


$(TARGET).o: $(TARGET).cpp $(AUXILIARY).cpp $(STRUCTS).hpp

all: $(TARGET).o
	g++ $(TARGET).o -o $(TARGET)

clear:
	rm -f $(TARGET).o