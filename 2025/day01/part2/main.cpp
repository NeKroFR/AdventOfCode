#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <iostream>
#include <fstream>

using namespace std;

auto parse = [](ifstream& in) -> vector<pair<bool,uint32_t>> {
    vector<pair<bool,uint32_t>> out;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        char dir_char = line[0];
        string dist_str = line.substr(1);
        int dist = stoi(dist_str);
        out.emplace_back(dir_char == 'R', static_cast<uint32_t>(dist));
    }
    in.close();
    return out;
};

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");

    // Read input.txt
    vector<pair<bool, uint32_t>> moves;
    ifstream infile("../input.txt");
    if (!infile) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }

    moves = parse(infile);
    
    
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
    for (const auto& m : moves) {
        uint32_t remaining = m.second;
        while (remaining > 0) {
            uint8_t this_dist = (remaining > 255) ? 255 : static_cast<uint8_t>(remaining);
            top->direction = m.first;
            top->distance = this_dist;
            top->valid = 1;
            top->clk = 1;
            top->eval();
            tfp->dump(time++);
            top->clk = 0;
            top->eval();
            tfp->dump(time++);
            top->valid = 0;
            remaining -= this_dist;
        }
    }

    // Print result
    cout << top->count << endl;
    tfp->close();
    delete tfp;
    delete top;
    return 0;
}
