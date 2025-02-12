CXX = g++
CXXFLAGS = -Wall -g
LIBS = -lraylib -lgdi32 -lwinmm

TARGET = main.exe

SRCS = math.cpp snake.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
