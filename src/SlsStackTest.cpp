/*
 * SlsStackTest.cpp
 *
 *  Created on: Aug 26, 2016
 *      Author: ares
 */
#include <iomanip>
#include "gmock/gmock.h"
#include "gtest/gtest.h"


#define private public
#include "SlsStack.hpp"

TEST(SlsStack, CreateVariableSizeStacks)
{
   EXPECT_NO_THROW(SlsStack testStack1);
   EXPECT_NO_THROW(SlsStack testStack2(2048));
   EXPECT_THROW(SlsStack testStack3(4097), SlsException);
}

TEST(SlsStack, StoreDataOnStack)
{
   SlsStack testStack1(12);
   uint8_t testArray[] = {0x01, 0x02, 0x03, 0x04, 0x05};
   EXPECT_NO_THROW(testStack1.push(0x01));
   EXPECT_NO_THROW(testStack1.pushw(0x0102));
   EXPECT_NO_THROW(testStack1.pushd(0x01020304));
   EXPECT_NO_THROW(testStack1.pushn(testArray, 5));
   EXPECT_THROW(testStack1.push(0x01), SlsException);
   EXPECT_THROW(testStack1.pushw(0x0102), SlsException);
   EXPECT_THROW(testStack1.pushd(0x01020304), SlsException);
   EXPECT_THROW(testStack1.pushn(testArray, 5), SlsException);
}

TEST(SlsStack, GetDataFromStackUint8)
{
   SlsStack testStack1(12);
   uint8_t testByte;

   testStack1.push(0x01);
   EXPECT_THROW(testStack1.pop(nullptr), SlsException);
   testStack1.pop(&testByte);
   EXPECT_EQ(testByte, 0x01);
   EXPECT_THROW(testStack1.pop(&testByte), SlsException);
   for(uint16_t byte = 0xFF; byte > 0x0; (byte >>= 1))
   {
      testStack1.push((uint8_t)byte);
      testStack1.pop(&testByte);
      EXPECT_EQ(testByte, byte);
   }
}

TEST(SlsStack, GetDataFromStackUint16)
{
   SlsStack testStack1(12);
   uint16_t testWord;

   testStack1.pushw(0x0102);
   EXPECT_THROW(testStack1.popw(nullptr), SlsException);
   testStack1.popw(&testWord);
   EXPECT_EQ(testWord, 0x0102);
   EXPECT_THROW(testStack1.popw(&testWord), SlsException);
   for(uint16_t word = 0xFFFF; word > 0; (word >>= 1))
   {
      testStack1.pushw((uint16_t)word);
      testStack1.popw(&testWord);
      EXPECT_EQ(testWord, word);
   }
}

TEST(SlsStack, GetDataFromStackUint32)
{
   SlsStack testStack1(12);
   uint32_t testDword;

   testStack1.pushd(0x01020304);
   EXPECT_THROW(testStack1.popd(nullptr), SlsException);
   testStack1.popd(&testDword);
   EXPECT_EQ(testDword, 0x01020304);
   EXPECT_THROW(testStack1.popd(&testDword), SlsException);
   for(uint32_t dword = 0xFFFFFFFF; dword > 0; (dword >>= 1))
   {
      testStack1.pushd(dword);
      testStack1.popd(&testDword);
      EXPECT_EQ(testDword, dword);
   }
}

TEST(SlsStack, GetDataFromStackUintNBytes)
{
   SlsStack testStack1(12);
   uint8_t testArray1[] = {0x01, 0x02, 0x03, 0x04, 0x05};
   uint8_t testArray2[] = {0x01, 0x02, 0x03, 0x04, 0x05};

   testStack1.pushn(testArray1, sizeof(testArray1));
   EXPECT_THROW(testStack1.popn(nullptr, 0), SlsException);
   testStack1.popn(testArray2, sizeof(testArray2));
   EXPECT_THAT(testArray2, testing::ElementsAre(0x01, 0x02, 0x03, 0x04, 0x05));
   EXPECT_THROW(testStack1.popn(testArray2, sizeof(testArray2)), SlsException);
}

TEST(SlsStack, GetDataFromStackVariousSizes)
{
   SlsStack testStack1(12);
   uint16_t testWord;
   uint32_t testDword;
   uint8_t testArray1[] = {0x01, 0x02, 0x03, 0x04, 0x05};

   typedef struct{
      uint8_t a;
      uint32_t b;
   }TestStruct;

   testStack1.push(0x01);
   EXPECT_THROW(testStack1.popw(&testWord), SlsException);
   EXPECT_THROW(testStack1.popd(&testDword), SlsException);
   EXPECT_THROW(testStack1.popn(testArray1, sizeof(testArray1)), SlsException);

   TestStruct TestStruct1;
   TestStruct1.a = 0x12;
   TestStruct1.b = 0x12345678;
   TestStruct TestStruct2;
   testStack1.pushn((uint8_t *)&TestStruct1, sizeof(TestStruct1));
   testStack1.popn((uint8_t*)&TestStruct2, sizeof(TestStruct2));
   EXPECT_EQ(TestStruct1.a, TestStruct2.a);
   EXPECT_EQ(TestStruct1.b, TestStruct2.b);
}

