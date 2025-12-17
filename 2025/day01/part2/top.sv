module top (
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

    always_ff @(posedge clk) begin
        if (rst) begin
            position <= 7'd50;
            count <= 32'd0;
        end else if (valid) begin

            // full = distance / 100;
            // eff_d = distance % 100;
            // But this version is a bit more optimized lol
            full = (distance[7] | (distance[6] & distance[5] & (distance[4] | distance[3] | distance[2]))) +
                   (distance[7] & distance[6] & (distance[5] | distance[4] | distance[3]));
            eff_d = distance -
                    ((distance[7] | (distance[6] & distance[5] & (distance[4] | distance[3] | distance[2]))) ? 8'd100 : 8'd0) -
                    ((distance[7] & distance[6] & (distance[5] | distance[4] | distance[3])) ? 8'd100 : 8'd0);

            pos = $signed({1'b0, position});

            if (direction) begin // Right
                next = pos + eff_d;
                extra_lap = (next >= 100);
                next_poval = extra_lap ? (next - 100) : next[6:0];
            end else begin // Left
                next = pos - eff_d;
                extra_lap = (eff_d >= pos) && (pos != 0);
                next_poval = (next < 0) ? (next + 100) : next[6:0];
            end
            position <= next_poval;
            count <= count + full + extra_lap;
        end
    end
endmodule
