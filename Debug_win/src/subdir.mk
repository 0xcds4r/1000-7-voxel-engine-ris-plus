################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/voxel_engine.cpp \
../src/imgui_impl_glfw.cpp \
../src/imgui_impl_opengl3.cpp

OBJS += \
./src/voxel_engine.o \
./src/imgui_impl_glfw.o \
./src/imgui_impl_opengl3.o

CPP_DEPS += \
./src/voxel_engine.d \
./src/imgui_impl_glfw.d \
./src/imgui_impl_opengl3.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

