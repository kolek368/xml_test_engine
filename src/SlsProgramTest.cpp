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
   SlsProgram test("./testing/libs");
   EXPECT_FALSE( test.load("invalid_path_to_some_file") );
}

TEST(SlsProgram, LoadXmlTestScriptValidExisting)
{
   SlsProgram test("./testing/libs");
   EXPECT_TRUE( test.load("./testing/test_xml_valid_file.xml") );
}

TEST(SlsProgram, CompileXmlTestScriptValid)
{
   SlsProgram test("./testing/libs");
   test.load("./testing/test_xml_valid_file.xml");
   EXPECT_TRUE( test.compile() );
}

TEST(SlsProgram, CompileXmlTestScriptInvalid)
{
   SlsProgram test("./testing/libs");
   test.load("./testing/test_xml_invalid_file.xml");
   EXPECT_FALSE( test.compile() );
}

TEST(SlsProgram, BuildXmlTestScriptValid)
{
   SlsProgram test("./testing/libs");
   int64_t Value;
   EXPECT_TRUE( test.build("./testing/test_xml_valid_file.xml") );
   test.run();
   static_cast<SlsInt*>(test.m_Variables.m_Variables["aaa"])->get(&Value);
   EXPECT_TRUE(123 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["bbb"])->get(&Value);
   EXPECT_TRUE(321 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["ccc"])->get(&Value);
   EXPECT_TRUE(444 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["ddd"])->get(&Value);
   EXPECT_TRUE(111 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["eee"])->get(&Value);
   EXPECT_TRUE(642 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["fff"])->get(&Value);
   EXPECT_TRUE(2 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["ggg"])->get(&Value);
   EXPECT_TRUE(79 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["hhh"])->get(&Value);
   EXPECT_TRUE(65 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["iii"])->get(&Value);
   EXPECT_TRUE(379 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["jjj"])->get(&Value);
   EXPECT_TRUE(314 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["kkk"])->get(&Value);
   EXPECT_TRUE(246 == Value);
   static_cast<SlsInt*>(test.m_Variables.m_Variables["lll"])->get(&Value);
   EXPECT_TRUE(123 == Value);
}

TEST(SlsProgram, BuildXmlTestScriptInvalid)
{
   SlsProgram test("./testing/libs");
   EXPECT_FALSE( test.build("./testing/test_xml_invalid_file.xml") );
}
