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

TEST(SlsVariable, SlsVariables)
{
   SLS_STATUS Status;
   int64_t valueTester;
   SlsInt test1;
   SlsInt test2(5);
   SlsInt test3(-100);
   SlsInt test4 = test1 + test2;
   SlsInt test5 = test1 - test2;
   ASSERT_TRUE(test4 == 5);
   ASSERT_TRUE(test5 == -5);
   ASSERT_TRUE(test4 == test2);
   ASSERT_TRUE(test5 == -test2);
   ASSERT_TRUE(test4 != 123);
   ASSERT_TRUE(test4 != test5);
   Status = test4.get(NULL);
   ASSERT_EQ(SLS_PTR_ERROR, Status);
   Status = test4.get(&valueTester);
   ASSERT_EQ(SLS_OK, Status);
   ASSERT_EQ(5, valueTester);
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
}

TEST(SlsVariable, SlsArrays)
{
   uint8_t *arrayValues = new uint8_t(10);
   EXPECT_THROW(SlsArray test1(1, NULL), SlsException);
   EXPECT_NO_THROW( SlsArray(10, new uint8_t(10) ) );
   EXPECT_NO_THROW(SlsArray(10, arrayValues));
}

TEST(SlsVariable, SlsVariablesContainter)
{
   SlsVarContainer testVariables;
   std::shared_ptr<SlsInt> p(new SlsArray(10, new uint8_t(10) ));
   std::shared_ptr<SlsInt> q(new SlsInt(1));
   std::shared_ptr<SlsInt> r(new SlsInt(1));
   testVariables.insert( SlsVar("Id", std::shared_ptr<SlsInt>(new SlsInt(1))) );
   testVariables.insert( SlsVar("Name", p) );
   testVariables.insert( SlsVar("Score", q) );
   testVariables.insert( SlsVar("Age", r) );
}
