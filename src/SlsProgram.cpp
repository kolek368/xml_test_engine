/*
 * SlsProgram.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */
#include "SlsProgram.h"

SlsProgram::SlsProgram(const char* libPath) {
   // TODO Auto-generated constructor stub
   this->m_ProgramReady = false;
   this->m_Libs.setPath(libPath);
}

SlsProgram::~SlsProgram() {
   // TODO Auto-generated destructor stub
   for(auto& entity : this->m_Program)
   {
      delete entity;
   }
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

bool SlsProgram::parseCall(boost::property_tree::ptree::value_type &line)
{
   try
   {
      bool result = true;
      SlsCallEntity *programLine = new SlsCallEntity;
      std::string lib = line.second.get<std::string>("<xmlattr>.lib", "not found");
      std::string fun = line.second.get<std::string>("<xmlattr>.function", "not found");

      if(0 == this->m_Libs.m_LoadedLibs.count(lib))
      {
         std::cout << "Unknown library: " << lib << std::endl;
         result = false;
      }
      else if(0 == this->m_Libs.m_LoadedLibs[lib].count(fun))
      {
         std::cout << "Function: " << fun << " not found in " << lib << " library." << std::endl;
         result = false;
      }
      else
      {
         std::cout << "lib: " << lib << " - function: " << fun << std::endl;
         programLine->addParam(this->m_Libs.m_LoadedLibs[lib][fun]);

         for(auto &child : line.second)
         {
            if("<xmlattr>" == std::string(child.first.data()))
               continue;

            if("param" == std::string(child.first.data()))
            {
               SlsFunParam param(child.second.get<std::string>("<xmlattr>.type", "not found"),  // type of data
                                 child.second.data());                                          // data in string
               programLine->addParam(param);
            }
            else
            {
               result = false;
               break;
            }
         }
         this->m_Program.push_back(programLine);
      }
      if(false == result)
      {
         delete programLine;
      }
   }
   catch (std::exception& e)
   {
      std::cout << "No attributes found." << std::endl;
      return true;
   }
   return true;
}

bool SlsProgram::parseSet(boost::property_tree::ptree::value_type &line)
{
   try
   {
      std::string name = line.second.get<std::string>("<xmlattr>.name", "not found");
      std::string type = line.second.get<std::string>("<xmlattr>.type", "not found");
      std::string value;
      for(auto &child : line.second)
      {
         if("<xmlattr>" == std::string(child.first.data()))
         {
            continue;
         }
         else if("value" == std::string(child.first.data()))
         {
            value = child.second.data();
         }
      }

      std::cout << "Varable: " << name << " Type: " << type << " Value: " << value << std::endl;
      if("Integer" == type)
      {
         int64_t iValue = std::stoi(value);
         std::cout << iValue << std::endl;
         this->m_Variables.insert( SlsVar(name, std::shared_ptr<SlsInt>(new SlsInt(iValue))) );
      }
   }
   catch (std::exception& e)
   {
      std::cout << "No attributes found." << std::endl;
      return false;
   }
   return true;
}

bool SlsProgram::parseLine(boost::property_tree::ptree::value_type &line)
{
   if("call" == std::string(line.first.data()))
   {
      return this->parseCall(line);
   }
   else if("set" == std::string(line.first.data()))
   {
      return this->parseSet(line);
   }
   else
   {
      return false;
   }
   return true;
}

bool SlsProgram::compile(void)
{
   SLS_STATUS status = SLS_OK;

   status = this->m_Libs.loadLibs();
   if(SLS_OK != status)
   {
      return false;
   }

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
   SLS_STATUS status = SLS_OK;
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


   for(auto& entity : this->m_Program)
   {
      status = entity->init();
      if(SLS_OK != status)
      {
         result = false;
         break;
      }
   }

   if(true == result)
   {
      this->m_ProgramReady = true;
   }

   return result;
}

void SlsProgram::run(void)
{
   if(true == this->m_ProgramReady)
   {
      for(auto& entity : this->m_Program)
      {
         entity->execute();
      }
   }
}
