CXX=g++-4.8
BIN_DIR=bin
SRC_DIR=src
INC_DIR=include

CXX_FLAG=-I$(INC_DIR) 
OPT_FLAG=-O3
LD_FLAG=

vpath %.C src
SRCS = bitop.C bitop-opt.C 
OBJS = $(patsubst %.C,obj/%.o,$(SRCS)) 

all: bench analyses
.PHONY: clean

$(OBJS): | obj

obj:
	@mkdir -p $@

obj/%.o : %.C
	$(CXX) $(CXX_FLAG) $(OPT_FLAG) -c $< -o $@

bench : $(OBJS) obj/driver.o 
	$(CXX) $(CXX_FLAG) $(OPT_FLAG) $(LD_FLAG) $^ -o $(BIN_DIR)/$@ 

analyses : $(OBJS) obj/driver-analyses.o 
	$(CXX) $(CXX_FLAG) $(OPT_FLAG) $(LD_FLAG) $^ -o $(BIN_DIR)/$@ 

clean:
	rm -f bin/bench obj/*
