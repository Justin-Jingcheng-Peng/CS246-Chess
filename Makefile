CXX=g++
CXXFLAGS=-std=c++14 -g -Werror=vla -Wall -MMD
OBJECTS=main.o chessBoard.o position.o piece.o queen.o bishop.o rook.o king.o knight.o pawn.o move.o chessController.o chessView.o computerPlayer.o levelOne.o levelTwo.o levelThree.o levelFour.o observer.o textObserver.o graphicsObserver.o subject.o window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean :
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
