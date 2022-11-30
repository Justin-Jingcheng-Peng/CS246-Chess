CXX=g++
CXXFLAGS=-std=c++14 -Wall -g -MMD
OBJECTS=main.o chessBoard.o pawn.o position.o piece.o queen.o bishop.o rook.o king.o knight.o
EXEC=main

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}


.PHONY: clean

clean :
	rm ${OBJECTS} ${EXEC} *.d

## Makefile for one simple C++ file
# CXX=g++
# CXXFLAGS=-std=c++14 -Wall -g -MMD
# OBJECTS=main.o 
# EXEC=main

# ${EXEC}: ${OBJECTS}
# 	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
