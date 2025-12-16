module top (
    input logic clk,
    input logic rst,
    input logic valid,
    output logic [31:0] count
);
    logic [6:0] position;
    always_ff @(posedge clk) begin
        if (rst) begin
            count <= 32'd0;
        end else if (valid) begin
            count <= count + 1;
        end
    end
endmodule
