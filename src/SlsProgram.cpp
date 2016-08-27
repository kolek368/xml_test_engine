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
         std::cout<< v.first.data() << std::endl;
         try
         {
            BOOST_FOREACH(boost::property_tree::ptree::value_type &w, v.second.get_child("<xmlattr>"))
            {
               std::cout << "Attribute: " << w.first.data() << std::endl;
            }
         }
         catch (std::exception& e)
         {
            continue;
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

