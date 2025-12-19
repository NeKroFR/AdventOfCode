// TODO: Optimize, do not use division

module top #(
    parameter int N = 9 // May need to increase based on max input size
) (
    input  logic        clk,
    input  logic        rst,
    input  logic        valid,
    input  logic [63:0] addend,
    output logic [63:0] count
);
    typedef logic [63:0] uint64_array_t [0:N];

    function automatic logic [63:0] pow10(int exp);
        logic [63:0] res;
        res = 64'd1;
        for (int i = 0; i < exp; i++)
            res = res * 10;
        return res;
    endfunction

    function automatic logic [63:0] get_multiplier(int l, int d);
        logic [63:0] m, p_d;
        m = 0;
        p_d = pow10(d);
        // m = (10^l - 1) / (10^d - 1)
        for (int i = 0; i < (l/d); i++) begin
            logic [63:0] t;
            t = 1;
            for (int j = 0; j < i; j++)
                t *= p_d;
            m += t;
        end
        return m;
    endfunction

    function automatic logic [63:0] modinv(logic [63:0] M);
        logic [63:0] inv;
        inv = 1; 
        // inv = M^(2^64 - 1) mod 2^64
        for (int i = 0; i < 6; i++) begin // 6 iterations is enough for 64-bit
            inv = inv * (2 - M * inv);
        end
        return inv;
    endfunction
    
    function automatic uint64_array_t init_pow10();
        uint64_array_t arr;
        for (int i = 0; i <= N; i++)
            arr[i] = pow10(i);
        return arr;
    endfunction

    function automatic logic check_div(logic [63:0] n, int l, int d);
        // check if (n * invM) <= (max_uint64 / M)
        logic [63:0] M, invM, maxQ;
        M = get_multiplier(l, d);
        invM = modinv(M);
        maxQ = 64'hFFFFFFFFFFFFFFFF / M;
        return (n * invM) <= maxQ;
    endfunction

    localparam uint64_array_t POW10 = init_pow10();
    logic is_periodic;
    int   l_val;

    always_comb begin
        is_periodic = 0;
        l_val = 1;
        for (int i = 1; i <= N; i++) begin
            if (addend >= POW10[i])
                l_val = i + 1;
        end

        if (l_val >= 2) begin
            for (int d = 1; d <= l_val / 2; d++) begin
                if (l_val % d == 0) begin
                    if (check_div(addend, l_val, d)) begin
                        is_periodic = 1;
                        break;
                    end
                end
            end
        end
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            count <= 64'd0;
        end else if (valid && is_periodic) begin
            count <= count + addend;
        end
    end
endmodule
