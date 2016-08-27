/*
 * SlsProgramTest.cpp
 *
 *  Created on: Aug 22, 2016
 *      Author: ares
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#define private public
#include "SlsProgram.h"

TEST(SlsProgram, LoadXmlTestScriptNotExisting)
{
   SlsProgram test;
   EXPECT_FALSE( test.load("invalid_path_to_some_file") );
}

TEST(SlsProgram, LoadXmlTestScriptValidExisting)
{
   SlsProgram test;
   EXPECT_TRUE( test.load("./testing/test_xml_valid_file.xml") );
}

TEST(SlsProgram, CompileXmlTestScriptValid)
{
   SlsProgram test;
   test.load("./testing/test_xml_valid_file.xml");
   EXPECT_TRUE( test.compile() );
}

TEST(SlsProgram, CompileXmlTestScriptInvalid)
{
   SlsProgram test;
   test.load("./testing/test_xml_invalid_file.xml");
   EXPECT_FALSE( test.compile() );
}

TEST(SlsProgram, BuildXmlTestScriptValid)
{
   SlsProgram test;
   EXPECT_TRUE( test.build("./testing/test_xml_valid_file.xml") );
}

TEST(SlsProgram, BuildXmlTestScriptInvalid)
{
   SlsProgram test;
   EXPECT_FALSE( test.build("./testing/test_xml_invalid_file.xml") );
}
