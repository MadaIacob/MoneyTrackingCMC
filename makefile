CPP = g++

AR = ar crf

INC_FLAG = -Imain\inc

TEST_FLAG = -Imain\tst

CPP_FLAGS = -Wall

GTEST_DIR = C:\gtest-1.7.0

GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a

GTEST_INC = -isystem $(GTEST_DIR)\include

OBJECTS = \
	main\src\WalletMain.o
	
HEADERS = \
	main\inc\CommandInterpreter.h \
	main\inc\PrintMessage.h \
	main\inc\WalletEntity.h

LIBS = \
	main\lib\WalletLib.a
	
LIB_OBJECTS = \
	main\src\CommandInterpreter.o \
	main\src\PrintMessage.o \
	main\src\WalletEntity.o
	
TEST_OBJECTS = \
	main\src\CommandInterpreter.o \
	main\src\PrintMessage.o \
	main\src\WalletEntity.o \
	main\tst\CreateWalletTest.o \
	main\tst\TestCommand.o
	
TEST_HELPER_CPP = \
	main\tst\CreateWalletTestHelper.cpp
	
TEST_HELPER_H =\
	main\tst\CreateWalletTestHelper.h
	
TEST_HELPER_O = \
	main\tst\CreateWalletTestHelper.o
	
# build WalletMain
walletMain: moneytracker.exe

moneytracker: moneytracker.exe

# execute tests 
# must be in different lines!!!
test : WalletTest.exe TestCommand.exe
	WalletTest.exe
	TestCommand.exe
	
# for wallet execution
main\lib\WalletLib.a: $(LIB_OBJECTS)
	$(AR) main\lib\WalletLib.a $(LIB_OBJECTS)

main\src\CommandInterpreter.o: main\src\CommandInterpreter.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o main\src\CommandInterpreter.o -c main\src\CommandInterpreter.cpp
	
main\src\PrintMessage.o: main\src\PrintMessage.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o main\src\PrintMessage.o -c main\src\PrintMessage.cpp
	
main\src\WalletEntity.o: main\src\WalletEntity.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o main\src\WalletEntity.o -c main\src\WalletEntity.cpp
	
main\src\WalletMain.o: main\src\main.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o main\src\WalletMain.o -c main\src\main.cpp
	
moneytracker.exe: $(OBJECTS) $(LIBS) 
	$(CPP) -o moneytracker.exe $(OBJECTS) $(LIBS)
	
#for tests execution
main\tst\CreateWalletTest.o: main\tst\CreateWalletTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o main\tst\CreateWalletTest.o -c main\tst\CreateWalletTest.cpp

WalletTest.exe: $(LIBS) $(TEST_OBJECTS) $(GTEST_LIB)
	$(CPP) -o WalletTest.exe $(TEST_OBJECTS) $(LIBS) $(GTEST_LIB)

main\tst\TestCommand.o: main\tst\TestCommand.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o main\tst\TestCommand.o -c main\tst\TestCommand.cpp

TestCommand.exe: $(LIBS) $(TEST_OBJECTS) $(GTEST_LIB)
	$(CPP) -o TestCommand.exe $(TEST_OBJECTS) $(LIBS) $(GTEST_LIB)


	
# clean up
clean:
	rm $(LIB_OBJECTS)
	rm $(LIBS)
	rm $(OBJECTS)
	rm moneytracker.exe
	rm $(TEST_OBJECTS)
