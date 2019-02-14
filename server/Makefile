#
# Copyright (c) 2019, Cong Nga Le. All rights reserved.
#
# This application used C++ version 11
#

# source files
SOURCE_FILES = $(shell find src -type f -name '*.cc')

# object files
OBJECT_FILES = $(shell find ./ -type f -name '*.o')

# full sources
SOURCES = $(SOURCE_FILES) server.cc

# object files
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))

# include inc folders
INCLUDE_DIRS = -Iinc 

# include -l
LDFLAGS = -lmosquittopp -lmosquitto

# build flags
CXXFLAGS = -D_GLIBCXX_USE_C99=1 -std=c++11 -Wall -Werror -Wno-sign-compare -ggdb

# include -I
CPPFLAGS = $(INCLUDE_DIRS)

.PHONY: server clean

server: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(OBJECTS) -o server $(LDFLAGS)

clean:
	@- $(RM) server
	@- $(RM) $(OBJECT_FILES)
