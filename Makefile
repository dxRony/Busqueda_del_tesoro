TARGET=ejecutable/busquedaDelTesoro

SRCS=$(wildcard src/*.cpp)

OBJS=$(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	 g++ -o $(TARGET) $(OBJS)

%.o: %.cpp
	 g++ -c $< -o $@

# Limpiar archivos generados
clean:
	 rm -f src/*.o $(TARGET)