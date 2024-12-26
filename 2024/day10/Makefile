CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Dynamically find all source files
SRCS = $(wildcard *.cpp)
HDRS = $(wildcard *.hpp)
OBJS = $(SRCS:.cpp=.o)

# Get the current directory name and use it for the executable
EXEC_NAME = $(notdir $(CURDIR)).out

# Default target
all: $(EXEC_NAME)

# Linking the target executable
$(EXEC_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compiling source files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(EXEC_NAME)

# Phony targets
.PHONY: all clean