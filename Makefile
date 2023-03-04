CFLAGS = -O3 -std=c++11 -Wall
TARGET = chall
AUXILIARY = chall_aux
STRUCTS = chall_structs
TEXT = chall_text
OBJ = $(TARGET).o $(AUXILIARY).o

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(CFLAGS) $(OBJ) -o $(TARGET)

$(TARGET).o: $(TARGET).cpp $(STRUCTS).hpp $(TEXT).hpp
	g++ $(CFLAGS) -c $(TARGET).cpp -o $(TARGET).o

$(AUXILIARY).o: $(AUXILIARY).cpp $(STRUCTS).hpp
	g++ $(CFLAGS) -c $(AUXILIARY).cpp -o $(AUXILIARY).o

clear:
	rm -f $(TARGET) $(OBJ)
