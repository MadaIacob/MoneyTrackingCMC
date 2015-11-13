CPP = g++

AR = ar crf

CPP_FLAGS = -Wall
INC_FLAG = -I..\inc

GTEST_DIR = C:\gtest-1.7.0
GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a
GTEST_INC = -isystem $(GTEST_DIR)\include

HEADERS = \
	..\inc\Wallet.h \
	..\inc\WalletEntity.h \
	..\inc\Command.h \
	..\inc\CreateWalletCmd.h \
	..\inc\MessageHandler.h \
	..\inc\MessageCodes_E.h \
	TestHelper.h \
	..\inc\Config.h \
	..\inc\HelperFunctions.h \
	..\inc\ConfigCmd.h \
	..\inc\TransactionCmd.h


TESTS = \
	WalletTest.o \
	CreateWalletCmdTest.o \
	TestHelper.o \
	ConfigClasTest.o \
	HelperFunctionsTest.o \
	ConfigCmdTest.o \
	TransactionsCmdTest.o

LIB_OBJ = ..\lib\WalletLib.a

all: ..\..\test.exe ..\lib\TestLib.a

#for tests execution
..\lib\TestLib.a: $(TESTS)
	$(AR) ..\lib\TestLib.a $(TESTS)

TestHelper.o: TestHelper.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o TestHelper.o -c TestHelper.cpp

WalletTest.o: WalletTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o WalletTest.o -c WalletTest.cpp

CreateWalletCmdTest.o: CreateWalletCmdTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o CreateWalletCmdTest.o -c CreateWalletCmdTest.cpp

ConfigClasTest.o: ConfigClasTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o ConfigClasTest.o -c ConfigClasTest.cpp

HelperFunctionsTest.o: HelperFunctionsTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o HelperFunctionsTest.o -c HelperFunctionsTest.cpp

ConfigCmdTest.o: ConfigCmdTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o ConfigCmdTest.o -c ConfigCmdTest.cpp

TransactionsCmdTest.o: TransactionsCmdTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o TransactionsCmdTest.o -c TransactionsCmdTest.cpp

..\..\test.exe: $(LIB_OBJ) $(TESTS) $(GTEST_LIB)
	$(CPP) -o ..\..\test.exe $(TESTS) $(LIB_OBJ) $(GTEST_LIB)

# clean up
clean:
	rm $(TESTS)
	rm ../lib/TestLib.a
