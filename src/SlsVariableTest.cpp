/*
 * SlsVariableTest.cpp
 *
 *  Created on: Sep 9, 2016
 *      Author: ares
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#include "SlsVariable.hpp"

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
   uint8_t *arrayValues = new uint8_t(10);
   uint8_t *getPtr;
   int64_t getSize;
   for(int8_t i = 0; i < 10; i++)
   {
      arrayValues[i] = 'a' + i;
   }
   EXPECT_THROW(SlsArray test1(1, NULL), SlsException);
   EXPECT_NO_THROW( SlsArray(10, new uint8_t(10) ) );
   EXPECT_NO_THROW(SlsArray(10, arrayValues));
   SlsArray test1(10, arrayValues);
   ASSERT_TRUE(SLS_PTR_ERROR == test1.get(NULL, NULL));
   ASSERT_TRUE(SLS_PTR_ERROR == test1.get(&getSize, NULL));
   ASSERT_TRUE(SLS_PTR_ERROR == test1.get(NULL, &getPtr));
   ASSERT_TRUE(SLS_OK == test1.get(&getSize, &getPtr));
   ASSERT_TRUE(getSize == 10);
   ASSERT_FALSE(getPtr == arrayValues);
   for(int8_t i = 0; i < 10; i++)
   {
      ASSERT_TRUE(getPtr[i] == arrayValues[i]);
   }
   delete arrayValues;
}

TEST(SlsVariable, SlsVariablesContainter)
{
   SlsVarContainer testVariables;
   std::shared_ptr<SlsInt> p(new SlsArray(10, new uint8_t(10) ));
   std::shared_ptr<SlsInt> q(new SlsInt(1));
   std::shared_ptr<SlsInt> r(new SlsInt(1));
   testVariables.insert( SlsVar("Id", std::shared_ptr<SlsInt>(new SlsInt(1))) );
   testVariables.insert( SlsVar("Score", q) );
   testVariables.insert( SlsVar("Age", r) );
   testVariables.insert( SlsVar("Name", p) );
   testVariables.insert( SlsVar("Surname", std::shared_ptr<SlsInt>(new SlsArray(5, new uint8_t(5)))) );
}
