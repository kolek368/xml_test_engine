/*
 * SlsProgram.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */
#include "SlsProgram.h"

SlsProgram::SlsProgram() {
   // TODO Auto-generated constructor stub

}

SlsProgram::~SlsProgram() {
   // TODO Auto-generated destructor stub
}

bool SlsProgram::load(const char* path)
{
   if(!boost::filesystem::exists(path))
      return false;
   try
   {
      read_xml(path, this->m_RawProgram);
   }
   catch (std::exception& e)
   {
      return false;
   }
   return true;
}

bool SlsProgram::parseLine(boost::property_tree::ptree::value_type &line)
{
   if(std::string(line.first.data()) == "call")
   {
      std::cout<< line.first.data() << "::" << line.second.data() <<std::endl;
      try
      {
         boost::property_tree::ptree::assoc_iterator it;
         it = line.second.find("id");
         if(it != line.second.not_found())
         {
            std::cout << "Id attribute not found" << std::endl;
         }
         else
         {
            std::cout << "Id attribute found" << std::endl;
         }

//         BOOST_FOREACH(boost::property_tree::ptree::value_type &w, line.second.get_child("<xmlattr>"))
//         {
//
//         }
      }
      catch (std::exception& e)
      {
         std::cout << "No attributes found." << std::endl;
         return true;
      }
   }
   else
   {
      return false;
   }
   return true;
}

bool SlsProgram::compile(void)
{
   if(this->m_RawProgram.empty())
   {
      std::cout << "No script is loaded." << std::endl;
      return false;
   }
   try
   {
      // TODO generate listing from xml file
      BOOST_FOREACH(boost::property_tree::ptree::value_type &v, this->m_RawProgram.get_child("sls_script"))
      {
         bool result = parseLine(v);
         if(false == result)
         {
            return result;
         }
      }
   }
   catch (std::exception& e)
   {
      return false;
   }
   return true;
}

bool SlsProgram::build(const char* path)
{
   bool result = false;
   result = this->load(path);
   if(false == result)
   {
      return result;
   }
   result = this->compile();
   if(false == result)
   {
      return result;
   }
   // TODO build program from compiled listing
   return result;
}

