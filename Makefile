# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0

ifeq ($(shell uname), Darwin)
PLATFORM=mac
else
PLATFORM=linux
endif

ifeq ($(TECHNOLOGY), teensy)
MAKE_PATH = teensy.mk
$(info TECHNOLOGY = teensy)
else
MAKE_PATH = sim.mk
$(info TECHNOLOGY = sim)
endif

include ${MAKE_PATH}
