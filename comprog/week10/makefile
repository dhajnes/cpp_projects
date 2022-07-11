# the compiler: gcc for C program, define as g++ for C++
CC = g++ -x c++ -std=gnu++17

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
DEBUG_FLAGS  = -g -Wall -Wextra -fsanitize=undefined,address -D_GLIBCXX_DEBUG -O2
JUDGE_FLAGS  = -Wall -O2 -static -pipe

# The build target 
TARGET = pathcounter

all:
			$(CC) $(JUDGE_FLAGS) -o $(TARGET) $(TARGET).cpp

debug:
			$(CC) $(DEBUG_FLAGS) -o $(TARGET) $(TARGET).cpp

clean:
			$(RM) $(TARGET)