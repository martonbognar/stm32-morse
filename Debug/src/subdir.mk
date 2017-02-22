################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/display_stm32.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/uart_custom.c 

OBJS += \
./src/display_stm32.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/uart_custom.o 

C_DEPS += \
./src/display_stm32.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/uart_custom.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F407VGTx -DSTM32F4 -DSTM32F4DISCOVERY -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40XX -DSTM32F40_41xxx -I"C:/Users/bogna/workspace/test/inc" -I"C:/Users/bogna/workspace/test/CMSIS/core" -I"C:/Users/bogna/workspace/test/CMSIS/device" -I"C:/Users/bogna/workspace/test/StdPeriph_Driver/inc" -I"C:/Users/bogna/workspace/test/Utilities" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


