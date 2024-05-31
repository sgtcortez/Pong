CXX=clang++

# User defined variables. 
# Example: make OTHER_FLAGS="-g -DDEBUG=1"
OTHER_FLAGS=

CXXFLAGS=-std=c++11 ${OTHER_FLAGS} -Iinclude

DEPS=\
	source/Paddle.o \
	source/Ball.o   \
	source/Wall.o   \
	source/Game.o   \

LINKS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: game

game: main.cpp $(DEPS) 
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

.PHONY: clean

clean:
	rm -rf *.o *.so *.out game source/*.o