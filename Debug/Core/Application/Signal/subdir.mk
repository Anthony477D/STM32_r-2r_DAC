################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/Signal/Combine_Signal.c \
../Core/Application/Signal/Signal_falling.c \
../Core/Application/Signal/Signal_hight.c \
../Core/Application/Signal/Signal_low.c \
../Core/Application/Signal/Signal_rising.c \
../Core/Application/Signal/Signal_sin.c 

OBJS += \
./Core/Application/Signal/Combine_Signal.o \
./Core/Application/Signal/Signal_falling.o \
./Core/Application/Signal/Signal_hight.o \
./Core/Application/Signal/Signal_low.o \
./Core/Application/Signal/Signal_rising.o \
./Core/Application/Signal/Signal_sin.o 

C_DEPS += \
./Core/Application/Signal/Combine_Signal.d \
./Core/Application/Signal/Signal_falling.d \
./Core/Application/Signal/Signal_hight.d \
./Core/Application/Signal/Signal_low.d \
./Core/Application/Signal/Signal_rising.d \
./Core/Application/Signal/Signal_sin.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/Signal/%.o Core/Application/Signal/%.su Core/Application/Signal/%.cyclo: ../Core/Application/Signal/%.c Core/Application/Signal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/Signal" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/DMA" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/UART" -I../Core/Inc -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Application-2f-Signal

clean-Core-2f-Application-2f-Signal:
	-$(RM) ./Core/Application/Signal/Combine_Signal.cyclo ./Core/Application/Signal/Combine_Signal.d ./Core/Application/Signal/Combine_Signal.o ./Core/Application/Signal/Combine_Signal.su ./Core/Application/Signal/Signal_falling.cyclo ./Core/Application/Signal/Signal_falling.d ./Core/Application/Signal/Signal_falling.o ./Core/Application/Signal/Signal_falling.su ./Core/Application/Signal/Signal_hight.cyclo ./Core/Application/Signal/Signal_hight.d ./Core/Application/Signal/Signal_hight.o ./Core/Application/Signal/Signal_hight.su ./Core/Application/Signal/Signal_low.cyclo ./Core/Application/Signal/Signal_low.d ./Core/Application/Signal/Signal_low.o ./Core/Application/Signal/Signal_low.su ./Core/Application/Signal/Signal_rising.cyclo ./Core/Application/Signal/Signal_rising.d ./Core/Application/Signal/Signal_rising.o ./Core/Application/Signal/Signal_rising.su ./Core/Application/Signal/Signal_sin.cyclo ./Core/Application/Signal/Signal_sin.d ./Core/Application/Signal/Signal_sin.o ./Core/Application/Signal/Signal_sin.su

.PHONY: clean-Core-2f-Application-2f-Signal

