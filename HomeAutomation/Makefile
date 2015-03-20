#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = HomeAutomation
#Set this to @ to keep the makefile quiet
SILENCE = 

#--- Inputs ----#
PROJECT_HOME_DIR = .
ifeq "$(CPPUTEST_HOME)" ""
    CPPUTEST_HOME = ../CppUTest
endif
CPP_PLATFORM = Gcc

SRC_DIRS = hoge \
    src\
    src/*

# to pick specific files (rather than directories) use this:    
SRC_FILES = 

TEST_SRC_DIRS = hoge \
    tests \
    tests/*

MOCKS_SRC_DIRS = hoge \
    mocks \

INCLUDE_DIRS =\
  .\
  include \
  include/* \
  $(CPPUTEST_HOME)/include/ \
  $(CPPUTEST_HOME)/include/Platforms/Gcc\
  mocks \
  tests/HomeAutomation

CPPUTEST_WARNINGFLAGS = -Wall -Werror -Wswitch-default 
CPPUTEST_WARNINGFLAGS += -Wconversion -Wswitch-enum 

include $(CPPUTEST_HOME)/build/MakefileWorker.mk

