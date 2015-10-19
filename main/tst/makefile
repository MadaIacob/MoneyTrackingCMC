CPP = g++

AR = ar crf

CPP_FLAGS = -Wall
INC_FLAG = -I..\inc

GTEST_DIR = C:\gtest-1.7.0
GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a
GTEST_INC = -isystem $(GTEST_DIR)\include

HEADERS = \
	..\inc\CommandInterpreter.h \
	..\inc\PrintMessage.h \
	..\inc\WalletEntity.h \
	..\inc\HelperFunctions.h

TESTS = \
	CreateWalletTest.o \
	TestCommand.o \
	CreateWalletTestHelper.o \
	HelperFunctionsTest.o \
	ConfigurationFileTest.o

LIB_OBJ = ..\lib\WalletLib.a
	
TEST_HELPER_H = CreateWalletTestHelper.h

all: ..\..\test.exe ..\lib\TestLib.a

#for tests execution
..\lib\TestLib.a: $(TESTS)
	$(AR) ..\lib\TestLib.a $(TESTS)	

CreateWalletTest.o: CreateWalletTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o CreateWalletTest.o -c CreateWalletTest.cpp

CreateWalletTestHelper.o: CreateWalletTestHelper.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o CreateWalletTestHelper.o -c CreateWalletTestHelper.cpp
	
TestCommand.o: TestCommand.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o TestCommand.o -c TestCommand.cpp

HelperFunctionsTest.o: HelperFunctionsTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o HelperFunctionsTest.o -c HelperFunctionsTest.cpp

ConfigurationFileTest.o: ConfigurationFileTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o ConfigurationFileTest.o -c ConfigurationFileTest.cpp
	
..\..\test.exe: $(LIB_OBJ) $(TESTS) $(GTEST_LIB)
	$(CPP) -o ..\..\test.exe $(TESTS) $(LIB_OBJ) $(GTEST_LIB)
	
# clean up
clean:
	rm $(TESTS)
	rm ..\lib\TestLib.a

