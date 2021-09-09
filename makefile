#	VX_UTILS MAKEFILE
#	CREATED BY VICIX
#
#	Usage:
#		Debug: `make PROFILE=DEBUG all`
#		Release: `make PROFILE=RELEASE all` or `make all` 

#	VARIABLES
CC 			= gcc
AR			= ar
CP			= cp -u

SRC_DIR 	= src
BUILD_DIR 	= build/temp
RESULT_INC_DIR = build/includes
RESULT_BIN_DIR = build/bin
LIB_NAME 	= libvxutils.a
LIB_RESULT  = $(RESULT_BIN_DIR)/$(LIB_NAME)
TEST_SRC	= test

#	DEBUG, RELEASE
PROFILE	  	= RELEASE

INCLUDES 	= 
LIBS 		= 

#	CHECK PROFILE
ifeq ($(PROFILE), DEBUG)
ARGS      	= -Wall -std=c99 -g -O0 -D_DEBUG $(LIBS) $(INCLUDES)
else
ifeq ($(PROFILE), RELEASE)
ARGS	  	= -Wall -std=c99 -O3 -D_RELEASE $(LIBS) $(INCLUDES)
else
$(error Invalid profile: the profile must be set to RELEASE or DEBUG)
endif
endif

_: all

#	FILES
vx_file.o:
	$(CC) -c $(SRC_DIR)/vx_file.c 		-o $(BUILD_DIR)/vx_file.o 		$(ARGS)
vx_functions.o:
	$(CC) -c $(SRC_DIR)/vx_functions.c 	-o $(BUILD_DIR)/vx_functions.o 	$(ARGS)
vx_math.o:
	$(CC) -c $(SRC_DIR)/vx_math.c 		-o $(BUILD_DIR)/vx_math.o 		$(ARGS)
vx_mem.o:
	$(CC) -c $(SRC_DIR)/vx_mem.c 		-o $(BUILD_DIR)/vx_mem.o 		$(ARGS)
vx_option.o:
	$(CC) -c $(SRC_DIR)/vx_option.c 	-o $(BUILD_DIR)/vx_option.o 	$(ARGS)
vx_panic.o:
	$(CC) -c $(SRC_DIR)/vx_panic.c 		-o $(BUILD_DIR)/vx_panic.o 		$(ARGS)
vx_tostring.o:
	$(CC) -c $(SRC_DIR)/vx_tostring.c 	-o $(BUILD_DIR)/vx_tostring.o 	$(ARGS)
vx_vector.o:
	$(CC) -c $(SRC_DIR)/vx_vector.c 	-o $(BUILD_DIR)/vx_vector.o 	$(ARGS)

#	GENERAL
all: vx_file.o vx_functions.o vx_math.o vx_mem.o vx_option.o vx_panic.o vx_tostring.o vx_vector.o
	$(AR) rcs $(LIB_RESULT) $(BUILD_DIR)/vx_file.o $(BUILD_DIR)/vx_functions.o $(BUILD_DIR)/vx_math.o $(BUILD_DIR)/vx_mem.o $(BUILD_DIR)/vx_option.o $(BUILD_DIR)/vx_panic.o $(BUILD_DIR)/vx_tostring.o $(BUILD_DIR)/vx_vector.o
	$(CP) $(SRC_DIR)/*.h $(RESULT_INC_DIR)

test: all
	$(CC) $(TEST_SRC)/main.c -o $(BUILD_DIR)/test.app $(ARGS) -I$(RESULT_INC_DIR) -L$(RESULT_BIN_DIR) -lvxutils
	$(BUILD_DIR)/test.app