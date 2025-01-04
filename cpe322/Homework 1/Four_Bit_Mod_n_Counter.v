module Four_Bit_Mod_n_Counter (
	input clk,
	input reset,
	input ld,
	input en,
	input [3:0] d,
	output reg [3:0] q,
	output reg c_out
);

	parameter N = 10; // default modulus 10
	
	// set counter
	always @(posedge clk or posedge reset or posedge ld) begin
		if (reset)
			q <= 4'b0000;  // async clear
		else if (ld)
			q <= d;  // async load
		else if (en && (q == N - 1))
			q <= 4'b0000;  // sync wrap around
		else if (en)
			q <= q + 1;  // sync increment
	end

	// set carry output
	always @(*) begin
		if (en && (q == N - 1))
			c_out = 1'b1;
		else
			c_out = 1'b0;
	end

endmodule
