// behavioral model of D flip flop
module D_FF (
	input clk,
	input d,
	output reg q
);

	always @ (posedge clk) begin
		q <= d;  // assign D to Q on positive edge of CLK signal
	end

endmodule

// structural model of Clock_24_Hour top level module
module Clock_24_Hour_structural (
	input clk,
	input reset_time,
	input set_time,
	input [23:0] time_in,
	output [23:0] time_out
);

	wire c_out0, c_out1, c_out2, c_out3, c_out4, c_out5;  // carry bits
	wire q_out, g3_out, g2_out, g1_out;  // gate outputs
	parameter VCC = 1'b1;  // set VCC to logic high

	// 4-bit modulo counters for each digit of hours, minutes, and seconds
	Four_Bit_Mod_n_Counter #(.N(3)) hr_tens (.clk(clk), .reset(g1_out), .ld(set_time), .en(c_out4), .d(time_in[23:20]), .q(time_out[23:20]), .c_out(c_out5));
	Four_Bit_Mod_n_Counter #(.N(10)) hr_ones (.clk(clk), .reset(g1_out), .ld(set_time), .en(c_out3), .d(time_in[19:16]), .q(time_out[19:16]), .c_out(c_out4));
	Four_Bit_Mod_n_Counter #(.N(6)) min_tens (.clk(clk), .reset(reset_time), .ld(set_time), .en(c_out2), .d(time_in[15:12]), .q(time_out[15:12]), .c_out(c_out3));
	Four_Bit_Mod_n_Counter #(.N(10)) min_ones (.clk(clk), .reset(reset_time), .ld(set_time), .en(c_out1), .d(time_in[11:8]), .q(time_out[11:8]), .c_out(c_out2));
	Four_Bit_Mod_n_Counter #(.N(6)) sec_tens (.clk(clk), .reset(reset_time), .ld(set_time), .en(c_out0), .d(time_in[7:4]), .q(time_out[7:4]), .c_out(c_out1));
	Four_Bit_Mod_n_Counter #(.N(10)) sec_ones (.clk(clk), .reset(reset_time), .ld(set_time), .en(VCC), .d(time_in[3:0]), .q(time_out[3:0]), .c_out(c_out0));

	// logic gates and flip-flop logic to handle hours reset
	not (g3_out, time_out[20]);
	and (g2_out, time_out[21], g3_out, time_out[17], time_out[16], c_out3);
	D_FF d_ff(.clk(clk), .d(g2_out), .q(q_out));
	or (g1_out, q_out, reset_time);

endmodule
