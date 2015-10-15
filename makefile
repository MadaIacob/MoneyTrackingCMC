CPP = g++

GTEST_DIR = C:\gtest-1.7.0
GTEST_LIB = $(GTEST_DIR)\make\gtest_main.a
GTEST_INC = -isystem $(GTEST_DIR)\include

LIB_OBJ = main\lib\WalletLib.a
LIB_TST = main\lib\TestLib.a

app: 
	$(MAKE) -C main\src
	$(MAKE) -C main\tst
	$(MAKE) moneytracker.exe
	
moneytracker.exe: main\lib\WalletLib.a main\src\WalletMain.o
	$(CPP) -o moneytracker.exe main\src\WalletMain.o main\lib\WalletLib.a

test.exe: $(LIB_OBJ) $(LIB_TST) $(GTEST_LIB)
	$(CPP) -o test.exe $(LIB_TST) $(LIB_OBJ) $(GTEST_LIB)

	
cleanAll:
	$(MAKE) -C main\src clean
	$(MAKE) -C main\tst clean
clean:	
	rm moneytracker.exe
	rm test.exe