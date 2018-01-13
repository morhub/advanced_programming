C++ = g++-5.3.0
OBJS = main.o
EXEC = ex4

COMP_FLAG = -std=c++14 -Wall -Wextra \
	    -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
		$(C++) $(OBJS) -o $@
main.o: main.cpp Puzzle2dPiece.h PuzzlePiece.h Puzzle3dPiece.h DataMap.h \
	 DataBase.h
		$(C++) $(COMP_FLAG) -c $*.cpp

clean:
		rm -f $(OBJS) $(EXEC)
