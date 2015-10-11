/*
File Description		Tests the  WalletEntity class' methods 
Author					madalina.iacob
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include "CreateWalletTestHelper.h"

TEST(CreateWalletTest, TestContent)
{
	helperCreateWallet("my.wallet" , "+1000");
	helperCreateWallet("other.wallet" , "+200");
	helperCreateWallet("yetother" , "-1021.23");
	helperCreateWallet("noinitial.wallet");
	helperCreateWallet("leading0.wallet" , "-00012.24");
	
	EXPECT_EQ("+1000 RON" , readWallet("my.wallet"));
	EXPECT_EQ("+200 RON" , readWallet("other.wallet"));
	EXPECT_EQ("-1021.23 RON" , readWallet("yetother"));
	EXPECT_EQ("+00.00 RON", readWallet("noinitial.wallet"));
	EXPECT_EQ("-00012.24 RON", readWallet("leading0.wallet"));
}

TEST(CreateWalletTest, TestCreate)
{
	helperCreateWallet("yetother");
	helperCreateWallet("C:\\mada\\tst");
	helperCreateWallet("C:/learn/MoneyTrackingCMC/madaFile.txt");
	
	EXPECT_EQ(1 , walletCreated("yetother"));
	EXPECT_EQ(0 , walletCreated("C:\\mada\\tst"));
	EXPECT_EQ(1 , walletCreated("C:/learn/MoneyTrackingCMC/madaFile.txt"));
	
}

