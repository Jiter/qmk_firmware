
SRC += jiter.c

ifeq ($(strip $(NEO2_ENABLE)), yes)
    OPT_DEFS += -DNEO2_ENABLE
endif
