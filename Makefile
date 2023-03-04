CFLAGS = -O3 -std=c++11 -Wall
TARGET = chall
AUXILIARY = chall_aux
STRUCTS = chall_structs
ALL = $(TARGET).cpp $(AUXILIARY).cpp $(STRUCTS).hpp

all:
	g++ $(CFLAGS) $(ALL) -o $(TARGET)

clear:
	rm -f $(TARGET)