// 24 Hour Clock Testbench
`timescale 1ms/100ps

module Clock_24_Hour_tb1;

   	parameter CLK_PERIOD = 1000; // clock period in ms, 1s period for 1Hz freq

	// declare inputs/outputs and initial values
	reg clk=1'b1;  // start clock HIGH
	reg reset_time=1'b0;
	reg set_time=1'b1;  // load initial value
	reg [23:0] time_in=24'h000000;  // initial time
	wire [23:0] time_out;  // calculated time

	reg [23:0] t_expected;  // expected time
	integer i;  // loop counter
	reg [7:0] hr, min, sec;
	reg [3:0] hr_tens, hr_ones, min_tens, min_ones, sec_tens, sec_ones;

	// 1Hz clock generation
	always #((CLK_PERIOD / 2)) clk = ~clk;  // toggle clk every half period for 50% duty cycle

	// instantiate Clock_24_Hour unit under test module
	// Clock_24_Hour_structural or Clock_24_Hour_behavioral
	Clock_24_Hour_behavioral UUT (
		.clk(clk),
		.reset_time(reset_time),
		.set_time(set_time),
		.time_in(time_in),
		.time_out(time_out)
	);
	
	initial begin
		// iterate through 00:00:00 to 23:59:59 in seconds, total seconds = 24*60*60
		for (i = 0; i < 24*60*60; i = i + 1)
			begin
				// calculate time components
				hr = i / 3600;  // integer division
				min = (i % 3600) / 60;
				sec = i % 60;

				// extract individual digits
				hr_tens = hr / 10;
				hr_ones = hr % 10;
        			min_tens = min / 10;
        			min_ones = min % 10;
        			sec_tens = sec / 10;
				sec_ones = sec % 10;

				// assign expected result
				t_expected[23:20] = hr_tens;
				t_expected[19:16] = hr_ones;
				t_expected[15:12] = min_tens;
				t_expected[11:8] = min_ones;
				t_expected[7:4] = sec_tens;
				t_expected[3:0] = sec_ones;

				#CLK_PERIOD;  // 1 second delay

				// if first iteration after initial time loaded, return to normal clock function
				if (i == 0) set_time = 0;

				// if calculated time does not equal expected time, display discrepancy
				if (time_out != t_expected)
					begin
            					$display("Mismatch, Expected Time: %h, Output Time: %h", t_expected, time_out);
					end
			end
		$finish;  // 86400 seconds elapsed total
	end

endmodule
