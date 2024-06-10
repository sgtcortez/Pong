CXX=clang++

# User defined variables. 
# Example: make OTHER_FLAGS="-g -DDEBUG=1"
OTHER_FLAGS=-g

CXXFLAGS=-std=c++11 ${OTHER_FLAGS} -Iinclude

DEPS=\
	source/controller/GameController.o   \
	source/controller/PhysicController.o \
	source/object/AIPaddle.o 			 \
	source/object/Ball.o 				 \
	source/object/Paddle.o  		     \
	source/object/Score.o				 \
	source/object/UserPaddle.o 			 \
	source/object/VisibleWall.o          \
	source/object/Wall.o  	             \
	source/shape/CircleShape.o           \
	source/shape/RectangleShape.o        \

LINKS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: game

game: main.cpp $(DEPS) 
	$(CXX) -o $@ $< $(LINKS) $(CXXFLAGS) $(DEPS)

.PHONY: clean

clean:
	find . -name '*.o' -delete  