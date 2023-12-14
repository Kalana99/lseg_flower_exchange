# Makefile

CXX = g++
CXXFLAGS = -std=c++17
SRC_DIR = src
INC_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
EXEC = lseg

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c -o $@ $<

clean:
	rm -f $(EXEC) $(OBJS)
