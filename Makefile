#
# Copyright (c) 2019, Cong Nga Le. All rights reserved.
#
# This application used C++ version 11
#

.PHONY: all clean client server clean_client clean_server

all: client server

client:
	$(MAKE) -C client

server:
	$(MAKE) -C server

clean: clean_client clean_server

clean_client:
	$(MAKE) clean -C client

clean_server:
	$(MAKE) client -C server

