# Makefile for N-Body Simulation
# Eamon Lightning

GXX = g++
GXXFLAGS = -Wall -Werror -ansi -pedantic

all: NBody

NBody: NBody_app.o NBody_implementation.o
	$(GXX) NBody_app.o NBody_implementation.o -o NBody -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
  
NBody_app.o: NBody_app.cpp NBody.hpp
	$(GXX) -c NBody_app.cpp $(GXXFLAGS)

NBody_implementation.o: NBody_implementation.cpp NBody.hpp 
	$(GXX) -c NBody_implementation.cpp $(GXXFLAGS) 

clean:
	rm *.o *~ NBody