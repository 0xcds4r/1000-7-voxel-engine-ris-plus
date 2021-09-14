################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/gui/gui.cpp \
../src/gui/chat.cpp

OBJS += \
./src/gui/gui.o \
./src/gui/chat.o

CPP_DEPS += \
./src/gui/gui.d \
./src/gui/chat.d

# Each subdirectory must supply rules for building sources it contributes
src/gui/%.o: ../src/gui/%.cpp src/gui/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


