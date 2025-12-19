module top #(
    parameter int INITIAL_POSITION = 50
) (
    input  logic        clk,
    input  logic        rst,
    input  logic        valid,
    input  logic        direction,  // R = 1, L = 0
    input  logic [7:0]  distance,
    output logic [31:0] count
);
    logic [6:0] position;
    logic [7:0] d, delta, sum, new_pos;

    always_comb begin
        d       = distance;
        delta   = 8'd0;
        sum     = 8'd0;
        new_pos = {1'b0, position};

        if (d >= 8'd100) d = d - 8'd100;
        if (d >= 8'd100) d = d - 8'd100;

        delta = direction ? d : (8'd100 - d);

        sum = {1'b0, position} + delta;
        if (sum >= 8'd100)
            new_pos = sum - 8'd100;
        else
            new_pos = sum;
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            position <= INITIAL_POSITION[6:0];
            count    <= 32'd0;
        end else if (valid) begin
            position <= new_pos[6:0];
            if (new_pos == 8'd0)
                count <= count + 1;
        end
    end
endmodule
