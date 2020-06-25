module reg_tree_4_4_2 #
(
  parameter DATA_WIDTH = 16
)
(
  input clk,
  input [DATA_WIDTH-1:0] in,
  output [DATA_WIDTH-1:0] out_0,
  output [DATA_WIDTH-1:0] out_1,
  output [DATA_WIDTH-1:0] out_2,
  output [DATA_WIDTH-1:0] out_3
);

  reg [DATA_WIDTH-1:0] r [0:13-1];
  integer i;

  initial begin
    for(i=0; i<13; i=i+1) begin
      r[i] = 0;
    end
  end



  always @(posedge clk) begin
    r[0] <= in;
    r[1] <= r[0];
    r[2] <= r[0];
    r[3] <= r[0];
    r[4] <= r[0];
    r[5] <= r[1];
    r[6] <= r[2];
    r[7] <= r[3];
    r[8] <= r[4];
    r[9] <= r[5];
    r[10] <= r[6];
    r[11] <= r[7];
    r[12] <= r[8];

  end

  assign out_0 = r[9];
  assign out_1 = r[10];
  assign out_2 = r[11];
  assign out_3 = r[12];

endmodule