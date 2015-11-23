//============================================================================
// Name        : HelperFunctionsTest.cpp
// Author      : AmadeusCPPL, calin-ciprian.popita
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Test implementation for HelperFunctions, in C++
//============================================================================

#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "HelperFunctions.h"
#include "TestHelper.h"
using namespace std;

TEST(validateAmountTest, notAllowedCharacters)
{
	//test
	EXPECT_EQ(false, validateAmount("-s34d3.5"));
	EXPECT_EQ(true, validateAmount("+0.000"));
	EXPECT_EQ(true, validateAmount("0"));
	EXPECT_EQ(true, validateAmount("-0.000"));
	EXPECT_EQ(false, validateAmount("3ddd4.5"));
	EXPECT_EQ(false, validateAmount("f633.5"));
	EXPECT_EQ(false, validateAmount("+343.000d35"));
	EXPECT_EQ(false, validateAmount("+34*3.00035"));
	EXPECT_EQ(false, validateAmount("+3^43.00035"));
	EXPECT_EQ(false, validateAmount("-3^43.0/0*.35"));
	EXPECT_EQ(false, validateAmount("+3^43.00<>\?035"));
	EXPECT_EQ(false, validateAmount("-3^43.00:\"?035"));
	EXPECT_EQ(false, validateAmount("+-456"));
	EXPECT_EQ(false, validateAmount("-+32.5456"));

}

TEST(validateAmountTest, leadingZeros)
{
	//test
	EXPECT_EQ(true, validateAmount("+0000.000"));
	EXPECT_EQ(true, validateAmount("00000"));
	EXPECT_EQ(true, validateAmount("-00.000"));
	EXPECT_EQ(true, validateAmount("-00003493.47895"));
	EXPECT_EQ(false, validateAmount("-0003d4.3695"));
	EXPECT_EQ(true, validateAmount("+000000006.00005"));
	EXPECT_EQ(true, validateAmount("000039998.00035"));
	EXPECT_EQ(true, validateAmount("+65"));
	EXPECT_EQ(true, validateAmount("39998"));
	EXPECT_EQ(true, validateAmount("-5"));
	EXPECT_EQ(true, validateAmount("-35987"));
}

TEST(cutSignTest, cutMinus)
{
	EXPECT_EQ("4d3.5", cutSign("-4d3.5"));
	EXPECT_EQ("-4d3.5", cutSign("--4d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("-#k0.634d3.5"));
	EXPECT_EQ("+343.565", cutSign("-+343.565"));
	EXPECT_EQ("0003435", cutSign("-0003435"));
	EXPECT_EQ("0.34365", cutSign("-0.34365"));
	EXPECT_EQ("0000.0123", cutSign("-0000.0123"));
	EXPECT_EQ("896123", cutSign("-896123"));
}

TEST(cutSignTest, cutPlus)
{
	EXPECT_EQ("4d3.5", cutSign("+4d3.5"));
	EXPECT_EQ("00003654d3.5", cutSign("+00003654d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("+#k0.634d3.5"));
	EXPECT_EQ("3435", cutSign("+3435"));
	EXPECT_EQ("0.3435", cutSign("+0.3435"));
	EXPECT_EQ("0000.3435", cutSign("+0000.3435"));
}


TEST(truncateAmountTest, allowedCharacters)
{
	//test
	EXPECT_EQ("-3493.48", truncateAmount("-00003493.47895"));
	EXPECT_EQ("-34.37", truncateAmount("-00034.3695"));
	EXPECT_EQ("+6.00", truncateAmount("+000000006.00005"));
	EXPECT_EQ("+39998.00", truncateAmount("000039998.00035"));
	EXPECT_EQ("+349348.00", truncateAmount("349348"));
	EXPECT_EQ("-3437.00", truncateAmount("-3437"));
	EXPECT_EQ("+6.00", truncateAmount("+6"));
	EXPECT_EQ("+39998.00", truncateAmount("000039998.00035"));
	EXPECT_EQ("+00.00", truncateAmount("+000"));
	EXPECT_EQ("+00.00", truncateAmount("-0"));
	EXPECT_EQ("+00.00", truncateAmount("-000"));
	EXPECT_EQ("+00.00", truncateAmount("+0.00"));
	EXPECT_EQ("+00.00", truncateAmount("-000.000"));
	EXPECT_EQ("+00.00", truncateAmount("-0.00"));
}

TEST(stoiTest, valid)
{
	//test
	EXPECT_EQ(0, stoi("0"));
	EXPECT_EQ(0, stoi("00"));
	EXPECT_EQ(0, stoi("00000000000000"));
	EXPECT_EQ(1, stoi("1"));
	EXPECT_EQ(1, stoi("01"));
	EXPECT_EQ(20004, stoi("00000000020004"));
	EXPECT_EQ(30005, stoi("00030005"));
	EXPECT_EQ(700004, stoi("00000000000700004"));
	EXPECT_EQ(123456789, stoi("00000000000123456789"));
}

TEST(stoiTest, notValid)
{
	//test
	EXPECT_EQ(-1, stoi("+0"));
	EXPECT_EQ(-1, stoi("0.0"));
	EXPECT_EQ(-1, stoi("00000000000-000"));
	EXPECT_EQ(-1, stoi("-1"));
	EXPECT_EQ(-1, stoi("00030 005"));
	EXPECT_EQ(-1, stoi("00000000000123456789+"));
}

TEST(parseDateTimeTest, notValid)
{
	//set-up
	string dateTime1 = "0--0-0000 0:00";
	string dateTime2 = "00-0-0100 0:005";
	string dateTime3 = "0-00-+000 0:10";
	string dateTime4 = "9-0 8000 00:00";
	string dateTime5 = "00-00-0080 0-00";
	string dateTime6 = "00-00-0000 0004";	
	string dateTime7 = "0-0-0000 *0:00";
	string dateTime8 = "300-0-0100 0:005";
	string dateTime9 = "G0-00-000 0:10";
	string dateTime10 = "9-0i-8000 00:00";
	string dateTime11 = "00-00-0r80 0:00";
	string dateTime12 = "00/00-0000 09:04";	
	string dateTime13 = " 00-00-0000 09:04";	
	string dateTime14 = "00-00-0000  09:04";	
	string dateTime15 = "00-00-0000 09:04 ";	
	string dateTime16 = "00-00-0000 09 :04";	
	string dateTime17 = "00-00-0000 +09:04";	
	
	//test
	EXPECT_FALSE(parseDateTime(dateTime1));
	EXPECT_EQ("0--0-0000 0:00", dateTime1);
	EXPECT_FALSE(parseDateTime(dateTime2));
	EXPECT_EQ("00-0-0100 0:005", dateTime2);
	EXPECT_FALSE(parseDateTime(dateTime3));
	EXPECT_EQ("0-00-+000 0:10", dateTime3);
	EXPECT_FALSE(parseDateTime(dateTime4));
	EXPECT_EQ("9-0 8000 00:00", dateTime4);
	EXPECT_FALSE(parseDateTime(dateTime5));
	EXPECT_EQ("00-00-0080 0-00", dateTime5);
	EXPECT_FALSE(parseDateTime(dateTime6));	
	EXPECT_EQ("00-00-0000 0004", dateTime6);
	EXPECT_FALSE(parseDateTime(dateTime7));
	EXPECT_EQ("0-0-0000 *0:00", dateTime7);
	EXPECT_FALSE(parseDateTime(dateTime8));
	EXPECT_EQ("300-0-0100 0:005", dateTime8);
	EXPECT_FALSE(parseDateTime(dateTime9));
	EXPECT_EQ("G0-00-000 0:10", dateTime9);
	EXPECT_FALSE(parseDateTime(dateTime10));
	EXPECT_EQ("9-0i-8000 00:00", dateTime10);
	EXPECT_FALSE(parseDateTime(dateTime11));
	EXPECT_EQ("00-00-0r80 0:00", dateTime11);
	EXPECT_FALSE(parseDateTime(dateTime12));	
	EXPECT_EQ("00/00-0000 09:04", dateTime12);
	EXPECT_FALSE(parseDateTime(dateTime13));
	EXPECT_EQ(" 00-00-0000 09:04", dateTime13);
	EXPECT_FALSE(parseDateTime(dateTime14));
	EXPECT_EQ("00-00-0000  09:04", dateTime14);
	EXPECT_FALSE(parseDateTime(dateTime15));
	EXPECT_EQ("00-00-0000 09:04 ", dateTime15);
	EXPECT_FALSE(parseDateTime(dateTime16));
	EXPECT_EQ("00-00-0000 09 :04", dateTime16);
	EXPECT_FALSE(parseDateTime(dateTime17));
	EXPECT_EQ("00-00-0000 +09:04", dateTime17);
	
	//tear-down
}

TEST(parseDateTimeTest, valid)
{
	//set-up
	string dateTime1 = "0-0-0000 0:00";
	string dateTime2 = "00-0-0100 0:05";
	string dateTime3 = "0-00-0105 0:10";
	string dateTime4 = "9-0-8000 00:00";
	string dateTime5 = "10-03-0080 0:00";
	string dateTime6 = "3-00-0000 00:04";	
	string dateTime7 = "17-0-2004 24:00";
	string dateTime8 = "30-20-0100 03:05";
	
	//test
	EXPECT_TRUE(parseDateTime(dateTime1));
	EXPECT_EQ("00-00-0000 00:00", dateTime1);
	EXPECT_TRUE(parseDateTime(dateTime2));
	EXPECT_EQ("00-00-0100 00:05", dateTime2);
	EXPECT_TRUE(parseDateTime(dateTime3));
	EXPECT_EQ("00-00-0105 00:10", dateTime3);
	EXPECT_TRUE(parseDateTime(dateTime4));
	EXPECT_EQ("09-00-8000 00:00", dateTime4);
	EXPECT_TRUE(parseDateTime(dateTime5));
	EXPECT_EQ("10-03-0080 00:00", dateTime5);
	EXPECT_TRUE(parseDateTime(dateTime6));	
	EXPECT_EQ("03-00-0000 00:04", dateTime6);
	EXPECT_TRUE(parseDateTime(dateTime7));
	EXPECT_EQ("17-00-2004 24:00", dateTime7);
	EXPECT_TRUE(parseDateTime(dateTime8));
	EXPECT_EQ("30-20-0100 03:05", dateTime8);
	
	//tear-down
}

TEST(validateDateTimeTest, boundariesDay)
{
	//set-up
	string dateTime1 = "12-12-1970 23:59";
	string dateTime2 = "01-01-1971 00:00";
	string dateTime3 = "31-01-1971 23:59";
	string dateTime4 = "32-01-1971 00:00";
	string dateTime5 = "01-02-1971 00:00";
	string dateTime6 = "28-02-1971 23:59";	
	string dateTime7 = "29-02-1971 00:00";
	string dateTime8 = "01-03-1971 00:00";
	string dateTime9 = "31-03-1971 00:00";
	string dateTime10 = "32-03-1971 00:00";
	string dateTime11 = "01-04-1971 00:00";
	string dateTime12 = "30-04-1971 23:59";	
	string dateTime13 = "31-04-1971 00:00";	
	string dateTime14 = "01-05-1971 00:00";	
	string dateTime15 = "31-05-1971 23:59";	
	string dateTime16 = "32-05-1971 00:00";	
	string dateTime17 = "01-06-1971 00:00";
	string dateTime18 = "30-06-1971 23:59";	
	string dateTime19 = "31-06-1971 00:00";	
	string dateTime20 = "01-07-1971 00:00";	
	string dateTime21 = "31-07-1971 23:59";	
	string dateTime22 = "32-07-1971 00:00";
	string dateTime23 = "01-08-1971 00:00";
	string dateTime24 = "31-08-1971 23:59";	
	string dateTime25 = "32-08-1971 00:00";
	string dateTime26 = "01-09-1971 00:00";
	string dateTime27 = "30-09-1971 23:59";
	string dateTime28 = "31-09-1971 00:00";
	string dateTime29 = "01-10-1971 00:00";
	string dateTime30 = "31-10-1971 23:59";
	string dateTime31 = "32-10-1971 00:00";
	string dateTime32 = "01-11-1971 00:00";
	string dateTime33 = "30-11-1971 23:59";
	string dateTime34 = "31-11-1971 00:00";
	string dateTime35 = "01-12-1971 00:00";
	string dateTime36 = "31-12-1971 23:59";
	string dateTime37 = "32-12-1971 00:00";
	string dateTime38 = "01-01-1972 00:00";
	string dateTime39 = "29-02-1972 23:59";	//leap year
	string dateTime40 = "30-02-1972 00:00"; //leap year
	string dateTime41 = "01-03-1972 00:00"; //leap year
	
	//test
	EXPECT_TRUE(validateDateTime(dateTime1));
	EXPECT_TRUE(validateDateTime(dateTime2));
	EXPECT_TRUE(validateDateTime(dateTime3));
	EXPECT_FALSE(validateDateTime(dateTime4));
	EXPECT_TRUE(validateDateTime(dateTime5));
	EXPECT_TRUE(validateDateTime(dateTime6));
	EXPECT_FALSE(validateDateTime(dateTime7));
	EXPECT_TRUE(validateDateTime(dateTime8));
	EXPECT_TRUE(validateDateTime(dateTime9));
	EXPECT_FALSE(validateDateTime(dateTime10));
	EXPECT_TRUE(validateDateTime(dateTime11));
	EXPECT_TRUE(validateDateTime(dateTime12));
	EXPECT_FALSE(validateDateTime(dateTime13));
	EXPECT_TRUE(validateDateTime(dateTime14));
	EXPECT_TRUE(validateDateTime(dateTime15));
	EXPECT_FALSE(validateDateTime(dateTime16));
	EXPECT_TRUE(validateDateTime(dateTime17));
	EXPECT_TRUE(validateDateTime(dateTime18));
	EXPECT_FALSE(validateDateTime(dateTime19));
	EXPECT_TRUE(validateDateTime(dateTime20));
	EXPECT_TRUE(validateDateTime(dateTime21));
	EXPECT_FALSE(validateDateTime(dateTime22));
	EXPECT_TRUE(validateDateTime(dateTime23));
	EXPECT_TRUE(validateDateTime(dateTime24));
	EXPECT_FALSE(validateDateTime(dateTime25));
	EXPECT_TRUE(validateDateTime(dateTime26));
	EXPECT_TRUE(validateDateTime(dateTime27));
	EXPECT_FALSE(validateDateTime(dateTime28));
	EXPECT_TRUE(validateDateTime(dateTime29));
	EXPECT_TRUE(validateDateTime(dateTime30));
	EXPECT_FALSE(validateDateTime(dateTime31));
	EXPECT_TRUE(validateDateTime(dateTime32));
	EXPECT_TRUE(validateDateTime(dateTime33));
	EXPECT_FALSE(validateDateTime(dateTime34));
	EXPECT_TRUE(validateDateTime(dateTime35));
	EXPECT_TRUE(validateDateTime(dateTime36));
	EXPECT_FALSE(validateDateTime(dateTime37));
	EXPECT_TRUE(validateDateTime(dateTime38));
	EXPECT_TRUE(validateDateTime(dateTime39)); //leap year
	EXPECT_FALSE(validateDateTime(dateTime40)); //leap year
	EXPECT_TRUE(validateDateTime(dateTime41)); //leap year
	
	//tear-down
}

TEST(validateDateTimeTest, boundariesMonth)
{
	//set-up
	string dateTime1 = "12-00-1989 23:59";
	string dateTime2 = "01-13-1972 00:00";
	
	//test
	EXPECT_FALSE(validateDateTime(dateTime1));
	EXPECT_FALSE(validateDateTime(dateTime2));
	
	//tear-down
}

TEST(validateDateTimeTest, boundariesYear)
{
	//set-up
	string dateTime1 = "31-12-1969 23:59";
	string dateTime2 = "01-13-9999 00:00";
	
	//test
	EXPECT_FALSE(validateDateTime(dateTime1));
	EXPECT_FALSE(validateDateTime(dateTime2));
	
	//tear-down
}

TEST(validateDateTimeTest, outOfRangeHour)
{
	//set-up
	string dateTime1 = "31-12-1989 24:00";
	string dateTime2 = "01-13-2013 99:00";
	
	//test
	EXPECT_FALSE(validateDateTime(dateTime1));
	EXPECT_FALSE(validateDateTime(dateTime2));
	
	//tear-down
}

TEST(validateDateTimeTest, outOfRangeMinute)
{
	//set-up
	string dateTime1 = "31-12-1989 22:60";
	string dateTime2 = "01-13-2013 00:99";
	
	//test
	EXPECT_FALSE(validateDateTime(dateTime1));
	EXPECT_FALSE(validateDateTime(dateTime2));
	
	//tear-down
}