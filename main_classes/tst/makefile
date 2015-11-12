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
	..\inc\MessageHandler.h

TESTS = \
	WalletTest.o \
	CreateWalletCmdTest.o


LIB_OBJ = ..\lib\WalletLib.a

all: ..\..\test.exe ..\lib\TestLib.a

#for tests execution
..\lib\TestLib.a: $(TESTS)
	$(AR) ..\lib\TestLib.a $(TESTS)

WalletTest.o: WalletTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o WalletTest.o -c WalletTest.cpp

CreateWalletCmdTest.o: CreateWalletCmdTest.cpp $(TEST_HELPER_H)
	$(CPP) $(CPP_FLAGS) $(GTEST_INC) $(INC_FLAG) -o CreateWalletCmdTest.o -c CreateWalletCmdTest.cpp


..\..\test.exe: $(LIB_OBJ) $(TESTS) $(GTEST_LIB)
	$(CPP) -o ..\..\test.exe $(TESTS) $(LIB_OBJ) $(GTEST_LIB)

# clean up
clean:
	rm $(TESTS)
	rm ../lib/TestLib.a
