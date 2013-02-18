# List targets defined in this file
TARGETS_SELF := cmake
# Exclude targets defined in this file
TARGETS_OTHER := $(filter-out $(TARGETS_SELF), $(MAKECMDGOALS))
 
# Call all targets using `Makefile` in build directory in one `make` command. It
# can depend on targets defined in this file, e.g., depending on a target to
# create the Makefile.
#
# If no targets are specified, use the dummy `all` target
$(or $(lastword $(TARGETS_OTHER)),all):
	$(MAKE) -C build $(TARGETS_OTHER)
.PHONY: $(TARGETS_OTHER) all
 
# Do nothing for all targets but last. Also quiet the message "Noting to be done on xxx"
$(filter-out $(lastword $(TARGETS_OTHER)), $(TARGETS_OTHER)):
	@cd .
 
cmake:
	cd build && cmake ../src
 
.PHONY: cmake
