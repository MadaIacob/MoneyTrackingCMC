/*
File Description		Tests for the CommandInterpreter functions 
Author					Cosmin Farcau
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include "CommandInterpreter.h"



// validAmount function
TEST(CommandInterpreter, ValidAmount_NotAllowedChar)
{
	ASSERT_EQ(false, validateAmount("-s34d3.5"));
	ASSERT_EQ(false, validateAmount("3ddd4.5"));
	ASSERT_EQ(false, validateAmount("f633.5"));
	ASSERT_EQ(false, validateAmount("+343.000d35"));
	ASSERT_EQ(false, validateAmount("+34*3.00035"));
	ASSERT_EQ(false, validateAmount("+3^43.00035"));
}

TEST(CommandInterpreter, ValidAmount_LeadingZeros)
{
	ASSERT_EQ(true, validateAmount("-00003493.47895"));
	ASSERT_EQ(false, validateAmount("-0003d4.3695"));
	ASSERT_EQ(true, validateAmount("+000000006.00005"));
	ASSERT_EQ(true, validateAmount("000039998.00035"));
}

// truncateAmount function; aici pot testa doar cu valori fara caractere speciale
// sau litere !?
TEST(CommandInterpreter, TruncateAmount)
{
	ASSERT_EQ("-3493.48", truncateAmount("-00003493.47895"));
	ASSERT_EQ("-34.37", truncateAmount("-00034.3695"));
	ASSERT_EQ("6", truncateAmount("+000000006.00005"));
	ASSERT_EQ("39998", truncateAmount("000039998.00035"));
}
