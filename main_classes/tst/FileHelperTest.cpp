//============================================================================
// Name        : FileHelperTest.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Test implementation for FileHelper, in C++
//============================================================================

#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "FileHelper.h"
#include "TestHelper.h"
using namespace std;

TEST(validateFileNameTest, existingFileName)
{
	//set-up
	//helperCreateWallet("some.wallet","0.23");
	createFile("some.wallet" , "0.23");
	//test
	EXPECT_EQ(false, validateFileName("some.wallet"));
	EXPECT_EQ(true, validateFileName("not.wallet"));

	//tear-down
	remove("some.wallet");
}

TEST(convertPathTest, validFileNamePath)
{
	//set-up
	string path = "c:\\learn\\vasile.wallet";
	string expected = "c:/learn/vasile.wallet";

	//test
	EXPECT_EQ(expected, convertPath(path));

	//tear-down
}

TEST(convertPathTest, inValidFileNamePath)
{
	//set-up
	string path = "c:\\/learn\\/vasile.wallet";
	string expected = "c://learn//vasile.wallet";

	//test
	EXPECT_EQ(expected, convertPath(path));

	//tear-down
}
