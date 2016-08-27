/*
 * SlsLibManagerTest.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: ares
 */

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
   //const char nonemptyPath[] = "./testing/libs";

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
   EXPECT_EQ(Test.m_LoadedLibs.size(), 0);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_INVALID_PATH);
   Status = Test.setPath(emptyPath);
   EXPECT_EQ(Status, SLS_OK);
   Status = Test.loadLibs();
   EXPECT_EQ(Status, SLS_OK);
   EXPECT_EQ(Test.m_LoadedLibs.size(), 0);
}
