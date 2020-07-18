module cgra0_top
(
  input clk,
  input rst,
  input en,
  input [64-1:0] conf_bus_in,
  output [1-1:0] fifo_in_re,
  input [32-1:0] fifo_in_data,
  output [1-1:0] fifo_out_we,
  output [32-1:0] fifo_out_data
);


  wire [64-1:0] conf_bus [0:6-1];
  wire [32-1:0] pe2neta [0:4-1];
  wire [32-1:0] pe2netb [0:4-1];
  wire [32-1:0] net2pea [0:4-1];
  wire [32-1:0] net2peb [0:4-1];
  wire [4-1:0] pe2net_branch;
  wire [4-1:0] net_branch2peb;


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  reg_conf_bus_in2
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(conf_bus_in),
    .out(conf_bus[0])
  );


  cgra0_pe_in
  #(
    .PE_ID(1)
  )
  pe_io_in_1
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .conf_bus_in(conf_bus[0]),
    .branch_in(net_branch2peb[0]),
    .branch_out(pe2net_branch[0]),
    .fifo_re(fifo_in_re[0]),
    .fifo_data(fifo_in_data[31:0]),
    .ina(net2pea[0]),
    .inb(net2peb[0]),
    .outa(pe2neta[0]),
    .outb(pe2netb[0])
  );


  cgra0_pe
  #(
    .PE_ID(2)
  )
  pe_2
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .conf_bus_in(conf_bus[1]),
    .branch_in(net_branch2peb[1]),
    .branch_out(pe2net_branch[1]),
    .ina(net2pea[1]),
    .inb(net2peb[1]),
    .outa(pe2neta[1]),
    .outb(pe2netb[1])
  );


  cgra0_pe
  #(
    .PE_ID(3)
  )
  pe_3
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .conf_bus_in(conf_bus[2]),
    .branch_in(net_branch2peb[2]),
    .branch_out(pe2net_branch[2]),
    .ina(net2pea[2]),
    .inb(net2peb[2]),
    .outa(pe2neta[2]),
    .outb(pe2netb[2])
  );


  cgra0_pe_out
  #(
    .PE_ID(4)
  )
  pe_io_out_4
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .conf_bus_in(conf_bus[3]),
    .branch_in(net_branch2peb[3]),
    .branch_out(pe2net_branch[3]),
    .fifo_we(fifo_out_we[0]),
    .fifo_data(fifo_out_data[31:0]),
    .ina(net2pea[3]),
    .inb(net2peb[3]),
    .outa(pe2neta[3]),
    .outb(pe2netb[3])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  conf_bus_reg_0
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(conf_bus[0]),
    .out(conf_bus[1])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  conf_bus_reg_1
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(conf_bus[1]),
    .out(conf_bus[2])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  conf_bus_reg_2
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(conf_bus[2]),
    .out(conf_bus[3])
  );


  reg_pipe
  #(
    .NUM_STAGES(1),
    .DATA_WIDTH(64)
  )
  conf_bus_reg_3
  (
    .clk(clk),
    .rst(1'b0),
    .en(1'b1),
    .in(conf_bus[3]),
    .out(conf_bus[4])
  );


  omega8x8_2_0_1
  #(
    .WIDTH(32),
    .PIPE_EXTRA(0)
  )
  net
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .net_conf_bus_in(conf_bus[4]),
    .in0(pe2neta[0]),
    .in1(pe2netb[0]),
    .in2(pe2neta[1]),
    .in3(pe2netb[1]),
    .in4(pe2neta[2]),
    .in5(pe2netb[2]),
    .in6(pe2neta[3]),
    .in7(pe2netb[3]),
    .out0(net2pea[0]),
    .out1(net2peb[0]),
    .out2(net2pea[1]),
    .out3(net2peb[1]),
    .out4(net2pea[2]),
    .out5(net2peb[2]),
    .out6(net2pea[3]),
    .out7(net2peb[3])
  );


  omega_branch4x4_2_1_1
  #(
    .WIDTH(1),
    .PIPE_EXTRA(0)
  )
  net_branch
  (
    .clk(clk),
    .rst(rst),
    .en(en),
    .net_conf_bus_in(conf_bus[4]),
    .in0(pe2net_branch[0]),
    .in1(pe2net_branch[1]),
    .in2(pe2net_branch[2]),
    .in3(pe2net_branch[3]),
    .out0(net_branch2peb[0]),
    .out1(net_branch2peb[1]),
    .out2(net_branch2peb[2]),
    .out3(net_branch2peb[3])
  );

endmodule