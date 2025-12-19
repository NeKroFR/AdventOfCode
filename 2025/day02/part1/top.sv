module top #(
    parameter int N = 9 // May need to increase based on max input size
) (
    input  logic        clk,
    input  logic        rst,
    input  logic        valid,
    input  logic [63:0] addend,
    output logic [63:0] count
);

    typedef logic [63:0] pow_array_t [0:N];
    typedef logic [63:0] mul_array_t [1:10];
    typedef int          shr_array_t [1:10];

    function automatic logic [63:0] pow10(int exp);
        logic [63:0] res = 64'd1;
        for (int i = 0; i < exp; i++) begin
            res = (res << 3) + (res << 1);  // res *= 10
        end
        return res;
    endfunction

    function automatic pow_array_t init_pow10();
        pow_array_t arr;
        for (int i = 0; i <= N; i++) begin
            arr[i] = pow10(i);
        end
        return arr;
    endfunction

    function automatic int floor_log2(logic [63:0] val);
        for (int i = 63; i >= 0; i--) begin
            if (val[i])
                return i;
        end
        return 0;
    endfunction

    function automatic mul_array_t init_mul();
        mul_array_t arr;
        logic [127:0] num;
        logic [63:0] d;
        int k;

        // m = ceil(2^(64+k) / d)        
        for (int i = 1; i <= 10; i++) begin
            d = pow10(i);
            k = floor_log2(d);
            num = 128'd1 << (64 + k);
            arr[i] = 64'((num + 128'(d) - 128'd1) / 128'(d));
        end
        return arr;
    endfunction

    function automatic shr_array_t init_shr1();
        shr_array_t arr;
        for (int i = 1; i <= 10; i++)
            arr[i] = 0;
        return arr;
    endfunction

    function automatic shr_array_t init_shr2();
        shr_array_t arr;
        for (int i = 1; i <= 10; i++) begin
            arr[i] = floor_log2(pow10(i));
        end
        return arr;
    endfunction

    localparam pow_array_t POW10 = init_pow10();
    localparam mul_array_t MUL   = init_mul();
    localparam shr_array_t SHR1  = init_shr1();
    localparam shr_array_t SHR2  = init_shr2();

    logic [63:0] left, right, d;
    logic        is_palindrome_half;
    int          l_val, half;

    always_comb begin
        logic [63:0] m;
        logic [63:0] tmp;
        logic [63:0] q;
        int shr1_val;
        int shr2_val;

        is_palindrome_half = 0;
        l_val    = 1;
        half     = 0;
        d        = 64'd1;
        m        = 64'd0;
        shr1_val = 0;
        shr2_val = 0;
        tmp      = 64'd0;
        q        = 64'd0;
        left     = 64'd0;
        right    = 64'd0;

        for (int i = 1; i <= N; i++) begin
            if (addend >= POW10[i]) begin
                l_val = i + 1;
            end
        end

        if (addend != 64'd0 && (!l_val[0])) begin
            half     = l_val >> 1;
            d        = POW10[half];
            m        = MUL[half];
            shr1_val = SHR1[half];
            shr2_val = SHR2[half];

            // q = (left = addend / d)
            tmp  = addend >> shr1_val;
            q    = 64'((128'(tmp) * 128'(m)) >> 64);
            left = q >> shr2_val;
            // r = (right = addend % d)
            right = addend - (left * d);

            is_palindrome_half = (left == right);
        end
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            count <= 64'd0;
        end else if (valid && is_palindrome_half) begin
            count <= count + addend;
        end
    end
endmodule
