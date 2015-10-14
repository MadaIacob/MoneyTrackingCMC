/*
File Description		Tests the  WalletEntity class' methods 
Author					madalina.iacob, calin-ciprian.popita
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "CreateWalletTestHelper.h"

//using namespace std;

TEST(CreateWalletTest, fileContent)
{
	//set-up
	helperCreateWallet("my.wallet" , "+1000");
	helperCreateWallet("other.wallet" , "+200");
	helperCreateWallet("yetother" , "-1021.23");
	helperCreateWallet("noinitial.wallet");
	helperCreateWallet("leading0.wallet" , "-00012.24");
	
	//test
	EXPECT_EQ("+1000 RON" , readWallet("my.wallet"));
	EXPECT_EQ("+200 RON" , readWallet("other.wallet"));
	EXPECT_EQ("-1021.23 RON" , readWallet("yetother"));
	EXPECT_EQ("+00.00 RON", readWallet("noinitial.wallet"));
	EXPECT_EQ("-00012.24 RON", readWallet("leading0.wallet"));
	
	//tear-down
	remove("my.wallet");
	remove("other.wallet");
	remove("yetother");
	remove("noinitial.wallet");
	remove("leading0.wallet");

}

TEST(CreateWalletTest, inCurrentFolder)
{
	//set-up
	helperCreateWallet("yetother");
	helperCreateWallet("C**%^&%");
	
	//test
	EXPECT_EQ(1 , walletCreated("yetother"));
	EXPECT_EQ(0 , walletCreated("C**%^&%"));
	
	//tear-down
	remove("yetother");

}

TEST(CreateWalletTest, withAbsolutePath)
{
	//set-up
	std::string path = "C:\\mada";
	std::string file = "C:\\mada\\mmm.txt";	
	bool createDir = CreateDirectory(path.c_str(),NULL);
	helperCreateWallet(file);
	
	//test
	EXPECT_EQ(1 , walletCreated(file));
	
	//tear-down
	if(createDir == true)
	{
		remove(file.c_str());
		RemoveDirectory(path.c_str());
	}

}

