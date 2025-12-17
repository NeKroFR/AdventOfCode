module top (
    input logic clk,
    input logic rst,
    input logic valid,
    input logic direction,  // R = 1, L = 0
    input logic [7:0] distance,
    output logic [31:0] count
);
    logic [6:0] position;
    logic [7:0] pos, d, delta, sum, new_pos;
    
    always_ff @(posedge clk) begin
        if (rst) begin
            position <= 7'd50;  // Initial position is 50
            count    <= 32'd0;
        end else if (valid) begin
            pos = position;
            d   = distance; // Input distance

            while (d >= 8'd100) begin
                d -= 8'd100;
            end
            
            delta = direction ? d : (8'd100 - d);
            
            sum = pos + delta;
            if (sum >= 8'd100) begin
                new_pos = sum - 8'd100;
            end else begin
                new_pos = sum;
            end
            
            position <= new_pos[6:0]; 
            if (new_pos == 8'd0) begin
                count <= count + 1;
            end
        end
    end
endmodule
