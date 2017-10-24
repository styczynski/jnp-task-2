all: ./bin ./bin/dict_test
	$(info Compilation done.)

./bin:
	@mkdir -p ./bin
	
./bin/dict.o: ./bin
	$(info Compiling dict module ...)
	@g++ -Wall -Wextra -O2 -std=c++17 -I ./src -c ./src/dict.cc -o ./bin/dict.o

./bin/dict_test: ./bin ./test/dict_test.cc ./bin/dict.o
	$(info Compile dict_test ...)
	@g++ -Wall -Wextra -O2 -std=c++17 -I ./src -c ./test/dict_test.cc -o ./bin/dict_test.o
	@g++ ./bin/dict.o ./bin/dict_test.o -o ./bin/dict_test
	
clean:
	@rm -r -f -d ./bin/**
	
rebuild: clean all

test: ./bin/dict_test
	@./bin/dict_test

.PHONY: all clean test
