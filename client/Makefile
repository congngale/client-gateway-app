#
# Copyright (c) 2019, Cong Nga Le. All rights reserved.
#
# This application used C++ version 11
#

#share source files
SHARE_SOURCE_FILES = $(shell find ../share/src -type f -name '*.cc')

# source files
SOURCE_FILES = $(shell find src -type f -name '*.cc')

# object files
OBJECT_FILES = $(shell find ../ -type f -name '*.o')

# MAC OS temp files
MAC_TEMP_FILES = $(shell find ../ -type f -name '._*')

# full sources
SOURCES = $(SOURCE_FILES) $(SHARE_SOURCE_FILES) client.cc

# object files
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))

# include inc folders
INCLUDE_DIRS = -Iinc -I../share/inc

# include -l
LDFLAGS = -ljson-c -lwiringPi -lcurl

# build flags
CXXFLAGS = -D_GLIBCXX_USE_C99=1 -std=c++11 -Wall -Werror -Wno-sign-compare -ggdb

# include -I
CPPFLAGS = $(INCLUDE_DIRS)

.PHONY: client clean

client: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJECTS) -o client $(LDFLAGS)

clean:
	@- $(RM) client
	@- $(RM) $(OBJECT_FILES)
	@- $(RM) $(MAC_TEMP_FILES)
