# ASI2900 variant.

FROZEN_MANIFEST ?= $(VARIANT_DIR)/manifest.py

MICROPY_STANDALONE = 1

# Add ASI module
ASI2900_ROOT = ../../../..
HWIO = $(realpath ${ASI2900_ROOT}/audio_protocols/dante/hwio)
ASI2900_LIBS = $(ASI2900_ROOT)/subrepos
CFLAGS += -I$(ASI2900_ROOT)/audio_protocols/dante -DMICROPY_PY_ASI_HWIO=1
SRC_C += asi_hwio_mod.c

# Add hwio implementation
EDAPI_ROOT = $(ASI2900_LIBS)/audinate-embedded-dapi_aarch64-gnueabihf_linux
CFLAGS += -I$(ASI2900_LIBS) -I$(ASI2900_ROOT) -I$(EDAPI_ROOT)/include -DASI2900
CFLAGS += -Wno-ignored-qualifiers
SRC_C += $(HWIO)/hwioc_auddep.c \
		$(HWIO)/hwioc_conmon.c \
		$(HWIO)/hwio_conmon.c \
		$(HWIO)/meter_ballistics.c \
		$(HWIO)/dapi_simple_timer.c \
		$(HWIO)/asi_iyo_conmon_fns.c

LDFLAGS += -L$(EDAPI_ROOT)/lib -ledapi -ldns_sd -lstdc++

ifeq ($(MICROPY_PY_UBUS),1)
LIBUBUS_LDFLAGS := "-lubus"

CFLAGS += $(LIBUBUS_CFLAGS_MOD) -DMICROPY_PY_UBUS=1
LDFLAGS += $(LIBUBUS_LDFLAGS)
SRC_C += modubus.c
endif
