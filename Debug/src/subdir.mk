################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SlsProgram.cpp \
../src/SlsProgramTest.cpp \
../src/SlsStackTest.cpp \
../src/xml_test_engine.cpp 

OBJS += \
./src/SlsProgram.o \
./src/SlsProgramTest.o \
./src/SlsStackTest.o \
./src/xml_test_engine.o 

CPP_DEPS += \
./src/SlsProgram.d \
./src/SlsProgramTest.d \
./src/SlsStackTest.d \
./src/xml_test_engine.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/ares/dev/googletest-master/googlemock/include -I/home/ares/dev/googletest-master/googlemock/gtest/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


