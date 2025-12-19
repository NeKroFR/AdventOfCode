#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <iostream>
#include <fstream>

using namespace std;


auto parse = [](ifstream& in) -> vector<string> {
    vector<string> lines;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
    }
    in.close();    
    return lines;
};

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");

    // Read input.txt
    vector<string> lines;
    ifstream infile("../input.txt");
    if (!infile) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }

    lines = parse(infile);
    
    
    // Simulation setup
    top->clk = 0;
    top->rst = 1;
    top->valid = 0;
    top->direction = 0;
    top->distance = 0;
    vluint64_t time = 0;

    // Initial eval
    top->eval();
    tfp->dump(time++);

    // RESET
    for (int i = 0; i < 8; ++i) {
        top->clk = !top->clk;
        top->eval();
        tfp->dump(time++);
    }
    top->rst = 0;

    // Apply on posedge
    for (const auto& l : lines) {
        top->valid = 1;
        top->clk = 1;
        top->eval();
        tfp->dump(time++);
        top->clk = 0;
        top->eval();
        tfp->dump(time++);
        top->valid = 0;
    }

    // Print result
    cout << top->count << endl;
    tfp->close();
    delete tfp;
    delete top;
    return 0;
}
