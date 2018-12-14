##############################
#    Sens'it SDK Makefile    #
##############################


# -----------
# SDK LIBRARY
# -----------
LIB_NAME = SENSIT_SDK_V2.0.0
LIB_PATH = lib


# --------------
# OUTPUT FOLDERS
# --------------
BIN_PATH = bin
OBJ_PATH = obj


# ------------
# OUTPUT FILES
# ------------
OUTPUT_NAME = sensit
MAP_OUTPUT  = $(OUTPUT_NAME).map
ELF_OUTPUT  = $(OUTPUT_NAME).elf
BIN_OUTPUT  = $(OUTPUT_NAME).bin
SIZE_OUTPUT = $(OUTPUT_NAME).siz


# ---------
# TOOLCHAIN
# ---------
TOOL_PATH =
CC        = $(TOOL_PATH)arm-none-eabi-gcc
BIN_TOOL  = $(TOOL_PATH)arm-none-eabi-objcopy
SIZE_TOOL = $(TOOL_PATH)arm-none-eabi-size


# -------------------
# COMPILATION OPTIONS
# -------------------
CC_OPT   = -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -g -Os -Wall -fmessage-length=0 -ffunction-sections
CC_INC   = -Iinc -Iinc/sensit -Iinc/sigfox -Iinc/resources -Iinc/radio -Iinc/sensors -Iinc/tools
CC_FLAGS = -DUART


# ---------------
# SOURCES FOLDERS
# ---------------
VPATH += \
src \
src/resources \
src/sensors \
src/radio \
src/tools


# ------------
# OBJECTS LIST
# ------------
OBJ_LIST = \
error.o \
button.o \
battery.o \
callback.o \
serial.o \
radio_api.o \
etsi.o \
fcc.o \
hts221.o \
ltr329.o \
fxos8700.o \
AT_parser.o \
AT_functions.o \
discovery.o

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_LIST))


# ------------
# LINK OPTIONS
# ------------
LD_OPT  = -L$(LIB_PATH) -T "LinkerScript.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Wl,-Map,"$(BIN_PATH)/$(MAP_OUTPUT)"


# -----------------
# COMPLETE BUILDING
# -----------------
all: clean dir $(OBJS) main bin

temperature: clean dir $(OBJS) main_TEMPERATURE bin
light: clean dir $(OBJS) main_LIGHT bin
vibration: clean dir $(OBJS) main_VIBRATION bin
magnet: clean dir $(OBJS) main_MAGNET bin
modem: clean dir $(OBJS) main_MODEM bin


# ----------------
# OBJECTS BUILDING
# ----------------
$(OBJ_PATH)/%.o: %.c
	@echo 'Building file: $@'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $@ $<
	@echo 'Finished building: $@'
	@echo ' '

main:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '

main_TEMPERATURE:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main_TEMPERATURE.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '

main_LIGHT:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main_LIGHT.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '

main_VIBRATION:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main_VIBRATION.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '

main_MAGNET:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main_MAGNET.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '

main_MODEM:
	@echo 'Building file: $(OBJ_PATH)/main.o'
	@echo 'Invoking: Cross ARM C Compiler'
	$(CC) $(CC_OPT) $(CC_FLAGS) $(CC_INC) -c -o $(OBJ_PATH)/main.o src/main_MODEM.c
	@echo 'Finished building: $(OBJ_PATH)/main.o'
	@echo ' '


# ------------------------
# ELF / BIN / SIZ BUILDING
# ------------------------
$(BIN_PATH)/$(ELF_OUTPUT):
	@echo 'Building target: $(ELF_OUTPUT)'
	@echo 'Invoking: Cross ARM C Linker'
	$(CC) $(CC_OPT) $(LD_OPT) -o $@ $(OBJS) $(OBJ_PATH)/main.o -l$(LIB_NAME)
	@echo 'Finished building: $(ELF_OUTPUT)'
	@echo ' '

$(BIN_PATH)/$(BIN_OUTPUT):
	@echo 'Building target: $(BIN_OUTPUT)'
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	$(BIN_TOOL) -O binary $(BIN_PATH)/$(ELF_OUTPUT) $@
	@echo 'Finished building: $(BIN_OUTPUT)'
	@echo ' '

$(BIN_PATH)/$(SIZE_OUTPUT):
	@echo 'Building target: $(SIZE_OUTPUT)'
	@echo 'Invoking: Cross ARM GNU Print Size'
	$(SIZE_TOOL) --format=berkeley "$(BIN_PATH)/$(ELF_OUTPUT)" > $@
	@cat $@
	@echo 'Finished building: $(SIZE_OUTPUT)'
	@echo ' '

bin: $(BIN_PATH)/$(ELF_OUTPUT) $(BIN_PATH)/$(BIN_OUTPUT) $(BIN_PATH)/$(SIZE_OUTPUT)


# -------------
# OTHER TARGETS
# -------------
clean:
	@echo 'Clean output folders'
	rm -rf $(BIN_PATH) $(OBJ_PATH)
	@echo ' '

dir:
	@echo 'Create output folders'
	mkdir -p $(BIN_PATH) $(OBJ_PATH)
	@echo ' '

# Rule for USB flashing using dfu file manager (vendor id 0483)
prog:
	dfu-util -a 0 -s 0x08000000:leave -D $(BIN_PATH)/$(BIN_OUTPUT)
