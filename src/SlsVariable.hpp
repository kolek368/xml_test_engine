/*
 * SlsVariable.hpp
 *
 *  Created on: Sep 9, 2016
 *      Author: ares
 */

#ifndef SLSVARIABLE_HPP_
#define SLSVARIABLE_HPP_
#include <map>
#include <memory>
#include <string>

#include "SlsLibraryApi.hpp"

class SlsVar {
public:
   typedef enum _Type {
      Base = 0,
      Integer,
      Array,
      String,
   } Type;

   SlsVar() {
      this->m_Type = Base;
   }

   virtual ~SlsVar() {

   }

   Type type(void) {
      return this->m_Type;
   }

   virtual SLS_STATUS get(void) {
      return SLS_OK;
   }

   virtual SLS_STATUS push(SlsStack *Stack) {
      return SLS_OK;
   }

   virtual SLS_STATUS add(SlsVar* Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS sub(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS mul(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS div(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS mod(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS land(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS lor(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS lxor(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS shl(std::string Rvalue) {
      return SLS_OK;
   }

   virtual SLS_STATUS shr(std::string Rvalue) {
      return SLS_OK;
   }

   // ==
   virtual bool cmp_eq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // !=
   virtual bool cmp_neq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // >
   virtual bool cmp_b(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // >=
   virtual bool cmp_beq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // <
   virtual bool cmp_l(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // <=
   virtual bool cmp_leq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

protected:
   Type m_Type;
};

class SlsInt : public SlsVar{
public:
   SlsInt(int64_t Initial = 0) {
      this->m_Value = Initial;
      this->m_Type = SlsVar::Integer;
   }

   virtual ~SlsInt(void) {

   }

   SLS_STATUS get(int64_t *Value) {
      if(NULL == Value)
      {
         return SLS_PTR_ERROR;
      }
      *Value = this->m_Value;
      return SLS_OK;
   }


   SLS_STATUS add(SlsVar* Rvalue) {
      SLS_STATUS Status = SLS_OK;
      if(NULL == Rvalue)
      {
         Status = SLS_PTR_ERROR;
      }
      else
      {
         SlsInt* pInt = static_cast<SlsInt *>(Rvalue);
         this->m_Value += pInt->m_Value;
      }
      return Status;
   }

   SlsInt operator+(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value + Other.m_Value;
      return Ret;
   }

   SlsInt operator-(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value - Other.m_Value;
      return Ret;
   }

   SlsInt operator-(void) {
      SlsInt Ret;
      Ret.m_Value = -this->m_Value;
      return Ret;
   }

   SlsInt operator*(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value * Other.m_Value;
      return Ret;
   }

   SlsInt operator/(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value / Other.m_Value;
      return Ret;
   }

   SlsInt operator%(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value % Other.m_Value;
      return Ret;
   }

   SlsInt operator&(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value & Other.m_Value;
      return Ret;
   }

   SlsInt operator|(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value | Other.m_Value;
      return Ret;
   }

   SlsInt operator^(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value ^ Other.m_Value;
      return Ret;
   }

   SlsInt operator<<(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value << Other.m_Value;
      return Ret;
   }

   SlsInt operator>>(const SlsInt &Other) {
      SlsInt Ret;
      Ret.m_Value = this->m_Value >> Other.m_Value;
      return Ret;
   }

   bool operator==(const SlsInt &Other) {
      return (this->m_Value == Other.m_Value);
   }

   bool operator!=(const SlsInt &Other) {
      return (this->m_Value != Other.m_Value);
   }

   bool operator>(const SlsInt &Other) {
      return (this->m_Value > Other.m_Value);
   }

   bool operator>=(const SlsInt &Other) {
      return (this->m_Value >= Other.m_Value);
   }

   bool operator<(const SlsInt &Other) {
      return (this->m_Value < Other.m_Value);
   }

   bool operator<=(const SlsInt &Other) {
      return (this->m_Value <= Other.m_Value);
   }

   SlsInt& operator+=(const SlsInt &Other) {
      this->m_Value += Other.m_Value;
      return *this;
   }

   SlsInt& operator-=(const SlsInt &Other) {
      this->m_Value -= Other.m_Value;
      return *this;
   }

   SlsInt& operator*=(const SlsInt Other) {
      this->m_Value *= Other.m_Value;
      return *this;
   }

   SlsInt& operator/=(const SlsInt Other) {
      this->m_Value /= Other.m_Value;
      return *this;
   }

   SlsInt& operator%=(const SlsInt Other) {
      this->m_Value %= Other.m_Value;
      return *this;
   }

   SlsInt& operator&=(const SlsInt Other) {
      this->m_Value &= Other.m_Value;
      return *this;
   }

   SlsInt& operator|=(const SlsInt Other) {
      this->m_Value |= Other.m_Value;
      return *this;
   }

   SlsInt& operator^=(const SlsInt Other) {
      this->m_Value ^= Other.m_Value;
      return *this;
   }

   SlsInt& operator<<=(const SlsInt Other) {
      this->m_Value <<= Other.m_Value;
      return *this;
   }

   SlsInt& operator>>=(const SlsInt Other) {
      this->m_Value >>= Other.m_Value;
      return *this;
   }

private:
   int64_t m_Value;
};

class SlsArray : public SlsVar {
public:
   SlsArray(int64_t Size,  const uint8_t* Initial) {
      if(NULL == Initial)
      {
         SlsException e("NULL pointer exception");
         throw e;
      }
      for(int64_t i = 0; i < Size; i++)
      {
         this->m_Array[i] = ((uint8_t *)Initial)[i];
      }
      this->m_Size = Size;
      this->m_Type = SlsVar::Array;
   }

   ~SlsArray(void) {
   }

   SLS_STATUS get(int64_t *Size, uint8_t **Value)
   {
      if((NULL == Size) || (NULL == Value))
      {
         return SLS_PTR_ERROR;
      }
      *Size = this->m_Size;
      *Value = this->m_Array;
      return SLS_OK;
   }

private:
   int64_t m_Size = 0;
   uint8_t m_Array[1024];
};

class SlsString : public SlsVar {
public:
   SlsString(std::string& Initial) {
      this->m_String = Initial;
      this->m_Type = SlsVar::String;
   }

   ~SlsString(void) {

   }

   SLS_STATUS get(std::string* Value)
   {
      if(NULL == Value)
      {
         return SLS_PTR_ERROR;
      }
      *Value = this->m_String;
      return SLS_OK;
   }

   SLS_STATUS push(SlsStack* Stack) {
      SLS_STATUS Status = SLS_OK;
      try
      {
         Stack->pushn((uint8_t *)this->m_String.c_str(), this->m_String.length());
         Stack->pushw(static_cast<uint16_t>(this->m_String.length()));
      }
      catch(std::exception& e)
      {
         std::cout << "Error: " << e.what();
         Status = SLS_NO_MEMORY;
      }
      return Status;
   }

private:
   std::string m_String;
};

typedef std::map<std::string, SlsVar*> SlsVarContainer;
typedef std::pair<std::string, SlsVar*> SlsVarPair;
typedef std::pair<std::string, std::string> SlsVarDesc;

class SlsVariables {
public:
   SlsVariables(void) {

   }

   ~SlsVariables(void) {
      for(auto& Var : this->m_Variables) {
         delete Var.second;
      }
   }

   void insert(SlsVarPair Pair) {
      this->m_Variables[Pair.first] = Pair.second;
   }

   SlsVar* find(std::string Key) {
      if(this->m_Variables.find(Key) == this->m_Variables.end())
      {
         return NULL;
      }
      else
      {
         return this->m_Variables[Key];
      }
   }

   SLS_STATUS get(std::string Key, int64_t *Value)
   {
      SLS_STATUS Status = SLS_OK;
      SlsVar *pVar = this->m_Variables[Key];
      if(NULL == pVar)
      {
         Status = SLS_INVALID_KEY;
      }
      else if(SlsVar::Integer == pVar->type())
      {
         Status = static_cast<SlsInt*>(pVar)->get(Value);
      }
      else
      {
         Status = SLS_INVALID_TYPE;
      }
      return Status;
   }

   SLS_STATUS push(std::string Key, SlsStack *Stack) {
      SLS_STATUS Status = SLS_OK;
      this->m_Variables[Key]->push(Stack);
      return Status;
   }

   SLS_STATUS add(std::string Lvalue, std::string Rvalue) {
      SLS_STATUS Status = SLS_OK;
      SlsVar *pLval = this->find(Lvalue);
      SlsVar *pRval = this->find(Rvalue);
      if( (NULL ==pLval) || (NULL == pRval))
      {
         Status  = SLS_INVALID_KEY;
      }
      else if(pLval->type() != pRval->type())
      {
         Status = SLS_INVALID_TYPE;
      }
      else
      {
         pLval->add(pRval);
      }
      return Status;
   }

   SLS_STATUS sub(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS mul(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS div(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS mod(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS land(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS lor(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS lxor(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS shl(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   SLS_STATUS shr(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // ==
   bool cmp_eq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // !=
   bool cmp_neq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // >
   bool cmp_b(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // >=
   bool cmp_beq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // <
   bool cmp_l(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

   // <=
   bool cmp_leq(std::string Lvalue, std::string Rvalue) {
      return SLS_OK;
   }

private:
   SlsVarContainer m_Variables;
};

#endif /* SLSVARIABLE_HPP_ */
