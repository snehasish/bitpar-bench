CXX=g++
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include

CXX_FLAG=-Iinclude
OPT_FLAG=-O3
LD_FLAG=


vpath %.C src
SRCS = driver.C bitop.C bitop-opt.C
OBJS = $(patsubst %.C,obj/%.o,$(SRCS)) 

all: bench
.PHONY: clean

$(OBJS): | obj

obj:
	@mkdir -p $@

obj/%.o : %.C
	$(CXX) $(CXX_FLAG) $(OPT_FLAG) -c $< -o $@

bench : $(OBJS) 
	$(CXX) $(OPT_FLAG) $(LD_FLAG) $^ -o $(BIN_DIR)/$@ 

clean:
	rm -f bin/bench obj/*
