################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/RC522.c \
../Core/Src/gate_control.c \
../Core/Src/log_history.c \
../Core/Src/main.c \
../Core/Src/menu_lcd.c \
../Core/Src/pcf8574.c \
../Core/Src/rfid_handler.c \
../Core/Src/rfid_logic.c \
../Core/Src/scheduler.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c 

OBJS += \
./Core/Src/RC522.o \
./Core/Src/gate_control.o \
./Core/Src/log_history.o \
./Core/Src/main.o \
./Core/Src/menu_lcd.o \
./Core/Src/pcf8574.o \
./Core/Src/rfid_handler.o \
./Core/Src/rfid_logic.o \
./Core/Src/scheduler.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o 

C_DEPS += \
./Core/Src/RC522.d \
./Core/Src/gate_control.d \
./Core/Src/log_history.d \
./Core/Src/main.d \
./Core/Src/menu_lcd.d \
./Core/Src/pcf8574.d \
./Core/Src/rfid_handler.d \
./Core/Src/rfid_logic.d \
./Core/Src/scheduler.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -DUSE_NUCLEO_64 -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32G4xx_Nucleo -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/RC522.cyclo ./Core/Src/RC522.d ./Core/Src/RC522.o ./Core/Src/RC522.su ./Core/Src/gate_control.cyclo ./Core/Src/gate_control.d ./Core/Src/gate_control.o ./Core/Src/gate_control.su ./Core/Src/log_history.cyclo ./Core/Src/log_history.d ./Core/Src/log_history.o ./Core/Src/log_history.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/menu_lcd.cyclo ./Core/Src/menu_lcd.d ./Core/Src/menu_lcd.o ./Core/Src/menu_lcd.su ./Core/Src/pcf8574.cyclo ./Core/Src/pcf8574.d ./Core/Src/pcf8574.o ./Core/Src/pcf8574.su ./Core/Src/rfid_handler.cyclo ./Core/Src/rfid_handler.d ./Core/Src/rfid_handler.o ./Core/Src/rfid_handler.su ./Core/Src/rfid_logic.cyclo ./Core/Src/rfid_logic.d ./Core/Src/rfid_logic.o ./Core/Src/rfid_logic.su ./Core/Src/scheduler.cyclo ./Core/Src/scheduler.d ./Core/Src/scheduler.o ./Core/Src/scheduler.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su

.PHONY: clean-Core-2f-Src

