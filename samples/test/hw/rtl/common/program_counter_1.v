module program_counter_1
(
  input clk,
  input rst,
  input en,
  input [1-1:0] max,
  input [1-1:0] loop,
  output reg [1-1:0] pc
);

  reg [1-1:0] pc_next;

  always @(posedge clk) begin
    if(rst) begin
      pc_next <= 0;
      pc <= 0;
    end else begin
      if(en) begin
        if(pc_next < max) begin
          pc <= pc_next;
          pc_next <= pc_next + 1;
        end else begin
          pc <= pc_next;
          pc_next <= loop;
        end
      end 
    end
  end

endmodule