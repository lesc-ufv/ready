module switch_box2x2 #
(
  parameter WIDTH = 16
)
(
  input [2-1:0] sel,
  input [WIDTH-1:0] in0,
  input [WIDTH-1:0] in1,
  output [WIDTH-1:0] out0,
  output [WIDTH-1:0] out1
);


  mux2x1
  #(
    .WIDTH(WIDTH)
  )
  mux0
  (
    .in0(in0),
    .in1(in1),
    .sel(sel[0:0]),
    .out(out0)
  );


  mux2x1
  #(
    .WIDTH(WIDTH)
  )
  mux1
  (
    .in0(in0),
    .in1(in1),
    .sel(sel[1:1]),
    .out(out1)
  );

endmodule