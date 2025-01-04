// 24 Hour Clock Testbench
`timescale 1ms/100ps

module Clock_24_Hour_tb1;

	parameter CLK_PERIOD = 1000; // clock period in ms

	reg clk;
	reg reset_time;
	reg set_time;
	reg [23:0] time_in;
	wire [23:0] time_out;

	// 1Hz clock generation
	always #((CLK_PERIOD / 2)) clk = ~clk;  // toggle clk every half period

	// instantiate Clock_24_Hour unit under test module
	// Clock_24_Hour_structural or Clock_24_Hour_behavioral
	Clock_24_Hour_structural UUT (
		.clk(clk),
		.reset_time(reset_time),
		.set_time(set_time),
        	.time_in(time_in),
        	.time_out(time_out)
	);

	initial
		begin
			// initialize inputs
        		clk = 1'b1;
        		reset_time = 1'b0;
        		set_time = 1'b1;  // load initial time
        		time_in = 24'h123456;  // time 12:34:56
		
			// 1) reset_time
        		#250  // delay 250ms != CLK_PERIOD to display async functionality
			reset_time = 1'b1;  // initiate reset, priority over set_time
			#500
			set_time = 1'b0;  // set low to prepare for rising edge

			// 2) set_time to 23:59:55 in time_out
			#850  // delay 850ms to misalign with clk edges
        		reset_time = 1'b0;  // disable reset to set time
			set_time = 1'b1;  // set rising edge to load time
			time_in = 24'h235955;

			// 3) count from 23:59:55 to 00:00:05
			#650
			set_time = 1'b0;  // resume clock increment when both reset_time and set_time are zero
			#750 // delay 750ms to line up delay times with rising edge of clk
        		#(10 * CLK_PERIOD); // wait for 10 clock cycles (10 seconds)
			$finish;  // 13 seconds elapsed total
		end

endmodule

