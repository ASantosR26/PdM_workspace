################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f429xx.s 

OBJS += \
./Startup/startup_stm32f429xx.o 

S_DEPS += \
./Startup/startup_stm32f429xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/CMSIS/Include" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Inc" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/Core/Inc" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/API/Inc" -I"/home/alex/Documentos/CESE-UBA/programación de microprocesadores/PdM_workspace/TP_Final/Drivers/API/Src" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

