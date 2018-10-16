FILE = $(wildcard *.cpp)
CXX = g++
CXX_FLAGS = -w -std=c++11#-c -Wall -Werror -pedantic-errors
TARGET = $(patsubst %.cpp,%,$(FILE))
OBJS = $(wildcard *.o)
DEPS = $(wildcard *.h)

%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXX_FLAGS)
all: $(OBJS)
	$(CXX) $(FILE) $(CXX_FLAGS) -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
