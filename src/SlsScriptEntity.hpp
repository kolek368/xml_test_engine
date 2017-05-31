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
         else if("dword" == value.first)
         {
            try
            {
               uint32_t iValue = ("" == value.second) ? 0 : std::stoi(value.second);
               Stack->pushd(iValue);
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

class SlsResultEntity : public SlsScriptEntity {
public:
   SlsResultEntity() { };
   ~SlsResultEntity(){ };
   SLS_STATUS init(void) {
      return SLS_OK;
   };
   void addParam(std::string Name) {
      this->m_Name = Name;
   };
   SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      SLS_STATUS Status = SLS_OK;
      SlsVar *pVar = Variables.find(this->m_Name);
      if(NULL == pVar)
      {
         Status = SLS_PTR_ERROR;
      }
      else
      {
         switch (pVar->type()) {
            case SlsVar::Integer:
               Status = pVar->pop(Stack);
               break;
            default:
               break;
         }
      }
      return Status;
   };
private:
   std::string m_Name;
};

class SlsIfEntity : public SlsScriptEntity {
public:
   SlsIfEntity() {
      this->m_sCondition = "";
   };
   ~SlsIfEntity() { };

   std::vector<SlsScriptEntity *>& getTrueFalse(bool Branch) {
      if(Branch) {
         return this->m_True;
      }
      else {
         return this->m_False;
      }
   };

   SLS_STATUS execute(SlsStack *Stack, SlsVariables &Variables) {
      SLS_STATUS Status = SLS_OK;
      std::vector<SlsScriptEntity *> *path = NULL;
      if(this->checkCondition())
      {
         path = &this->m_True;
      }
      else
      {
         path = &this->m_False;
      }
      for(auto& entity : *path)
      {
         entity->execute(Stack, Variables);
      }
      return Status;
   }

   SLS_STATUS parse(boost::property_tree::ptree &iftree) {
      SLS_STATUS Status = SLS_OK;
      this->m_sCondition = "";
      for(auto& child : iftree)
      {
         if("<xmlattr>" == child.first)
         {
            continue;
         }
         if("condition" == child.first)
         {
            parseCondition(child.second);
         }
         else if("true" == child.first)
         {
            continue;
         }
         else if("false" == child.first)
         {
            continue;
         }
         else
         {
            Status = SLS_ERROR;
         }
      }
      return Status;
   }

   std::string toString(void) {
      return this->m_sCondition;
   }
private:
   typedef enum _COMPARE_OPRATOR {
      COMPARE_EQUAL = 0,
      COMPARE_NEQUAL,
      COMPARE_MORE,
      COMPARE_LESS,
      COMPARE_INVALID,
   } COMPARE_OPERATOR;
   class IfEntity {
      public:
         IfEntity() {
            this->m_Operator = COMPARE_INVALID;
            this->m_Left = NULL;
            this->m_Right = NULL;
         }
         ~IfEntity() {
            if(NULL != this->m_Left) delete this->m_Left;
            if(NULL != this->m_Right) delete this->m_Right;
            for(auto& entity : this->m_Nested)
            {
               delete entity;
            }
         }
         bool evaluate() {
            return true;
         }
      private:
         COMPARE_OPERATOR m_Operator;
         SlsVar* m_Left;
         SlsVar* m_Right;
         std::vector<IfEntity *> m_Nested;

   };
   bool checkCondition(void) {
      bool result = true;
      //TODO stub have to add checking condition of this if statement
      return result;
   }

   bool parseCompare(COMPARE_OPERATOR CompType, boost::property_tree::ptree &iftree)
   {
      bool result = true;
      int nvar = 0;
      const static char *CompOperator[] = {
            " == ",
            " != ",
            " > ",
            " < "
      };
      std::cout << "Parsing COMPARE statement" << std::endl;
      std::string lvar = iftree.get<std::string>("<xmlattr>.lvar", "");
      std::string lval = iftree.get<std::string>("<xmlattr>.lval", "");
      std::string rvar = iftree.get<std::string>("<xmlattr>.rvar", "");
      std::string rval = iftree.get<std::string>("<xmlattr>.rval", "");
      std::string *l;
      std::string *r;
      if("" != lvar)
      {
         l = &lvar;
         nvar += 1;
      }
      if("" != lval)
      {
         l = &lval;
         nvar += 1;
      }
      if("" != rvar)
      {
         r = &rvar;
         nvar += 1;
      }
      if("" != rval)
      {
         r = &rval;
         nvar += 1;
      }

      if(2 != nvar) {
         result = false;
      }
      else {
         this->m_sCondition += *l + CompOperator[CompType] + *r;
      }
      std::cout << "Parsing EQUAL statement finished." << std::endl;
      return result;
   }

   bool parseCondition(boost::property_tree::ptree &iftree) {
      bool result = true;
      std::cout << "Parsing CONDITION statement" << std::endl;
      for(auto& child : iftree) {
         if("equal" == child.first)
         {
            parseCompare(COMPARE_EQUAL, child.second);
         }
         else if("nequal" == child.first)
         {
            parseCompare(COMPARE_NEQUAL, child.second);
         }
         else if("more" == child.first)
         {
            parseCompare(COMPARE_MORE, child.second);
         }
         else if("less" == child.first)
         {
            parseCompare(COMPARE_LESS, child.second);
         }
      }
      std::cout << "Parsing CONDITION statement finished." << std::endl;
      return result;
   }

   std::vector<SlsScriptEntity *> m_True;
   std::vector<SlsScriptEntity *> m_False;
   std::string m_sCondition;
   IfEntity m_eCondition;
};

#endif /* SLSSCRIPTENTITY_HPP_ */
