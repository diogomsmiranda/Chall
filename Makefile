CFLAGS = -O3 -std=c++11 -Wall
TARGET = chall
AUXILIARY = chall_aux
STRUCTS = chall_structs


$(TARGET).o: $(TARGET).cpp $(AUXILIARY).cpp $(STRUCTS).hpp

all: $(TARGET).o
	g++ -o $(TARGET) $(TARGET).o

clear:
	rm -f $(TARGET).o