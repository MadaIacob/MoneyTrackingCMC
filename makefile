CPP = g++

GTEST_DIR = C:\gtest-1.7.0
GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a
GTEST_INC = -isystem $(GTEST_DIR)\include

LIB_OBJ = main_classes\lib\WalletLib.a

app: 
	$(MAKE) -C main_classes\src
	$(MAKE) moneytracker.exe

moneytracker: 
	$(MAKE) -C main_classes\src
	$(MAKE) moneytracker.exe

moneytracker.exe: main_classes\lib\WalletLib.a main_classes\src\WalletMain.o
	$(CPP) -o moneytracker.exe main_classes\src\WalletMain.o main_classes\lib\WalletLib.a

	
clean:
	-rm moneytracker.exe
	$(MAKE) -C main_classes\src clean
	