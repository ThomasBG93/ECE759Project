# Warnings
WFLAGS	:= -Wall -Wextra -Wsign-conversion -Wsign-compare -fopenmp -lstdc++

# Optimization and architecture
OPT		:= -O3
ARCH   	:= -march=native

# Language standard
CCSTD	:= -std=c99
CXXSTD	:= -std=c++11
CCX	:= g++
# Linker options
LDOPT 	:= $(OPT)
LDFLAGS := -fopenmp -lstdc++
BIN = "/usr/local/gcc/6.4.0/bin/gcc"
.DEFAULT_GOAL := all

CFLAGS  := -g
CXXFLAGS  := -g  

.PHONY: debug
debug : OPT  := -O0 -g -fno-omit-frame-pointer -fsanitize=address
debug : LDFLAGS := -fsanitize=address
debug : ARCH :=
debug : $(EXEC)

all : gen_file check spawn move main

%.o : %.c Makefile
	@ echo Compiling $<...
	$(CCX) $(CFLAGS) $(CXXSTD) $(WFLAGS) $(OPT) $(ARCH) -c $< -o $@
 
gen_file : input_file.o
	@ echo Building $@...
	@ $(CC) -o $@ $< $(LDFLAGS)
check : check.o
	@ echo Building $@...
	@ $(CC) -o $@ $< $(LDFLAGS)
move : movement.o
	@ echo Building $@...
	@ $(CC) -o $@ $< $(LDFLAGS)
spawn : spawn.o
	@ echo Building $@...
	@ $(CC) -o $@ $< $(LDFLAGS)
main : main.o
	@ echo Building $@...
	@ $(CC) -o $@ $< $(LDFLAGS)


.PHONY: clean
clean:
	rm -f *.o *.exe *.dat *.out
