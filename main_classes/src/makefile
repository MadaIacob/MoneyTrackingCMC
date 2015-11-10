CPP = g++

AR = ar crf

INC_FLAG = -I..\inc

CPP_FLAGS = -Wall

GTEST_DIR = C:\gtest-1.7.0

GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a

GTEST_INC = -isystem $(GTEST_DIR)\include

HEADERS = \
	..\inc\Command.h \
	..\inc\CommandFactory.h \
	..\inc\Config.h \
	..\inc\CreateWalletCmd.h \
	..\inc\MessageCodes_E.h \
	..\inc\MessageHandler.h \
	..\inc\Wallet.h \
	..\inc\WalletEntity.h \
	..\inc\FileHelper.h
	
OBJECTS = \
	Command.o \
	CommandFactory.o \
	CreateWalletCmd.o \
	MessageHandler.o \
	Wallet.o \
	WalletEntity.o \
	FileHelper.o

WALLET_LIB = ..\lib\WalletLib.a

all: ..\lib\WalletLib.a WalletMain.o
	
# for wallet execution
..\lib\WalletLib.a: $(OBJECTS)
	$(AR) ..\lib\WalletLib.a $(OBJECTS)

Command.o: Command.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o Command.o -c Command.cpp

CommandFactory.o: CommandFactory.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o CommandFactory.o -c CommandFactory.cpp

Wallet.o: Wallet.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o Wallet.o -c Wallet.cpp

CreateWalletCmd.o: CreateWalletCmd.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o CreateWalletCmd.o -c CreateWalletCmd.cpp

WalletEntity.o: WalletEntity.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o WalletEntity.o -c WalletEntity.cpp
	
MessageHandler.o: MessageHandler.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o MessageHandler.o -c MessageHandler.cpp

FileHelper.o: FileHelper.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o FileHelper.o -c FileHelper.cpp
	
WalletMain.o: main.cpp $(HEADERS)
	$(CPP) $(CPP_FLAGS) $(INC_FLAG) -o WalletMain.o -c main.cpp
	

# clean up
clean:
	rm $(OBJECTS)
	rm ../lib/WalletLib.a
	rm WalletMain.o
