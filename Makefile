CCX = g++
CFLAGS = -Wall -g

CPP_SOURCES = $(wildcard *.cpp)
CPP_OBJECTS = $(patsubst %.cpp,%.o,$(CPP_SOURCES))


LDFLAGS = -L.
LDLIBS = -lm 
INC = -I.
SDL_FLAGS = `sdl2-config --cflags --libs`


EXECUTABLE = main

$(EXECUTABLE) : $(CPP_OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(SDL_FLAGS) $(LDLIBS) -o $(EXECUTABLE) $(CPP_OBJECTS)

$(CPP_OBJECTS) : %.o : %.cpp
	$(CXX) $(INC) $(CFLAGS) $(SDL_FLAGS) -c $^ -o $@

clean:
	rm -f *o $(EXECUTABLE)
