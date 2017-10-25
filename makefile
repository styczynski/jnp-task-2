
#########################################

EXAMPLES_LOCATIONS := $(wildcard ./examples/**)
EXAMPLES := $(foreach location,$(EXAMPLES_LOCATIONS),$(shell basename $(location)))
EXAMPLES_FILE_NAMES := $(EXAMPLES)
EXAMPLES_DIRS := $(addprefix ./examples/,$(addsuffix /,$(EXAMPLES)))
EXAMPLES_OUT_FILES := $(addprefix ./bin/,$(EXAMPLES_FILE_NAMES))
EXAMPLES_RUN_CMDS := $(addprefix run-,$(EXAMPLES))
EXAMPLES_RUN_CMDS := $(foreach runcmd,$(EXAMPLES_LOCATIONS),$(shell echo $(runcmd) | tr '_' '-'))

# Print help information
help:
	$(info Use the following targets:)
	$(info )
	$(info    all - to build all executables)
	$(info    [name] - to compile only one given problem)
	$(info )
	$(info    clean - to remove the compilation files)
	$(info )
	$(info    run-[name] - to run exact executable. Available executions are:)
	$(foreach problem,$(EXAMPLES),$(info        run-$(shell echo $(problem) | tr '_' '-')))
	$(info )
	
# Build all examples
all: $(EXAMPLES_OUT_FILES)
	$(info [MAKE] Compilation done.)

# Clean all compilation files
clean:
	$(shell rm -r -f -d ./bin/**)

./bin:
	@mkdir -p ./bin
	
./bin/dict.o: ./bin
	$(info [MAKE] Compiling DICT module ...)
	@g++ -Wall -Wextra -O2 -std=c++17 -I ./src -c ./src/dict.cc -o ./bin/dict.o

./bin/dictglobal.o: ./bin
	$(info [MAKE] Compiling DICTGLOBAL module ...)
	@g++ -Wall -Wextra -O2 -std=c++17 -I ./src -c ./src/dictglobal.cc -o ./bin/dictglobal.o
	
# Template to generate
# ./problem/[name]/[name] targets
# that compiles sources to executables
define compilation_template


ifeq ($(wildcard ./examples/$(1)/$(1).cc),) 

$(shell echo $(1) | tr '_' '-'): ./bin/$(1)
	$$(info [MAKE] Single problem compiled.)

./bin/$(1).o: ./bin ./examples/$(1)/$(1).c
	$$(info [MAKE] Compiling problem $(shell echo $(1) | tr '[:lower:]' '[:upper:]')... (GCC) )
	$$(shell gcc -c ./examples/$(1)/$(1).c -I ./src -o ./bin/$(1).o -O2 -Wall -Wextra)

./bin/$(1): ./bin ./bin/$(1).o ./bin/dict.o ./bin/dictglobal.o
	$$(info [MAKE] Linking problem $(shell echo $(1) | tr '[:lower:]' '[:upper:]')... )
	$$(shell g++ ./bin/dict.o ./bin/dictglobal.o ./bin/$(1).o -o ./bin/$(1))
 
else 

    $(shell echo $(1) | tr '_' '-'): ./bin/$(1)
	$$(info [MAKE] Single problem compiled.)

./bin/$(1).o: ./bin ./examples/$(1)/$(1).cc
	$$(info [MAKE] Compiling problem $(shell echo $(1) | tr '[:lower:]' '[:upper:]')... (G++) )
	$$(shell g++ -c ./examples/$(1)/$(1).cc -I ./src -o ./bin/$(1).o -O2 -Wall -Wextra -std=c++17)

./bin/$(1): ./bin ./bin/$(1).o ./bin/dict.o ./bin/dictglobal.o
	$$(info [MAKE] Linking problem $(shell echo $(1) | tr '[:lower:]' '[:upper:]')... )
	$$(shell g++ ./bin/dict.o ./bin/dictglobal.o ./bin/$(1).o -o ./bin/$(1))

endif

endef

# Template to generate
# run-[problem] targets
# and [problem] targets
# that runs compiled executable
define run_template

run-$(shell echo $(1) | tr '_' '-'): ./bin ./bin/$(1)
	$$(info [MAKE] Running problem $(shell echo $(1) | tr '[:lower:]' '[:upper:]')...)
	$$(info $$(shell ./bin/$(1)))
	$$(info [MAKE] Program exited.)

endef

# Generate all the templates
$(foreach problem, $(EXAMPLES), $(eval $(call run_template,$(problem))))
$(foreach problem_path, $(EXAMPLES), $(eval $(call compilation_template,$(problem_path))))

.PHONY: all help clean $(EXAMPLES_RUN_CMDS)
