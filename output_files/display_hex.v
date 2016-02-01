//Hex to 7-segment display code converter

module display_hex (
	input [3:0] hex,
	output reg [0:6] seg
);

//012_3456 (segments are active-low)
parameter ZERO = 7'b111_1101;
parameter ONE = 7'b011_0000;
parameter TWO = 7'b110_1101;
parameter THREE = 7'b111_1001;
parameter FOUR = 7'b011_0011;
parameter FIVE = 7'b101_1011;
parameter SIX = 7'b101_1111;
parameter SEVEN = 7'b111_0000;
parameter EIGHT = 7'b111_1111;
parameter NINE = 7'b111_0011;
parameter A = 7'b111_0111;
parameter B = 7'b001_1111;
parameter C = 7'b100_1110;
parameter D = 7'b011_1101;
parameter E = 7'b100_1111;
parameter F = 7'b100_0111;

always @(hex)

case (hex)
	0: seg = ZERO;
	1: seg = ONE;
	2: seg = TWO;
	3: seg = THREE;
	4: seg = FOUR;
	5: seg = FIVE;
	6: seg = SIX;
	7: seg = SEVEN;
	8: seg = EIGHT;
	9: seg = NINE;
	10: seg = A;
	11: seg = B;
	12: seg = C;
	13: seg = D;
	14: seg = E;
	15: seg = F;
endcase

endmodule

