module reg_tree_4_7_2 #
(
  parameter DATA_WIDTH = 16
)
(
  input clk,
  input [DATA_WIDTH-1:0] in,
  output [DATA_WIDTH-1:0] out_0,
  output [DATA_WIDTH-1:0] out_1,
  output [DATA_WIDTH-1:0] out_2,
  output [DATA_WIDTH-1:0] out_3,
  output [DATA_WIDTH-1:0] out_4,
  output [DATA_WIDTH-1:0] out_5,
  output [DATA_WIDTH-1:0] out_6
);

  reg [DATA_WIDTH-1:0] r [0:24-1];
  integer i;

  initial begin
    for(i=0; i<24; i=i+1) begin
      r[i] = 0;
    end
  end



  always @(posedge clk) begin
    r[0] <= in;
    r[1] <= r[0];
    r[2] <= r[0];
    r[3] <= r[1];
    r[4] <= r[1];
    r[5] <= r[1];
    r[6] <= r[1];
    r[7] <= r[2];
    r[8] <= r[2];
    r[9] <= r[2];
    r[10] <= r[3];
    r[11] <= r[4];
    r[12] <= r[5];
    r[13] <= r[6];
    r[14] <= r[7];
    r[15] <= r[8];
    r[16] <= r[9];
    r[17] <= r[10];
    r[18] <= r[11];
    r[19] <= r[12];
    r[20] <= r[13];
    r[21] <= r[14];
    r[22] <= r[15];
    r[23] <= r[16];

  end

  assign out_0 = r[17];
  assign out_1 = r[18];
  assign out_2 = r[19];
  assign out_3 = r[20];
  assign out_4 = r[21];
  assign out_5 = r[22];
  assign out_6 = r[23];

endmodule