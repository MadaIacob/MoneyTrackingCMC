#include "gtest/gtest.h"

#include "Wallet.h"
#include "WalletEntity.h"

#include <fstream>
#include <iostream>

using namespace std;

TEST(CreateWalletFileTest, creatingFile) 
{
	//set-up
	WalletEntity entity1("+","153.2689","RON");
	Wallet wallet1("testWallet", entity1);
	
	WalletEntity entity2("+","153.2689","RON");
	Wallet wallet2("C:/testWallet", entity2);
	
	WalletEntity entity3("+","153.2689","RON");
	Wallet wallet3("C:/testWalletDir/testWalletFile", entity3);
	
	//TEST
	EXPECT_EQ(true, wallet1.createWalletFile());
	EXPECT_EQ(true, wallet2.createWalletFile());
	
	EXPECT_EQ(false, wallet3.createWalletFile());
	
	//tear-down
	remove("testWallet");
	remove("C:/testWallet");
	remove("C:/testWalletDir/testWalletFile");
}

TEST(AppendWalletFileTest, testAppend)
{
	//set-up
	WalletEntity entity1("+","153.2689","RON");
	WalletEntity entity2("-","200","lost","RON");
	Wallet wallet1("testWallet", entity1);
	wallet1.createWalletFile();
	
	//test
	EXPECT_EQ(true, wallet1.appendWalletFile(entity2));
	
	//tear-down
	remove("testWallet");
}
TEST(ReadWalletFileTest, readWallet)
{
	//set-up
	WalletEntity entity1("+","153.2689","RON");
	Wallet wallet1("testWallet", entity1);
	WalletEntity entity2("-","200","lost","RON");
	wallet1.createWalletFile();
	wallet1.appendWalletFile(entity2);
	
	Wallet walletRead("testWallet");
	walletRead.readWalletFile();
	
	//test
	EXPECT_EQ("+", walletRead.getWalletContent().at(0).getSign());
	EXPECT_EQ("153.2689", walletRead.getWalletContent().at(0).getAmount());
	EXPECT_EQ("RON",  walletRead.getWalletContent().at(0).getCurrency());
	
	EXPECT_EQ("-",  walletRead.getWalletContent().at(1).getSign());
	EXPECT_EQ("200",  walletRead.getWalletContent().at(1).getAmount());
	EXPECT_EQ("lost",  walletRead.getWalletContent().at(1).getCategory());
	EXPECT_EQ("RON",  walletRead.getWalletContent().at(1).getCurrency());
	
	//tear-down
	remove("testWallet");	
}

TEST(GetWalletEntityFromLineTest, getWalletEntity)
{
	//set-up
	WalletEntity entity1;
	WalletEntity entity2;
	Wallet wallet("wallet", entity1);
	
	entity2 = wallet.getWalletEntityFromLine("145698;+;124.36;category;RON");
	
	string ssTimeStamp; // time converted to string
	
	//convert from time_t to string
	std::stringstream ss;
	ss << entity2.getTimeStamp();
	ssTimeStamp = ss.str();
	
	//test
	EXPECT_EQ("145698",  ssTimeStamp);
	EXPECT_EQ("+", entity2.getSign());
	EXPECT_EQ("124.36",  entity2.getAmount());
	EXPECT_EQ("category",  entity2.getCategory());
	EXPECT_EQ("RON",  entity2.getCurrency());
	
	//tear-down
	remove("wallet");
}