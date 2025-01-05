module clock_implement(input CLK, reset, set, output [6:0] HH, hh, MM, mm, SS, ss);
	
	reg [23:0] set_time;
	wire [23:0] T;
	reg [26: 0] clock_divider;
	
	initial
		begin
		set_time = 24'b001000110101100101010101; // Should correspond to 23:59:55
		clock_divider = 0;
		end
		
		

		
	always @( posedge CLK)
		begin
			set_time = 24'b001000110101100101010101;
			clock_divider = clock_divider + 3; // Using bit 25 and adding 3 will generate very close to 1 second clock pulses
		end
	
	Clock_24_Hour_structural clock_24(.CLK(clock_divider[24]), .Reset_time(reset), .Set_time(set), .Time_in(set_time), .Time_out(T));
	//Clock_24_Hour_behavioral clock_24(.CLK(clock_divider[26]), .Reset_time(reset), .Set_time(set), .Time_in(set_time), .Time_out(T));
	
	hex_seven 	Hr(.i(T[23:20]), .hex(HH)), 
					hr(.i(T[19:16]), .hex(hh)), 
					Mi(.i(T[15:12]), .hex(MM)), 
					mi(.i(T[11:8]), .hex(mm)), 
					Se(.i(T[7:4]), .hex(SS)), 
					se(.i(T[3:0]), .hex(ss));

endmodule


module hex_seven(i,hex);
   input [3:0] i;
   output reg [6:0] hex;

	always @ (i)
	   case (i)
		   0  : hex <= 7'b1000000;
		   1  : hex <= 7'b1111001;
		   2  : hex <= 7'b0100100;
		   3  : hex <= 7'b0110000;
		   4  : hex <= 7'b0011001;
		   5  : hex <= 7'b0010010;
		   6  : hex <= 7'b0000010;
		   7  : hex <= 7'b1111000;
         8  : hex <= 7'b0000000;
		   9  : hex <= 7'b0011000;
		   10 : hex <= 7'b0001000;
		   11 : hex <= 7'b0000011;
		   12 : hex <= 7'b1000110;
		   13 : hex <= 7'b0100001;
		   14 : hex <= 7'b0000110;
		   15 : hex <= 7'b0001110;
		   default : hex <= 7'bx;
		endcase

endmodule
