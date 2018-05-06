# List of all the board related files.
TDA7468SRC = ${CHIBIOS}/projects/AUDIO_DAC_STM32F105RC/libraries/TDA7468/tda7468.c

# Required include directories
TDA7468INC = ${CHIBIOS}/projects/AUDIO_DAC_STM32F105RC/libraries/TDA7468

# Shared variables
ALLCSRC += $(TDA7468SRC)
ALLINC  += $(TDA7468INC)
