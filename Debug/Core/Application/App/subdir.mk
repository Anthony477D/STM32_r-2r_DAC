################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/App/RunTime.c 

OBJS += \
./Core/Application/App/RunTime.o 

C_DEPS += \
./Core/Application/App/RunTime.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/App/%.o Core/Application/App/%.su Core/Application/App/%.cyclo: ../Core/Application/App/%.c Core/Application/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/Signal" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/DMA" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/UART" -I../Core/Inc -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Application-2f-App

clean-Core-2f-Application-2f-App:
	-$(RM) ./Core/Application/App/RunTime.cyclo ./Core/Application/App/RunTime.d ./Core/Application/App/RunTime.o ./Core/Application/App/RunTime.su

.PHONY: clean-Core-2f-Application-2f-App

