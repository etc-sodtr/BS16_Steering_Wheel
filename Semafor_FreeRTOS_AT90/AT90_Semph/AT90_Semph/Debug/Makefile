################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include \
../source


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../include/lcd_lib.c \
../include/LED.c \
../source/heap_1.c \
../source/list.c \
../source/main.c \
../source/port.c \
../source/queue.c \
../source/tasks.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
include/lcd_lib.o \
include/LED.o \
source/heap_1.o \
source/list.o \
source/main.o \
source/port.o \
source/queue.o \
source/tasks.o

OBJS_AS_ARGS +=  \
include/lcd_lib.o \
include/LED.o \
source/heap_1.o \
source/list.o \
source/main.o \
source/port.o \
source/queue.o \
source/tasks.o

C_DEPS +=  \
include/lcd_lib.d \
include/LED.d \
source/heap_1.d \
source/list.d \
source/main.d \
source/port.d \
source/queue.d \
source/tasks.d

C_DEPS_AS_ARGS +=  \
include/lcd_lib.d \
include/LED.d \
source/heap_1.d \
source/list.d \
source/main.d \
source/port.d \
source/queue.d \
source/tasks.d

OUTPUT_FILE_PATH +=AT90_Semph.elf

OUTPUT_FILE_PATH_AS_ARGS +=AT90_Semph.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler

















include/%.o: ../include/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=at90can32 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\at90can32" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

source/%.o: ../source/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=at90can32 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\at90can32" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="AT90_Semph.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=at90can32 -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.1.130\gcc\dev\at90can32"  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "AT90_Semph.elf" "AT90_Semph.hex"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "AT90_Semph.elf" "AT90_Semph.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "AT90_Semph.elf" > "AT90_Semph.lss"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "AT90_Semph.elf" "AT90_Semph.srec"
	"C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "AT90_Semph.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "AT90_Semph.elf" "AT90_Semph.a" "AT90_Semph.hex" "AT90_Semph.lss" "AT90_Semph.eep" "AT90_Semph.map" "AT90_Semph.srec" "AT90_Semph.usersignatures"
	