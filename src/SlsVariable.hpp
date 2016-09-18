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

class SlsInt {
public:
   SlsInt(int64_t Initial = 0) {
      this->m_Value = Initial;
   }

   SLS_STATUS get(int64_t *Value) {
      if(NULL == Value)
      {
         return SLS_PTR_ERROR;
      }
      *Value = this->m_Value;
      return SLS_OK;
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

class SlsArray : public SlsInt{
public:
   SlsArray(int64_t Size, uint8_t* Initial = NULL) {
      if(NULL == Initial)
      {
         SlsException e("NULL pointer exception");
         throw e;
      }
      this->m_Value.reset(new uint8_t(Size));
      for(int64_t i = 0; i < Size; i++)
      {
         this->m_Value.get()[i] = Initial[i];
      }
      this->m_Size = Size;
   }

   SLS_STATUS get(int64_t *Size, uint8_t **Value)
   {
      if((NULL == Size) || (NULL == Value))
      {
         return SLS_PTR_ERROR;
      }
      *Size = this->m_Size;
      *Value = this->m_Value.get();
      return SLS_OK;
   }

private:
   int64_t m_Size;
   std::shared_ptr<uint8_t> m_Value;
};

typedef std::map<std::string, std::shared_ptr<SlsInt>> SlsVarContainer;
typedef std::pair<std::string, std::shared_ptr<SlsInt>> SlsVar;

#endif /* SLSVARIABLE_HPP_ */
