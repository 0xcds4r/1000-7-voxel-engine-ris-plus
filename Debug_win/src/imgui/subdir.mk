################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/imgui/imgui.cpp \
../src/imgui/imgui_draw.cpp \
../src/imgui/imgui_tables.cpp \
../src/imgui/imgui_widgets.cpp

OBJS += \
./src/imgui/imgui.o \
./src/imgui/imgui_draw.o \
./src/imgui/imgui_tables.o \
./src/imgui/imgui_widgets.o

CPP_DEPS += \
./src/imgui/imgui.d \
./src/imgui/imgui_draw.d \
./src/imgui/imgui_tables.d \
./src/imgui/imgui_widgets.d


# Each subdirectory must supply rules for building sources it contributes
src/imgui/%.o: ../src/imgui/%.cpp src/imgui/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


