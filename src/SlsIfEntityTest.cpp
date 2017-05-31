/*
 * SlsIfEntityTest.cpp
 *
 *  Created on: Nov 27, 2016
 *      Author: ares
 */

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#define private public
#include "SlsScriptEntity.hpp"

TEST(SlsIfEntity, TestConditionParsing_1)
{
   std::string IfPath("./testing/test_xml_if_file1.xml");
   if(!boost::filesystem::exists(IfPath))
   {
      EXPECT_TRUE(false) << "Invalid test xml path.";
   }
   else
   {
      try
      {
         boost::property_tree::ptree IfStatement;
         read_xml(IfPath, IfStatement);
         for(auto& child : IfStatement)
         {
            if("if" != child.first)
            {
               continue;
            }

            SlsIfEntity test;
            std::string expected = child.second.get<std::string>("<xmlattr>.expected", "not found");
            std::string syntaxok = child.second.get<std::string>("<xmlattr>.syntaxok", "not found");
            SLS_STATUS syntax = ("true" == syntaxok) ? SLS_OK : SLS_ERROR;
            std::cout << "<!-----------------!>" << std::endl;
            std::cout << child.first << " : " << expected << " : " << syntaxok << std::endl;
            SLS_STATUS result = test.parse(child.second);
            std::string parsed = test.toString();
            EXPECT_TRUE(result == syntax);
            EXPECT_TRUE(parsed == expected);
            std::cout << "<!-----------------!>" << std::endl;
         }
      }
      catch (std::exception& e)
      {
         EXPECT_TRUE(false) << "Invalid test xml file.";
      }
   }
}

