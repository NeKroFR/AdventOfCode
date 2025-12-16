TOP_MODULE ?= top
VERILATOR ?= verilator
CFLAGS ?= -Wall -Wno-fatal
VERILATOR_FLAGS ?= --cc --exe --trace --sv --timing --top-module $(TOP_MODULE)

SV_FILES := $(wildcard *.sv *.vh)
SIM_EXE := obj_dir/V$(TOP_MODULE)

all: sim

sim: $(SIM_EXE)
	./$(SIM_EXE)

$(SIM_EXE): $(SV_FILES) main.cpp
	$(VERILATOR) $(CFLAGS) $(VERILATOR_FLAGS) \
		--exe main.cpp \
		$(SV_FILES)
	$(MAKE) -j -C obj_dir -f V$(TOP_MODULE).mk V$(TOP_MODULE)

wave: sim
	gtkwave wave.vcd &

clean:
	rm -rf obj_dir wave.vcd

.PHONY: all sim wave clean
