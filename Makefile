C++ = g++
OBJS = main.o Puzzle.o Part.o
EXEC = ex1_run

COMP_FLAG = -std=c++11 -Wall -Wextra \
	    -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
		$(C++) $(OBJS) -o $@
main.o: main.cpp Puzzle.h
		$(C++) $(COMP_FLAG) -c $*.cpp
Puzzle.o: Puzzle.h Puzzle.cpp Part.h
		$(C++) $(COMP_FLAG) -c $*.cpp
Part.o: Part.h Part.cpp
		$(C++) $(COMP_FLAG) -c $*.cpp

clean:
		rm -f $(OBJS) $(EXEC)
