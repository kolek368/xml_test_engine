/*
 * SlsProgram.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */
#include "SlsProgram.h"

SlsProgram::SlsProgram(const char* libPath) {
   // TODO Auto-generated constructor stub
   this->m_Stack = nullptr;
   this->m_ProgramReady = false;
   this->m_Libs.setPath(libPath);
}

SlsProgram::~SlsProgram() {
   // TODO Auto-generated destructor stub
   if(nullptr != this->m_Stack)
   {
      delete[] this->m_Stack;
   }
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

SLS_STATUS SlsProgram::createVariable(std::string Name, std::string Type, std::string Value)
{
   SLS_STATUS Status = SLS_OK;

   // create new variable only if it does not already exists
   if(NULL == this->m_Variables.find(Name))
   {
      if("Integer" == Type)
      {
         try {
            int64_t iValue = ("" == Value) ? 0 : std::stoi(Value, nullptr, 0);
            std::cout << "Creating Integer value: " << iValue << std::endl;
            this->m_Variables.insert( SlsVarPair(Name, new SlsInt(iValue) ));
         } catch (std::exception& e) {
            Status = SLS_INVALID_SYNTAX;
            std::cout << "ERROR: Invalid syntax while creating INTEGER with value: " << Value << std::endl;
         }
      }
      else if("String" == Type)
      {
         std::cout << "Adding String value: " << Value << " Length: " << Value.length() << std::endl;
         this->m_Variables.insert( SlsVarPair(Name, new SlsString( Value ) ));
      }
   }
   return Status;
}

bool SlsProgram::parseCall(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog)
{
   try
   {
      bool result = true;
      SlsResultEntity *resultLine = nullptr;
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
            else if("result" == child.first)
            {
               resultLine = new SlsResultEntity();
               std::string name = child.second.get<std::string>("<xmlattr>.name", "not found");
               std::string type = child.second.get<std::string>("<xmlattr>.type", "not found");
               this->createVariable(name, type, "");
               resultLine->addParam(name);
            }
            else
            {
               result = false;
               break;
            }
         }
         prog.push_back(programLine);
         if(nullptr != resultLine)
         {
            prog.push_back(resultLine);
         }
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

bool SlsProgram::parseSet(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog)
{
   try
   {
      std::string name = line.second.get<std::string>("<xmlattr>.name", "not found");
      std::string type = line.second.get<std::string>("<xmlattr>.type", "not found");
      for(auto &child : line.second)
      {
         if("<xmlattr>" == child.first)
         {
            continue;
         }
         else if("value" == child.first)
         {
            this->createVariable(name, type, child.second.data());
         }
         else if("add" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_ADD, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("sub" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_SUB, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("mul" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_MUL, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("div" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_DIV, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("mod" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_MOD, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("and" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_AND, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("or" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_OR, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("xor" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_XOR, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("shr" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_SHR, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
         else if("shl" == child.first)
         {
            SlsOperatorEntity *programLine = new SlsOperatorEntity();
            this->createVariable(name, type, "");
            programLine->addParam(SlsOperatorEntity::OPER_SHL, name, SlsVarDesc(SlsVar::Variable, child.second.data()));
            prog.push_back(programLine);
         }
      }
   }
   catch (std::exception& e)
   {
      std::cout << "No attributes found." << std::endl;
      return false;
   }
   return true;
}

bool SlsProgram::parseIf(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog)
{
   bool Retval = true;
   try
   {
      SlsIfEntity *programLine = new SlsIfEntity();
      std::cout << "Parsing IF statement." << std::endl;
      for(auto &child : line.second)
      {
         std::cout << "Child: " << child.first << std::endl;
         if("condition" == child.first)
         {
            std::cout << "Parsing CONDITION." << std::endl;
            for(auto &cond : child.second)
            {
               std::cout << "Child:" << cond.first << std::endl;
               if("more" == cond.first)
               {
                  std::cout << "Parsing MORE." << std::endl;
                  std::string lval = cond.second.get<std::string>("<xmlattr>.lvar", "not found");
                  std::string rval = cond.second.get<std::string>("<xmlattr>.rvar", "not found");
                  std::cout << "lval: " << lval << std::endl;
                  std::cout << "rval: " << rval << std::endl;
                  std::cout << "Parsing MORE finished." << std::endl;
               }
            }
            std::cout << "Parsing CONDITION finished." << std::endl;
         }
         else if("true" == child.first)
         {
            std::cout << "Parsing TRUE branch." << std::endl;
            BOOST_FOREACH(boost::property_tree::ptree::value_type &v, child.second)
            {
               std::cout << v.first.data() << std::endl;
               bool result = parseLine(v, programLine->getTrueFalse(true));
               if(false == result)
               {
                  Retval = false;
                  break;
               }
            }
            std::cout << "Parsing TRUE branch finished." << std::endl;
         }
         else if("false" == child.first)
         {
            std::cout << "Parsing FALSE branch." << std::endl;
            BOOST_FOREACH(boost::property_tree::ptree::value_type &v, child.second)
            {
               std::cout << v.first.data() << std::endl;
               bool result = parseLine(v, programLine->getTrueFalse(false));
               if(false == result)
               {
                  Retval = false;
                  break;
               }
            }
            std::cout << "Parsing FALSE branch finished." << std::endl;
         }
      }
      if(true == Retval)
      {
         prog.push_back(programLine);
      }
      else
      {
         delete programLine;
      }
      std::cout << "Parsing IF statement finished." << std::endl;
   }
   catch (std::exception& e)
   {
      std::cout << "Invalid IF statement syntax." << std::endl;
      Retval = false;
   }
   return Retval;
}

bool SlsProgram::parseLine(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog)
{
   bool Retval = true;
   if("call" == std::string(line.first.data()))
   {
      Retval = this->parseCall(line, prog);
   }
   else if("set" == std::string(line.first.data()))
   {
      Retval = this->parseSet(line, prog);
   }
   else if("if" == std::string(line.first.data()))
   {
      Retval = this->parseIf(line, prog);
   }
   else
   {
      Retval = false;
   }
   return Retval;
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

   this->m_Stack = new SlsStack[MAX_SLS_SCRIPT_STACK_SIZE];
   if(NULL == this->m_Stack)
   {
      return false;
   }

   try
   {
      BOOST_FOREACH(boost::property_tree::ptree::value_type &v, this->m_RawProgram.get_child("sls_script"))
      {
         bool result = parseLine(v, this->m_Program);
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
         entity->execute(this->m_Stack, this->m_Variables);
      }
   }
}
