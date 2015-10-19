CPP = g++

AR = ar crf

INC_FLAG = -I..\inc

CPP_FLAGS = -Wall

GTEST_DIR = C:\gtest-1.7.0

GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a

GTEST_INC = -isystem $(GTEST_DIR)\include

HEADERS = \
	..\inc\CommandInterpreter.h \
	..\inc\PrintMessage.h \
	..\inc\WalletEntity.h \
	..\inc\HelperFunctions.h
	
OBJECTS = \
	CommandInterpreter.o \
	PrintMessage.o \
	WalletEntity.o \
	HelperFunctions.o

WALLET_LIB = ..\lib\WalletLib.a

all: ..\lib\WalletLib.a WalletMain.o
	
# for wallet execution
..\lib\WalletLib.a: $(OBJECTS)
	$(AR) ..\lib\WalletLib.a $(OBJECTS)

CommandInterpreter.o: CommandInterpreter.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o CommandInterpreter.o -c CommandInterpreter.cpp
	
PrintMessage.o: PrintMessage.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o PrintMessage.o -c PrintMessage.cpp
	
WalletEntity.o: WalletEntity.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o WalletEntity.o -c WalletEntity.cpp
	
WalletMain.o: main.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o WalletMain.o -c main.cpp
	
HelperFunctions.o: HelperFunctions.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o HelperFunctions.o -c HelperFunctions.cpp
	
# clean up
clean:
	rm $(OBJECTS)
	rm ../lib/WalletLib.a
	rm WalletMain.o
