################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../compute_pi.c \
../main.c \
../watchdog.c 

OBJS += \
./compute_pi.o \
./main.o \
./watchdog.o 

C_DEPS += \
./compute_pi.d \
./main.d \
./watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -D_REENTRANT -D_POSIX_C_SOURCE=199309L -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


