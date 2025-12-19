#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


auto parse = [](ifstream& in) -> vector<pair<uint64_t, uint64_t>> {
    vector<pair<uint64_t, uint64_t>> ranges;
    string s;
    if (getline(in, s)) {
        stringstream ss(s);
        string token;
        while (getline(ss, token, ',')) {
            if (token.empty()) continue;
            stringstream ss2(token);
            string a_str, b_str;
            getline(ss2, a_str, '-');
            getline(ss2, b_str, '-');
            uint64_t a = stoull(a_str);
            uint64_t b = stoull(b_str);
            ranges.emplace_back(a, b);
        }
    }
    in.close();
    return ranges;
};

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("wave.vcd");

    // Read input.txt
    vector<pair<uint64_t, uint64_t>> ranges;
    ifstream infile("../input.txt");
    if (!infile) {
        cerr << "Error: Cannot open input.txt" << endl;
        return 1;
    }

    ranges = parse(infile);
    
    
    // Simulation setup
    top->clk = 0;
    top->rst = 1;
    top->valid = 0;
    top->addend = 0;
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
    for (const auto& r : ranges) {
        for (uint64_t n = r.first; n <= r.second; n++) {
            top->addend = n;
            top->valid = 1;
            top->clk = 1;
            top->eval();
            tfp->dump(time++);
            top->clk = 0;
            top->eval();
            tfp->dump(time++);
            top->valid = 0;
        }
    }

    // Print result
    cout << top->count << endl;
    tfp->close();
    delete tfp;
    delete top;
    return 0;
}
