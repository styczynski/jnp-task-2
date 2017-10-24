all: ./dict_test
	$(info Compilation done.)

./dict_test: ./dict_test.cc
	$(info Compile dict_test.cc ...)
	@g++ -Wall -Wextra -O2 -std=c++17 dict_test.cc -o dict_test
	
clean:
	@rm -r -f -d ./dict_test
	
rebuild: clean all

test: ./dict_test
	@dict_test

.PHONY: all clean test
