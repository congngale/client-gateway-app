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
SOURCES = $(SOURCE_FILES) client.cc

# object files
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))

# include inc folders
INCLUDE_DIRS = -Iinc 

# include -l
LDFLAGS =

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
