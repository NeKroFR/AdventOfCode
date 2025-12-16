module top (
    input logic clk,
    input logic rst,
    input logic valid,
    input logic direction, // R = 1, L = 0
    input logic [7:0] distance,
    output logic [31:0] count
);
    logic [6:0] position;
    always_ff @(posedge clk) begin
        if (rst) begin
            position <= 7'd50; // Initial position is 50
            count <= 32'd0;
        end else if (valid) begin
            logic [6:0] new_pos;
            logic [31:0] new_count;
            logic [1:0] full;
            logic [7:0] eff_d;

            // Compute full laps and effective distance
            if (distance >= 8'd200) begin
                full = 2'd2;
            end else if (distance >= 8'd100) begin
                full = 2'd1;
            end else begin
                full = 2'd0;
            end
            eff_d = distance - (8'd100 * {6'b0, full});

            if (direction) begin  // Right
                logic carry;
                logic [7:0] tmp_pos = position + eff_d;
                if (tmp_pos >= 8'd100) begin
                    new_pos = tmp_pos - 8'd100;
                    carry = 1'b1;
                end else begin
                    new_pos = tmp_pos[6:0];
                    carry = 1'b0;
                end
                new_count = count + {30'b0, full} + {31'b0, carry};
            end else begin  // Left
                logic add_extra;
                if (eff_d > position) begin
                    new_pos = position + 7'd100 - eff_d;
                end else begin
                    new_pos = position - eff_d;
                end
                add_extra = (eff_d >= position) && (position != 7'd0);
                new_count = count + {30'b0, full} + {31'b0, add_extra};
            end
            position <= new_pos;
            count <= new_count;
        end
    end
endmodule
