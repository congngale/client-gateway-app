#
# Copyright (c) 2019, Cong Nga Le. All rights reserved.
#
# This application used C++ version 11
#

.PHONY: all clean client gateway clean_client clean_gateway

all: gateway client

client:
	$(MAKE) -C client

gateway:
	$(MAKE) -C gateway

clean: clean_client clean_gateway

clean_client:
	$(MAKE) clean -C client

clean_gateway:
	$(MAKE) clean -C gateway

