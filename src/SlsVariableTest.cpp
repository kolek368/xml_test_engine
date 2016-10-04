/*
 * SlsVariableTest.cpp
 *
 *  Created on: Sep 9, 2016
 *      Author: ares
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

//#define private public
#include "SlsVariable.hpp"

#include <exception>

TEST(SlsVariable, SlsIntVariables)
{
   SLS_STATUS Status;
   int64_t valueTester;
   SlsInt test1;
   SlsInt test2(5);
   SlsInt test3(-100);
   SlsInt test4 = test1 + test2;
   SlsInt test5 = test1 - test2;
   Status = test4.get(NULL);
   ASSERT_EQ(SLS_PTR_ERROR, Status);
   Status = test4.get(&valueTester);
   ASSERT_EQ(SLS_OK, Status);
   ASSERT_EQ(5, valueTester);
   ASSERT_TRUE(test4 == 5);
   ASSERT_TRUE(test5 == -5);
   ASSERT_TRUE(test4 == test2);
   ASSERT_TRUE(test5 == -test2);
   ASSERT_TRUE(test4 != 123);
   ASSERT_TRUE(test4 != test5);
   ASSERT_TRUE(test4 > 4);
   ASSERT_FALSE(test4 > 5);
   ASSERT_TRUE(test4 >= 5);
   ASSERT_FALSE(test4 >= 6);
   ASSERT_TRUE(test4 < 6);
   ASSERT_FALSE(test4 < 5);
   ASSERT_TRUE(test4 <= 5);
   ASSERT_FALSE(test4 <= 4);
   test4 += test3;
   ASSERT_TRUE(test4 == -95);
   test4 += 15;
   ASSERT_TRUE(test4 == -80);
   test4 -= 1;
   ASSERT_TRUE(test4 == -81);
   test4 = test4 * 2;
   ASSERT_TRUE(test4 == -162);
   test4 = test4 / 2;
   ASSERT_TRUE(test4 == -81);
   test4 *= 2;
   ASSERT_TRUE(test4 == -162);
   test4 /= 2;
   ASSERT_TRUE(test4 == -81);
   test1 = test2 * test2;
   ASSERT_TRUE(test1 == 25);
   ASSERT_TRUE( (test1 % 2) == 1 );
   test1 %= 2;
   ASSERT_TRUE( test1 == 1);
   test1 = 0xA5;
   ASSERT_TRUE( (test1 & 0x81) == 0x81 );
   test1 &= 0x81;
   ASSERT_TRUE( test1 == 0x81);
   ASSERT_TRUE( (test1 | 0x24) == 0xA5 );
   test1 |= 0x24;
   ASSERT_TRUE( test1 == 0xA5);
   test1 = 0xFF;
   ASSERT_TRUE( (test1 ^ 0xAA) == 0x55 );
   test1 ^= 0xAA;
   ASSERT_TRUE( test1 == 0x55);
   ASSERT_TRUE( (test1 << 1) == 0xAA );
   test1 <<= 1;
   ASSERT_TRUE( test1 == 0xAA);
   ASSERT_TRUE( (test1 >> 1) == 0x55 );
   test1 >>= 1;
   ASSERT_TRUE( test1 == 0x55);
}

TEST(SlsVariable, SlsArrays)
{
   uint8_t arrayValuesSize = 5;
   uint8_t *arrayValues;
   uint8_t *getPtr;
   int64_t getSize;
   try {
      arrayValues = new uint8_t[arrayValuesSize];
      for(int8_t i = 0; i < arrayValuesSize; i++)
      {
         //arrayValues[i] = 'a' + i;
         arrayValues[i] = 'a';
      }
      EXPECT_THROW(SlsArray test1(1, NULL), SlsException);
      EXPECT_NO_THROW(SlsArray(arrayValuesSize, arrayValues));
      SlsArray test1(arrayValuesSize, arrayValues);
      ASSERT_TRUE(SLS_PTR_ERROR == test1.get(NULL, NULL));
      ASSERT_TRUE(SLS_PTR_ERROR == test1.get(&getSize, NULL));
      ASSERT_TRUE(SLS_PTR_ERROR == test1.get(NULL, &getPtr));
      ASSERT_TRUE(SLS_OK == test1.get(&getSize, &getPtr));
      ASSERT_TRUE(getSize == arrayValuesSize);
      ASSERT_FALSE(getPtr == arrayValues);
      for(int8_t i = 0; i < arrayValuesSize; i++)
      {
         ASSERT_TRUE(getPtr[i] == arrayValues[i]);
      }
      delete[] arrayValues;
   }
   catch(std::exception& e) {
      std::cout<< "SlsVariable::SlsArrays failed: " << e.what();
   }
}

TEST(SlsVariable, SlsString)
{
   std::string testString = "Test string message for testing purposes";
   EXPECT_NO_THROW( SlsString s(testString) );
}

TEST(SlsVariable, SlsVariablesContainter)
{
   int64_t testInteger;
   std::string testString = "This is string test of a veeeeeeery long string adasd asdasdad asdasda asdada asdasd asdasd asdasd";
   std::string testString2;
   uint8_t *pUintArray = new uint8_t[50];
   SlsArray* p = new SlsArray(50, pUintArray );
   SlsInt* q = new SlsInt(1);
   SlsInt* r = new SlsInt(30);
   SlsString* s = new SlsString(testString);
   SlsVariables testVariables;
   testVariables.insert( SlsVarPair("Score", q) );
   testVariables.insert( SlsVarPair("Age", r) );
   testVariables.insert( SlsVarPair("Name", p) );
   testVariables.insert( SlsVarPair("Message", s));
   std::cout << "Type: " << testVariables.find("Age")->type() << std::endl;
   testVariables.get("Id", &testInteger);
   testVariables.get("Age", &testInteger);
   std::cout << "Age: " << testInteger << std::endl;
   delete[] pUintArray;
}
