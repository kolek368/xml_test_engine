/*
 * SlsScriptEntity.h
 *
 *  Created on: Sep 1, 2016
 *      Author: ares
 */

#ifndef SLSSCRIPTENTITY_HPP_
#define SLSSCRIPTENTITY_HPP_
#include <vector>
#include "SlsLibraryApi.hpp"
#include "SlsVariable.hpp"

#define MAX_SLS_SCRIPT_STACK_SIZE   256

class SlsScriptEntity {
public:
   SlsScriptEntity() { };
   virtual ~SlsScriptEntity(){ };
   virtual SLS_STATUS init(void) {
      return SLS_OK;
   };
   virtual void addParam(void) {};
   virtual SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      return SLS_OK;
   };
};

class SlsCallEntity : public SlsScriptEntity {
public:
   ~SlsCallEntity() {

   }

   void addParam(SlsFunParam &param) {
      this->m_Params.push_back(param);
   }

   void addParam(sls_lib_function fun) {
      this->m_Fun = fun;
   }

   SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      if(NULL == Stack)
      {
         return SLS_PTR_ERROR;
      }

      for(auto const& value: this->m_Params)
      {
         if("string" == value.first)
         {
            try
            {
               uint16_t stringLen = (uint16_t)value.second.length();
               Stack->pushn((uint8_t *)value.second.c_str(), value.second.length());
               Stack->pushw(stringLen);
            }
            catch(SlsException& e)
            {
               return SLS_ERROR;
            }
         }
         else if("var" == value.first)
         {
            SLS_STATUS Status = Variables.push(value.second, Stack);
            if(SLS_OK != Status) {
               return SLS_ERROR;
            }
         }
      }
      this->m_Fun(Stack);
      return SLS_OK;
   };
private:
   std::vector<SlsFunParam> m_Params;
   sls_lib_function m_Fun = NULL;
};

class SlsOperatorEntity : public SlsScriptEntity {
public:
   SlsOperatorEntity() {

   };

   ~SlsOperatorEntity() {

   }

   void addParam(std::string Operation, std::string Lvalue, SlsVarDesc Rvalue) {
      if(this->isOperationValid(Operation)) {
         this->m_Operation = Operation;
         this->m_Lvalue = Lvalue;
         this->m_Rvalue = Rvalue;
      }
   }

   SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      SLS_STATUS Status = SLS_OK;
      if("add" == this->m_Operation) {
         if("var" == this->m_Rvalue.first) {
            Variables.add(this->m_Lvalue, this->m_Rvalue.second);
         }
         else {
            Status = SLS_INVALID_TYPE;
         }
      }
      else {
         Status = SLS_INVALID_KEY;
      }
      return Status;
   }

private:
   std::string m_Operation;
   std::string m_Lvalue;
   SlsVarDesc m_Rvalue;
   const std::string m_SupportedOperations[1] = { "add"};
   bool isOperationValid(std::string Operation) {
      for(auto &oper : this->m_SupportedOperations) {
         if(oper == Operation) {
            return true;
         }
      }
      return false;
   }
};

#endif /* SLSSCRIPTENTITY_HPP_ */
