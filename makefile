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
file.o:
	$(CC) -c $(SRC_DIR)/file.c 		-o $(BUILD_DIR)/file.o 		$(ARGS)
functions.o:
	$(CC) -c $(SRC_DIR)/functions.c -o $(BUILD_DIR)/functions.o $(ARGS)
math.o:
	$(CC) -c $(SRC_DIR)/math.c 		-o $(BUILD_DIR)/math.o 		$(ARGS)
mem.o:
	$(CC) -c $(SRC_DIR)/mem.c 		-o $(BUILD_DIR)/mem.o 		$(ARGS)
option.o:
	$(CC) -c $(SRC_DIR)/option.c 	-o $(BUILD_DIR)/option.o 	$(ARGS)
panic.o:
	$(CC) -c $(SRC_DIR)/panic.c 	-o $(BUILD_DIR)/panic.o 	$(ARGS)
tostring.o:
	$(CC) -c $(SRC_DIR)/tostring.c 	-o $(BUILD_DIR)/tostring.o 	$(ARGS)
vector.o:
	$(CC) -c $(SRC_DIR)/vector.c 	-o $(BUILD_DIR)/vector.o 	$(ARGS)

#	GENERAL
all: file.o functions.o math.o mem.o option.o panic.o tostring.o vector.o
	$(AR) rcs $(LIB_RESULT) $(BUILD_DIR)/file.o $(BUILD_DIR)/functions.o $(BUILD_DIR)/math.o $(BUILD_DIR)/mem.o $(BUILD_DIR)/option.o $(BUILD_DIR)/panic.o $(BUILD_DIR)/tostring.o $(BUILD_DIR)/vector.o
	$(CP) $(SRC_DIR)/*.h $(RESULT_INC_DIR)

test: all
	$(CC) $(TEST_SRC)/main.c -o $(BUILD_DIR)/test.app $(ARGS) -I$(RESULT_INC_DIR) -L$(RESULT_BIN_DIR) -lvxutils
	$(BUILD_DIR)/test.app