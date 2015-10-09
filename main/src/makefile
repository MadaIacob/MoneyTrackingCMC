
all: Main.cpp CommandInterpreter.cpp PrintMessage.cpp WalletEntity.cpp
	g++ -c Main.cpp CommandInterpreter.cpp PrintMessage.cpp WalletEntity.cpp
	g++ -o mt Main.o CommandInterpreter.o PrintMessage.o WalletEntity.o

# clean up
clean:
	rm *.o
	rm *.exe
	rm *.txt