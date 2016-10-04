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
   typedef enum _OPERATIONS {
      OPER_ADD = 0,
      OPER_SUB,
      OPER_MUL,
      OPER_DIV,
      OPER_MOD,
      OPER_AND,
      OPER_OR,
      OPER_XOR,
      OPER_SHL,
      OPER_SHR,
      OPER_MAX
   } OPERATIONS;

   SlsOperatorEntity() {
      this->m_Operation = OPER_MAX;
   };

   ~SlsOperatorEntity() {

   }

   void addParam(OPERATIONS Operation, std::string Lvalue, SlsVarDesc Rvalue) {
      if(this->isOperationValid(Operation)) {
         this->m_Operation = Operation;
         this->m_Lvalue = Lvalue;
         this->m_Rvalue = Rvalue;
      }
   }

   SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      SLS_STATUS Status = SLS_OK;
      switch (this->m_Operation) {
         case OPER_ADD:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.add(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_SUB:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.sub(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_MUL:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.mul(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_DIV:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.div(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_MOD:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.mod(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_AND:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.land(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_OR:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.lor(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_XOR:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.lxor(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_SHR:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.shr(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         case OPER_SHL:
            if(SlsVar::Variable == this->m_Rvalue.first) {
               Variables.shl(this->m_Lvalue, this->m_Rvalue.second);
            }
            else {
               Status = SLS_INVALID_TYPE;
            }
            break;
         default:
            Status = SLS_INVALID_KEY;
            break;
      }
      return Status;
   }

private:
   OPERATIONS m_Operation;
   std::string m_Lvalue;
   SlsVarDesc m_Rvalue;
   bool isOperationValid(OPERATIONS Operation) {
      if(OPER_MAX > Operation)
      {
         return true;
      }
      return false;
   }
};

#endif /* SLSSCRIPTENTITY_HPP_ */
