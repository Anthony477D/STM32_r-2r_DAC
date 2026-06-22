################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Application/DMA/DMA_process.c 

OBJS += \
./Core/Application/DMA/DMA_process.o 

C_DEPS += \
./Core/Application/DMA/DMA_process.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Application/DMA/%.o Core/Application/DMA/%.su Core/Application/DMA/%.cyclo: ../Core/Application/DMA/%.c Core/Application/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/Signal" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/DMA" -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/UART" -I../Core/Inc -I"/Users/antondzisenko/Documents/MyDocuments_workspace/STM_Project/SignalGenerator/Core/Application/App" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Application-2f-DMA

clean-Core-2f-Application-2f-DMA:
	-$(RM) ./Core/Application/DMA/DMA_process.cyclo ./Core/Application/DMA/DMA_process.d ./Core/Application/DMA/DMA_process.o ./Core/Application/DMA/DMA_process.su

.PHONY: clean-Core-2f-Application-2f-DMA

