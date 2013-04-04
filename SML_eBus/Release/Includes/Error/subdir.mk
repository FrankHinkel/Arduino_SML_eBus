################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Includes/Error/error.cpp 

CPP_DEPS += \
./Includes/Error/error.cpp.d 

LINK_OBJ += \
./Includes/Error/error.cpp.o 


# Each subdirectory must supply rules for building sources it contributes
Includes/Error/error.cpp.o: ../Includes/Error/error.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/tools/avr/bin/avr-g++" -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=152    -I"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/arduino/avr/cores/arduino" -I"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/arduino/avr/variants/mega" -I"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/arduino/avr/libraries/Ethernet" -I"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/arduino/avr/libraries/Ethernet/utility" -I"/Applications/Arduino_1_5.app/Contents/Resources/Java/hardware/arduino/avr/libraries/SPI" -I"/Users/frank/Documents/Arduino/libraries/eBus" -I"/Users/frank/git/repository/SML_eBus/Includes/Error" -I"/Users/frank/Documents/Arduino/libraries/SML" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


