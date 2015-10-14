/*
File Description		Tests the  WalletEntity class' methods 
Author					madalina.iacob
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include <windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "CreateWalletTestHelper.h"

//using namespace std;

TEST(CreateWalletTest, TestContent)
{
	helperCreateWallet("my.wallett" , "+1000");
	helperCreateWallet("other.wallet" , "+200");
	helperCreateWallet("yetother" , "-1021.23");
	helperCreateWallet("noinitial.wallet");
	helperCreateWallet("leading0.wallet" , "-00012.24");
	
	EXPECT_EQ("+1000 RON" , readWallet("my.wallett"));
	EXPECT_EQ("+200 RON" , readWallet("other.wallet"));
	EXPECT_EQ("-1021.23 RON" , readWallet("yetother"));
	EXPECT_EQ("+00.00 RON", readWallet("noinitial.wallet"));
	EXPECT_EQ("-00012.24 RON", readWallet("leading0.wallet"));
}

TEST(CreateWalletTest, TestCreate)
{
	helperCreateWallet("yetother");
	helperCreateWallet("C**%^&%");
	
	EXPECT_EQ(1 , walletCreated("yetother"));
	EXPECT_EQ(0 , walletCreated("C**%^&%"));
	
}

TEST(CreateWalletTest, TestWithAbsolutePath)
{
	std::string path = "C:\\mada";
	std::string file = "C:\\mada\\mmm.txt";
	
	bool createDir = CreateDirectory(path.c_str(),NULL);
	std::cout << "mmmmmmmmmmmmmmmmmmmmmm" << createDir << std::endl;
	helperCreateWallet(file);
	EXPECT_EQ(1 , walletCreated(file));
	
	if(createDir == true)
	{
		createDir = remove(file.c_str());
		createDir = RemoveDirectory(path.c_str());
		std::cout << "aaaaaaaaaaaaaaaaaaaaaaa" << createDir << std::endl;
	}
}

