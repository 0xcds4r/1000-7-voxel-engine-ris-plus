################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/voxels/Block.cpp \
../src/voxels/Chunk.cpp \
../src/voxels/Chunks.cpp \
../src/voxels/Level.cpp \
../src/voxels/Blocks.cpp \
../src/voxels/Items.cpp \
../src/voxels/TimeCycle.cpp \
../src/voxels/WorldGenerator.cpp \
../src/voxels/voxel.cpp 

OBJS += \
./src/voxels/Block.o \
./src/voxels/Chunk.o \
./src/voxels/Chunks.o \
./src/voxels/Level.o \
./src/voxels/Blocks.o \
./src/voxels/Items.o \
./src/voxels/TimeCycle.o \
./src/voxels/WorldGenerator.o \
./src/voxels/voxel.o 

CPP_DEPS += \
./src/voxels/Block.d \
./src/voxels/Chunk.d \
./src/voxels/Chunks.d \
./src/voxels/WorldGenerator.d \
./src/voxels/Level.d \
./src/voxels/Blocks.d \
./src/voxels/Items.d \
./src/voxels/TimeCycle.d \
./src/voxels/voxel.d 


# Each subdirectory must supply rules for building sources it contributes
src/voxels/%.o: ../src/voxels/%.cpp src/voxels/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


