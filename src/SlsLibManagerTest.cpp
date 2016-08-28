/*
 * SlsLibManagerTest.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: ares
 */

#include <iomanip>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#include "SlsLibManager.h"

TEST(SlsLibManager, SetLibrariesPath)
{
   SlsLibManager Test;
   SLS_STATUS Status;
   const char invalidPath[] = "./some/test/lib/path";
   const char validPath[] = "./testing/libs";
   Status = Test.setPath(invalidPath);
   EXPECT_EQ(Status, SLS_INVALID_PATH);
   Status = Test.setPath(validPath);
   EXPECT_EQ(Status, SLS_OK);
}

TEST(SlsLibManager, LoadLibrariesFromPath)
{
   SlsLibManager Test;
   SLS_STATUS Status;
   const char emptyPath[] = "./testing/empty";
   const char nonemptyPath[] = "./testing/libs";

   // Test empty directory
   EXPECT_EQ(Test.m_LoadedLibs.size(), 0);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_INVALID_PATH);
   Status = Test.setPath(emptyPath);
   EXPECT_EQ(Status, SLS_OK);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_OK);
   EXPECT_EQ(Test.m_LoadedLibs.size(), 0);

   // Test valid directory
   Status = Test.setPath(nonemptyPath);
   EXPECT_EQ(Status, SLS_OK);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_OK);
   EXPECT_EQ(Test.m_LoadedLibs.size(), 1);
}

TEST(SlsLibManager, GetApiFromLibrary)
{
   SlsLibManager Test;
   SLS_STATUS Status;
   const char nonemptyPath[] = "./testing/libs";

   Test.setPath(nonemptyPath);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_OK);
   for(std::map<std::string, SlsLibApi>::iterator it = Test.m_LoadedLibs.begin(); it != Test.m_LoadedLibs.end(); it++)
   {
      EXPECT_EQ(it->second.size(), 4);
      for(std::map<std::string, sls_lib_function>::iterator it2 = it->second.begin(); it2 != it->second. end(); it2++)
      {
         std::cout << it2->first << " ptr: " << std::hex << it2->second <<std::endl;
         if(it2->first == "TestFunPrintMsg")
         {
            std::cout << "To jest to!" << std::endl;
            uint8_t testMsg[] = "Hello fun fromdynamic loaded lib!\n";
            uint16_t testMsgSize = sizeof(testMsg);
            SlsStack testStack(128);
            testStack.pushn(testMsg, sizeof(testMsg));
            testStack.pushw(testMsgSize);
            Status = it2->second(&testStack);
         }
      }
      /*
      uint8_t testMsg[] = "Hello fun fromdynamic loaded lib!\n";
      SlsStack testStack(128);
      testStack.pushn(testMsg, sizeof(testMsg));
      it->second["TestFunPrintMsg"](&testStack);
      */
   }

}
