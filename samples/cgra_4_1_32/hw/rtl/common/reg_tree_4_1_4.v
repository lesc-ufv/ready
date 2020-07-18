module reg_tree_4_1_4 #
(
  parameter DATA_WIDTH = 16
)
(
  input clk,
  input [DATA_WIDTH-1:0] in,
  output [DATA_WIDTH-1:0] out_0
);

  reg [DATA_WIDTH-1:0] r [0:6-1];
  integer i;

  initial begin
    for(i=0; i<6; i=i+1) begin
      r[i] = 0;
    end
  end



  always @(posedge clk) begin
    r[0] <= in;
    r[1] <= r[0];
    r[2] <= r[1];
    r[3] <= r[2];
    r[4] <= r[3];
    r[5] <= r[4];

  end

  assign out_0 = r[5];

endmodule