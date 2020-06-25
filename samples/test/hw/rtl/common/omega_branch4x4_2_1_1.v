module omega_branch4x4_2_1_1 #
(
  parameter WIDTH = 16,
  parameter PIPE_EXTRA = 0
)
(
  input clk,
  input rst,
  input en,
  input [64-1:0] net_conf_bus_in,
  input [WIDTH-1:0] in0,
  input [WIDTH-1:0] in1,
  input [WIDTH-1:0] in2,
  input [WIDTH-1:0] in3,
  output [WIDTH-1:0] out0,
  output [WIDTH-1:0] out1,
  output [WIDTH-1:0] out2,
  output [WIDTH-1:0] out3
);

  wire [12-1:0] conf_out;
  wire [WIDTH-1:0] in_reg_wire_0 [0:4-1];
  wire [WIDTH-1:0] in_reg_wire_1 [0:4-1];
  wire [WIDTH-1:0] in_reg_wire_2 [0:4-1];
  wire [WIDTH-1:0] in_reg_wire_3 [0:4-1];
  wire [WIDTH-1:0] in_reg_wire_4 [0:4-1];
  wire [WIDTH-1:0] in_reg_wire_5 [0:4-1];
  wire [64-1:0] net_conf_bus [0:6-1];

  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg0
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus_in),
    .out(net_conf_bus[0])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(1),
    .STAGE(PIPE_EXTRA + 1)
  )
  swicth_conf_control_0
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[0]),
    .swicth_conf_out(conf_out[1:0])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg1
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus[0]),
    .out(net_conf_bus[1])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(2),
    .STAGE(PIPE_EXTRA + 1)
  )
  swicth_conf_control_1
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[1]),
    .swicth_conf_out(conf_out[3:2])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg2
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus[1]),
    .out(net_conf_bus[2])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(3),
    .STAGE(PIPE_EXTRA + 2)
  )
  swicth_conf_control_2
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[2]),
    .swicth_conf_out(conf_out[5:4])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg3
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus[2]),
    .out(net_conf_bus[3])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(4),
    .STAGE(PIPE_EXTRA + 2)
  )
  swicth_conf_control_3
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[3]),
    .swicth_conf_out(conf_out[7:6])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg4
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus[3]),
    .out(net_conf_bus[4])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(5),
    .STAGE(PIPE_EXTRA + 3)
  )
  swicth_conf_control_4
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[4]),
    .swicth_conf_out(conf_out[9:8])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  net_conf_bus_reg5
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(net_conf_bus[4]),
    .out(net_conf_bus[5])
  );


  swicth_conf_control_branch_2_1
  #(
    .SWICTH_NUMBER(6),
    .STAGE(PIPE_EXTRA + 3)
  )
  swicth_conf_control_5
  (
    .clk(clk),
    .rst(rst),
    .en_pc_net(en),
    .conf_bus_in(net_conf_bus[5]),
    .swicth_conf_out(conf_out[11:10])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_0_0
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in0),
    .out(in_reg_wire_0[0])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_0_1
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in1),
    .out(in_reg_wire_0[1])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_0_2
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in2),
    .out(in_reg_wire_0[2])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_0_3
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in3),
    .out(in_reg_wire_0[3])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_1_0
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_1[0]),
    .out(in_reg_wire_2[0])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_1_1
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_1[1]),
    .out(in_reg_wire_2[1])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_1_2
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_1[2]),
    .out(in_reg_wire_2[2])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_1_3
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_1[3]),
    .out(in_reg_wire_2[3])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_2_0
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_3[0]),
    .out(in_reg_wire_4[0])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_2_1
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_3[1]),
    .out(in_reg_wire_4[1])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_2_2
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_3[2]),
    .out(in_reg_wire_4[2])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_2_3
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_3[3]),
    .out(in_reg_wire_4[3])
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_3_0
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_5[0]),
    .out(out0)
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_3_1
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_5[1]),
    .out(out2)
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_3_2
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_5[2]),
    .out(out1)
  );


  reg_pipe
  #(
    .NUM_STAGES(PIPE_EXTRA + 1),
    .DATA_WIDTH(WIDTH)
  )
  reg_in_3_3
  (
    .clk(clk),
    .rst(1'b0),
    .en(en),
    .in(in_reg_wire_5[3]),
    .out(out3)
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_0_0
  (
    .sel(conf_out[1:0]),
    .in0(in_reg_wire_0[0]),
    .in1(in_reg_wire_0[2]),
    .out0(in_reg_wire_1[0]),
    .out1(in_reg_wire_1[1])
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_0_1
  (
    .sel(conf_out[3:2]),
    .in0(in_reg_wire_0[1]),
    .in1(in_reg_wire_0[3]),
    .out0(in_reg_wire_1[2]),
    .out1(in_reg_wire_1[3])
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_1_0
  (
    .sel(conf_out[5:4]),
    .in0(in_reg_wire_2[0]),
    .in1(in_reg_wire_2[2]),
    .out0(in_reg_wire_3[0]),
    .out1(in_reg_wire_3[1])
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_1_1
  (
    .sel(conf_out[7:6]),
    .in0(in_reg_wire_2[1]),
    .in1(in_reg_wire_2[3]),
    .out0(in_reg_wire_3[2]),
    .out1(in_reg_wire_3[3])
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_2_0
  (
    .sel(conf_out[9:8]),
    .in0(in_reg_wire_4[0]),
    .in1(in_reg_wire_4[2]),
    .out0(in_reg_wire_5[0]),
    .out1(in_reg_wire_5[1])
  );


  switch_box2x2
  #(
    .WIDTH(WIDTH)
  )
  sw_2_1
  (
    .sel(conf_out[11:10]),
    .in0(in_reg_wire_4[1]),
    .in1(in_reg_wire_4[3]),
    .out0(in_reg_wire_5[2]),
    .out1(in_reg_wire_5[3])
  );

endmodule