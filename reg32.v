module reg32(
input clock,
input reset_n,
input [31:0] D,
input [3:0] byteenable, 
output reg [31:0] Q
);


always @ (posedge clock or negedge reset_n)
begin
	if (!reset_n) begin
		Q <= 32'h0000;
	end else if (byteenable == 4'b1111) begin
		Q <= D;
	end else if (byteenable == 4'b0011) begin 
		Q[15:0] <= D[15:0];
	end else if (byteenable == 4'b1100) begin 
		Q[31:16] <= D[31:16];
	end else if (byteenable == 4'b0001) begin 
		Q[7:0] <= D[7:0];
	end else if (byteenable == 4'b0010) begin 
		Q[15:8] <= D[15:8];
	end else if (byteenable == 4'b0100) begin 
		Q[23:16] <= D[23:16];
	end else if (byteenable == 4'b1000) begin 
		Q[31:24] <= D[31:24];
	end 
end	
	
endmodule