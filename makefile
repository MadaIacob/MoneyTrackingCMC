CPP=g++

CPPFLAGS=-Wall -Iinc

GTEST_DIR=c:\gtest-1.7.0

GTEST_LIB=$(GTEST_DIR)\make\gtest_main.a

GTEST_INC=-isystem $(GTEST_DIR)\include

OBJECTS=\
	src\game.o

HEADERS=\
	inc\TicTacToe.h \
	inc\TicTacToeTypes.h

TESTS=\
	tst\test.o
	
LIBS=\
	lib\TicTacToe.a

# build all
all: game.exe test.exe

game.exe: $(OBJECTS) $(LIBS)
	$(CPP) -o game.exe $(OBJECTS) $(LIBS)

test.exe: $(LIBS) $(TESTS) $(GTEST_LIB)
	$(CPP) -o test.exe $(TESTS) $(LIBS) $(GTEST_LIB)	

src\game.o: src\game.cpp $(HEADERS)
	$(CPP) $(CPPFLAGS) -o src\game.o -c src\game.cpp

tst\test.o: tst\test.cpp
	$(CPP) $(CPPFLAGS) $(GTEST_INC) -o tst\test.o -c tst\test.cpp	

# play the game
play: game.exe
	cls
	game.exe

# run tests
test: test.exe
	cls
	test.exe

# clean up
clean:
	del $(OBJECTS)
	del $(TESTS)
	del game.exe
	del test.exe
