# Makefile

# DIR definitions
SRC_DIR=src
OBJ_DIR=obj
INC_DIR=include
DAT_DIR=data
BIN_DIR=bin

CXX            = g++

ifeq ($(DEBUG),y)
  DEBFLAGS = -O -g3 -D_GNULINUX
else
  DEBFLAGS = -O2 -D_UNIX_ -D_LINUX_
#  DEBFLAGS = -O2 -Wall -D_GNULINUX
endif

CFLAGS += $(DEBFLAGS)
CFLAGS += -I $(INC_DIR)

TARGET2 = $(BIN_DIR)/stereo_calibrage
TARGET1 = $(BIN_DIR)/mono_calibrage

SRC1 = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/calibrage.cpp \
       $(SRC_DIR)/common.cpp \
       $(SRC_DIR)/Chessboard.cpp \

SRC2 = $(SRC_DIR)/mainStereo.cpp \
       $(SRC_DIR)/calibrageStereo.cpp \
       $(SRC_DIR)/common.cpp \
       $(SRC_DIR)/Chessboard.cpp \

OBJS1:= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC1))
OBJS2:= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC2))

VISP_BUILD_DIR = /usr
VISP_CFLAGS    = `$(VISP_BUILD_DIR)/bin/visp-config --cflags`
VISP_LDFLAGS   = `$(VISP_BUILD_DIR)/bin/visp-config --libs`

BOOSTIP = -I/usr/include/boost
BOOSTLP = -lboost_filesystem -lboost_program_options -lboost_system

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) -c $(BOOSTIP) $(CFLAGS) $(VISP_CFLAGS) $^ -o $@ 

all: $(OBJS1) $(OBJS2)
	$(CXX) $(OBJS1) -o $(TARGET1) $(VISP_LDFLAGS) $(BOOSTLP)
	$(CXX) $(OBJS2) -o $(TARGET2) $(VISP_LDFLAGS) $(BOOSTLP)

clean:
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(OBJ_DIR)/*.o
	rm -f ./*~
	rm -f $(SRC_DIR)/*~
	rm -f $(INC_DIR)/*~

data-clean:
	rm -f $(DAT_DIR)/intrinsic/*.xml
	rm -f $(DAT_DIR)/extrinsic/*.xml
	rm -f $(DAT_DIR)/calibrationtables/*.txt
