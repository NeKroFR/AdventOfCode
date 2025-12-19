module top #(
    parameter logic [6:0] INITIAL_POSITION = 50
) (
    input logic clk,
    input logic rst,
    input logic valid,
    input logic direction, // R = 1, L = 0
    input logic [7:0] distance,
    output logic [31:0] count
);
    logic [6:0] position;
    int signed full, eff_d, pos, next;
    logic extra_lap;
    logic [6:0] next_poval;
    int signed to_add;

    always_comb begin
        // full = distance / 100;
        // eff_d = distance % 100;
        // But this version is a bit more optimized lol
        logic q, r;
        q = distance[7] | (distance[6] & distance[5] & (distance[4] | distance[3] | distance[2]));
        r = distance[7] & distance[6] & (distance[5] | distance[4] | distance[3]);
        full = int'(q) + int'(r);
        eff_d = int'(distance) - (q ? 32'd100 : 32'd0) - (r ? 32'd100 : 32'd0);

        pos = int'({1'b0, position});

        if (direction) begin // Right
            next = pos + eff_d;
            extra_lap = (next >= 100);
            next_poval = 7'(extra_lap ? (next - 32'd100) : next);
        end else begin // Left
            next = pos - eff_d;
            extra_lap = (eff_d >= pos) && (pos != 0);
            next_poval = 7'((next < 0) ? (next + 32'd100) : next);
        end
        to_add = full + int'(extra_lap);
    end

    always_ff @(posedge clk) begin
        if (rst) begin
            position <= INITIAL_POSITION;
            count <= 32'd0;
        end else if (valid) begin
            position <= next_poval;
            count <= count + 32'(to_add);
        end
    end
endmodule
